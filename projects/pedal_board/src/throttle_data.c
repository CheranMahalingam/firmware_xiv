#include "ads1015.h"
#include "brake_data.h"
#include "event_queue.h"
#include "fsm.h"
#include "log.h"
#include "pedal_data_tx.h"
#include "pedal_events.h"
#include "soft_timer.h"
#include "pedal_data.h"

#define UPPER_THROTTLE_VALUE 1273
#define LOWER_THROTTLE_VALUE 295
#define MULTIPLYER 4096

StatusCode get_throttle_data(PedalDataStorage *storage, int16_t *position) {
  // throttle actually uses 2 channels. may configure later
  status_ok_or_return(ads1015_read_raw(get_ads1015_storage(), storage->throttle_channel2, position));
  int32_t range = UPPER_THROTTLE_VALUE - LOWER_THROTTLE_VALUE;
  int32_t position_upscaled = (int32_t)*position * MULTIPLYER;
  position_upscaled -= LOWER_THROTTLE_VALUE * MULTIPLYER;
  position_upscaled *= 100;
  position_upscaled /= range * MULTIPLYER;
  *position = (int16_t)position_upscaled;
  return STATUS_CODE_OK;
}
