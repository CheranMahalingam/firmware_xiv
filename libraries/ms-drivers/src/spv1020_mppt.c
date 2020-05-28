#include "spv1020_mppt.h"
#include "spv1020_mppt_defs.h"

// This file implements common functionality between stm32 and x86. See stm32f0xx/spv1020_mppt.c
// and x86/spv1020_mppt.c for stm32 and x86-specific functionality.

bool spv1020_is_overcurrent(uint8_t status, uint8_t *ovc_branches) {
  // this is the number of bits to shift to get the OVC bits of the bitmask as the LSBs
  const uint8_t ovc_bitshift = __builtin_ctz(OVC_BITMASK);

  *ovc_branches = (status & OVC_BITMASK) >> ovc_bitshift;
  return *ovc_branches != 0;
}

bool spv1020_is_overvoltage(uint8_t status) {
  return (status & OVV_BITMASK) != 0;
}

bool spv1020_is_overtemperature(uint8_t status) {
  return (status & OVT_BITMASK) != 0;
}

// What should we do about the CR bit (or bits)? Ask Micah.
