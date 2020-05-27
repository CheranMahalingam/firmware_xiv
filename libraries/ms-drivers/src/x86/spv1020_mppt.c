#include "spv1020_mppt.h"

StatusCode spv1020_shut(void) {
  return STATUS_CODE_UNIMPLEMENTED;
}

StatusCode spv1020_turn_on(void) {
  return STATUS_CODE_UNIMPLEMENTED;
}

StatusCode spv1020_read_current(uint16_t *current) {
  return STATUS_CODE_UNIMPLEMENTED;
}

StatusCode spv1020_read_voltage_in(uint16_t *vin) {
  return STATUS_CODE_UNIMPLEMENTED;
}

StatusCode spv1020_read_pwm(uint16_t *pwm) {
  return STATUS_CODE_UNIMPLEMENTED;
}

StatusCode spv1020_read_status(uint8_t *status) {
  return STATUS_CODE_UNIMPLEMENTED;
}

bool spv1020_is_overcurrent(uint8_t status, uint8_t *ovc_branch) {
  return false;
}

bool spv1020_is_overvoltage(uint8_t status) {
  return false;
}

bool spv1020_is_overtemperature(uint8_t status) {
  return false;
}
