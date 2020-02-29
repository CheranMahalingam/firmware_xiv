#include "can.h"
#include "can_ack.h"
#include "log.h"
#include "can_msg_defs.h"
#include "can_transmit.h"
#include "can_unpack.h"
#include "gpio.h"
#include "gpio_it.h"
#include "status.h"
#include "exported_enums.h"
#include "motor_controller.h"

static PrechargeControlStorage s_precharge_storage = { 0 };

PrechargeControlStorage *test_get_storage(void) {
  return &s_precharge_storage;
}
StatusCode prv_set_precharge_control(PrechargeControlStorage *storage, const GpioState state) {
  gpio_set_state(&storage->precharge_control, state);
  gpio_set_state(&storage->precharge_control2, state);
  return STATUS_CODE_OK;
}

void prv_precharge_completed(const GpioAddress *address, void *context) {
  PrechargeControlStorage *storage = context;
  storage->state = MCI_PRECHARGE_CHARGED;
  CAN_TRANSMIT_PRECHARGE_COMPLETED();
}

StatusCode prv_discharge_rx(const CanMessage *msg, void *context, CanAckStatus *ack_reply) {
  PrechargeControlStorage *storage = context;
  storage->state = MCI_PRECHARGE_DISCHARGED;
  return prv_set_precharge_control(storage, GPIO_STATE_LOW);
}

StatusCode prv_precharge_rx(const CanMessage *msg, void *context, CanAckStatus *ack_reply) {
  PrechargeControlStorage *storage = context;
  return prv_set_precharge_control(storage, GPIO_STATE_HIGH);
}

PrechargeState get_precharge_state() {
  return s_precharge_storage.state;
}

void prv_populate_storage(PrechargeControlStorage *storage, const PrechargeControlSettings *settings) {
  storage->precharge_control = settings->precharge_control;
  storage->precharge_control2 = settings->precharge_control2;
  storage->precharge_monitor = settings->precharge_monitor;
  storage->initialized = true;
}

StatusCode precharge_control_init(const PrechargeControlSettings *settings) {
  if (s_precharge_storage.initialized) {
    return STATUS_CODE_INTERNAL_ERROR;
  }
  prv_populate_storage(&s_precharge_storage, settings);
  GpioSettings monitor_settings = { .direction = GPIO_DIR_IN,
                                                 .state = GPIO_STATE_LOW,
                                                 .alt_function = GPIO_ALTFN_NONE,
                                                 .resistor = GPIO_RES_NONE };
  GpioSettings control_settings = monitor_settings;
  control_settings.direction = GPIO_DIR_OUT;
  InterruptSettings monitor_it_settings = { .type = INTERRUPT_TYPE_INTERRUPT,
                                                         .priority = INTERRUPT_PRIORITY_NORMAL };
  status_ok_or_return(gpio_init_pin(&s_precharge_storage.precharge_control, &control_settings));
  status_ok_or_return(gpio_init_pin(&s_precharge_storage.precharge_control2, &control_settings));
  status_ok_or_return(gpio_init_pin(&s_precharge_storage.precharge_monitor, &monitor_settings));
  status_ok_or_return(
      gpio_it_register_interrupt(&s_precharge_storage.precharge_monitor, &monitor_it_settings,
                                 INTERRUPT_EDGE_RISING, prv_precharge_completed, &s_precharge_storage));
  status_ok_or_return(can_register_rx_handler(SYSTEM_CAN_MESSAGE_BEGIN_PRECHARGE, prv_precharge_rx, &s_precharge_storage));
  status_ok_or_return(can_register_rx_handler(SYSTEM_CAN_MESSAGE_DISCHARGE_PRECHARGE, prv_discharge_rx, &s_precharge_storage));
  return STATUS_CODE_OK;
}
