#include "can.h"
#include "can_transmit.h"
#include "can_unpack.h"
#include "delay.h"
#include "exported_enums.h"
#include "test_helpers.h"

#include "mci_events.h"
#include "motor_controller.h"
#include "precharge_control.h"

static CanStorage s_can_storage;
static MotorControllerStorage s_mci_storage;

void prv_setup_system_can() {
  CanSettings can_settings = {
    .device_id = SYSTEM_CAN_DEVICE_MOTOR_CONTROLLER,
    .bitrate = CAN_HW_BITRATE_500KBPS,
    .rx_event = MCI_CAN_EVENT_RX,
    .tx_event = MCI_CAN_EVENT_TX,
    .fault_event = MCI_CAN_EVENT_FAULT,
    .tx = { GPIO_PORT_A, 12 },
    .rx = { GPIO_PORT_A, 11 },
    .loopback = true,
  };

  can_init(&s_can_storage, &can_settings);
}

void prv_mci_storage_init(void *context) {
  MotorControllerStorage *storage = context;
  PrechargeStorage precharge_storage = { .precharge_control = { .port = GPIO_PORT_A, .pin = 9 },
                                         .precharge_control2 = { .port = GPIO_PORT_B, .pin = 1 },
                                         .precharge_monitor = { .port = GPIO_PORT_B, .pin = 0 },
                                         .state = MCI_PRECHARGE_DISCHARGED };
  storage->precharge_storage = precharge_storage;
}

void setup_test(void) {
  prv_setup_system_can();
  prv_mci_storage_init(&s_mci_storage);
  TEST_ASSERT(precharge_control_init(&s_mci_storage) == STATUS_CODE_OK);
}

void teardown_test(void) {}

void test_run(void) {
  MotorControllerStorage *storage = &s_mci_storage;
  TEST_ASSERT_TRUE(get_precharge_state(storage) == GPIO_STATE_LOW);

  // Test that a non precharge power main sequence message does nothing
  CAN_TRANSMIT_POWER_ON_MAIN_SEQUENCE(NULL, EE_POWER_MAIN_SEQUENCE_CONFIRM_AUX_STATUS);
  // TODO(SOFT-113): Check if this is valid amount of time to wait,
  // i.e. how long does precharge take
  delay_ms(500);
  TEST_ASSERT_TRUE(storage->precharge_storage.state != MCI_PRECHARGE_CHARGED);

  // Test that a precharge message precharges
  CAN_TRANSMIT_POWER_ON_MAIN_SEQUENCE(NULL, EE_POWER_MAIN_SEQUENCE_BEGIN_PRECHARGE);
  delay_ms(500);
  TEST_ASSERT_TRUE(storage->precharge_storage.state == MCI_PRECHARGE_CHARGED);
  // TODO(SOFT-113): add a check to ensure proper discharge
}