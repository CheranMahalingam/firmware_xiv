#pragma once

#include "can_msg_defs.h"

// This file stores enums which are exported between projects to allow both
// sides to use the same enums when sending and receiving CAN Messages over the
// primary network. To make things easier all enums in this file must follow a
// slightly modified naming convention.
//
// Example:
// typedef enum {
//   EE_<MY_CAN_MESSAGE_NAME>_<FIELD_NAME>_<VALUE> = 0,
//   // ...
//   NUM_EE_<MY_CAN_MESSAGE_NAME>_<FIELD_NAME>_<PLURAL>,
// } EE<MyCanMessageName><FieldName>

// Front Power Distribution Output to be used with a SYSTEM_CAN_MESSAGE_FRONT_POWER message.
typedef enum {
  EE_POWER_MAIN_SEQUENCE_CONFIRM_AUX_STATUS = 0,
  EE_POWER_MAIN_SEQUENCE_TURN_ON_DRIVER_BMS,
  EE_POWER_MAIN_SEQUENCE_CONFIRM_BATTERY_STATUS,
  EE_POWER_MAIN_SEQUENCE_CLOSE_BATTERY_RELAYS,
  EE_POWER_MAIN_SEQUENCE_CONFIRM_DCDC,
  EE_POWER_MAIN_SEQUENCE_TURN_ON_EVERYTHING,
  EE_POWER_MAIN_SEQUENCE_BEGIN_PRECHARGE,
  EE_POWER_MAIN_SEQUENCE_PRECHARGE_COMPLETED,
  NUM_EE_POWER_MAIN_SEQUENCES
} EEPowerMainSequence;

typedef enum {
  EE_POWER_AUX_SEQUENCE_CONFIRM_AUX_STATUS = 0,
  EE_POWER_AUX_SEQUENCE_TURN_ON_EVERYTHING,
  NUM_EE_POWER_AUX_SEQUENCES
} EEPowerAuxSequence;

typedef enum {
  EE_CHARGER_SET_RELAY_STATE_OPEN = 0,
  EE_CHARGER_SET_RELAY_STATE_CLOSE,
  NUM_EE_CHARGER_SET_RELAY_STATES,
} EEChargerSetRelayState;

typedef enum {
  EE_CHARGER_CONN_STATE_DISCONNECTED = 0,
  EE_CHARGER_CONN_STATE_CONNECTED,
  NUM_EE_CHARGER_CONN_STATES,
} EEChargerConnState;

typedef enum {
  EE_FRONT_POWER_DISTRIBUTION_OUTPUT_DRIVER_DISPLAY = 0,
  EE_FRONT_POWER_DISTRIBUTION_OUTPUT_STEERING,
  EE_FRONT_POWER_DISTRIBUTION_OUTPUT_CENTRE_CONSOLE,
  EE_FRONT_POWER_DISTRIBUTION_OUTPUT_PEDAL,
  EE_FRONT_POWER_DISTRIBUTION_OUTPUT_FRONT_HEADLIGHTS_LEFT,
  EE_FRONT_POWER_DISTRIBUTION_OUTPUT_STROBE,
  EE_FRONT_POWER_DISTRIBUTION_OUTPUT_DRIVER_FANS
} EEFrontPowerDistributionOutput;

typedef enum {
  EE_REAR_POWER_DISTRIBUTION_OUTPUT_MCI = 0,
  EE_REAR_POWER_DISTRIBUTION_OUTPUT_BMS_CARRIER,
  NUM_EE_REAR_POWER_DISTRIBUTION_OUTPUTS,
} EERearPowerDistributionOutput;

typedef enum {
  EE_RELAY_ID_BATTERY = 0,
  EE_RELAY_ID_MOTOR_CONTROLLER,
  EE_RELAY_ID_SOLAR,
  NUM_EE_RELAY_IDS,
} EERelayId;

// Front Power Distribution Output State to be used with a SYSTEM_CAN_MESSAGE_FRONT_POWER message.
typedef enum {
  EE_FRONT_POWER_DISTRIBUTION_OUTPUT_STATE_OFF = 0,
  EE_FRONT_POWER_DISTRIBUTION_OUTPUT_STATE_ON,
  NUM_EE_FRONT_POWER_DISTRIBUTION_OUTPUT_STATES
} EEFrontPowerDistributionOutputState;

// Light type to be used with a SYSTEM_CAN_MESSAGE_LIGHTS_STATE message.
typedef enum EELightType {
  EE_LIGHT_TYPE_HIGH_BEAMS = 0,
  EE_LIGHT_TYPE_LOW_BEAMS,
  EE_LIGHT_TYPE_DRL,
  EE_LIGHT_TYPE_BRAKES,
  EE_LIGHT_TYPE_SIGNAL_RIGHT,
  EE_LIGHT_TYPE_SIGNAL_LEFT,
  EE_LIGHT_TYPE_SIGNAL_HAZARD,
  EE_LIGHT_TYPE_STROBE,
  NUM_EE_LIGHT_TYPES,
} EELightType;

// Light state to be used with a SYSTEM_CAN_MESSAGE_LIGHTS message.
typedef enum EELightState {
  EE_LIGHT_STATE_OFF = 0,  //
  EE_LIGHT_STATE_ON,       //
  NUM_EE_LIGHT_STATES,     //
} EELightState;

// Horn state, used with a SYSTEM_CAN_MESSAGE_HORN message.
typedef enum EEHornState {
  EE_HORN_STATE_OFF = 0,  //
  EE_HORN_STATE_ON,       //
  NUM_EE_HORN_STATES,     //
} EEHornState;

typedef enum EERelayState {
  EE_RELAY_STATE_OPEN = 0,
  EE_RELAY_STATE_CLOSE,
  NUM_EE_RELAY_STATES,
} EERelayState;

typedef enum EEEbrakeState {
  EE_EBRAKE_STATE_PRESSED = 0,
  EE_EBRAKE_STATE_RELEASED,
  NUM_EE_EBRAKE_STATES,
} EEEbrakeState;

// For heartbeat
typedef enum EEBatteryHeartbeatFaultSource {
  EE_BATTERY_HEARTBEAT_FAULT_SOURCE_KILLSWITCH = 0,
  EE_BATTERY_HEARTBEAT_FAULT_SOURCE_CURRENT_SENSE_AFE_CELL,
  EE_BATTERY_HEARTBEAT_FAULT_SOURCE_CURRENT_SENSE_AFE_TEMP,
  EE_BATTERY_HEARTBEAT_FAULT_SOURCE_CURRENT_SENSE_AFE_FSM,
  EE_BATTERY_HEARTBEAT_FAULT_SOURCE_CURRENT_SENSE_ADC,
  EE_BATTERY_HEARTBEAT_FAULT_SOURCE_ACK_TIMEOUT,
  NUM_EE_BATTERY_HEARTBEAT_FAULT_SOURCES,
} EEBatteryHeartbeatFaultSource;

// Battery heartbeat bitset representing fault reason
typedef uint8_t EEBatteryHeartbeatState;
#define EE_BATTERY_HEARTBEAT_STATE_OK 0x0
#define EE_BATTERY_HEARTBEAT_STATE_FAULT_KILLSWITCH \
  (1 << EE_BATTERY_HEARTBEAT_FAULT_SOURCE_KILLSWITCH)
#define EE_BATTERY_HEARTBEAT_STATE_FAULT_CURRENT_SENSE_AFE_CELL \
  (1 << EE_BATTERY_HEARTBEAT_FAULT_SOURCE_LTC_AFE_CELL)
#define EE_BATTERY_HEARTBEAT_STATE_FAULT_CURRENT_SENSE_AFE_TEMP \
  (1 << EE_BATTERY_HEARTBEAT_FAULT_SOURCE_LTC_AFE_TEMP)
#define EE_BATTERY_HEARTBEAT_STATE_FAULT_CURRENT_SENSE_AFE_FSM \
  (1 << EE_BATTERY_HEARTBEAT_FAULT_SOURCE_LTC_AFE_FSM)
#define EE_BATTERY_HEARTBEAT_STATE_FAULT_CURRENT_SENSE_ADC \
  (1 << EE_BATTERY_HEARTBEAT_FAULT_SOURCE_LTC_ADC)
#define EE_BATTERY_HEARTBEAT_STATE_FAULT_ACK_TIMEOUT \
  (1 << EE_BATTERY_HEARTBEAT_FAULT_SOURCE_ACK_TIMEOUT)
