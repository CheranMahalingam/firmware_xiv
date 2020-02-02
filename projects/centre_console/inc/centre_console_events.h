#pragma once

typedef enum {
  CENTRE_CONSOLE_EVENT_CAN_RX = 0,
  CENTRE_CONSOLE_EVENT_CAN_TX,
  CENTRE_CONSOLE_EVENT_CAN_FAULT,
  NUM_CENTRE_CONSOLE_EVENTS  // 3
} CentreConsoleEvent;

typedef enum {
  CENTRE_CONSOLE_POWER_EVENT_OFF = NUM_CENTRE_CONSOLE_EVENTS, // 3
  CENTRE_CONSOLE_POWER_EVENT_ON_MAIN,
  CENTRE_CONSOLE_POWER_EVENT_ON_AUX,
  CENTRE_CONSOLE_POWER_EVENT_CLEAR_FAULT,
  CENTRE_CONSOLE_POWER_EVENT_PUBLISH_FAULT,
  CENTRE_CONSOLE_POWER_EVENT_FAULT,
  CENTRE_CONSOLE_POWER_EVENT_FAULT_POWER_MAIN_SEQUENCE,
  CENTRE_CONSOLE_POWER_EVENT_FAULT_POWER_AUX_SEQUENCE,
  NUM_CENTRE_CONSOLE_POWER_EVENTS  // 11
} CentreConsolePowerEvent;

typedef enum {
  POWER_AUX_SEQUENCE_EVENT_BEGIN = NUM_CENTRE_CONSOLE_POWER_EVENTS,  // 11
  POWER_AUX_SEQUENCE_EVENT_FAULT,
  POWER_AUX_SEQUENCE_EVENT_AUX_STATUS_OK,
  POWER_AUX_SEQUENCE_EVENT_TURNED_ON_EVERYTHING,
  POWER_AUX_SEQUENCE_EVENT_COMPLETE,
  NUM_POWER_AUX_SEQUENCE_EVENTS  // 16
} PowerAuxSequenceEvent;

typedef enum {
  POWER_MAIN_SEQUENCE_EVENT_BEGIN = NUM_POWER_AUX_SEQUENCE_EVENTS,  // 16
  POWER_MAIN_SEQUENCE_EVENT_FAULT,
  POWER_MAIN_SEQUENCE_EVENT_NO_OP,
  POWER_MAIN_SEQUENCE_EVENT_AUX_STATUS_OK,
  POWER_MAIN_SEQUENCE_EVENT_DRIVER_DISPLAY_BMS_ON,
  POWER_MAIN_SEQUENCE_EVENT_BATTERY_STATUS_OK,
  POWER_MAIN_SEQUENCE_EVENT_BATTERY_RELAYS_CLOSED,
  POWER_MAIN_SEQUENCE_EVENT_DC_DC_OK,
  POWER_MAIN_SEQUENCE_EVENT_TURNED_ON_EVERYTHING,
  POWER_MAIN_SEQUENCE_EVENT_PRECHARGE_BEGAN,
  POWER_MAIN_SEQUENCE_EVENT_PRECHARGE_COMPLETE,
  POWER_MAIN_SEQUENCE_EVENT_COMPLETE,
  NUM_POWER_MAIN_SEQUENCE_EVENTS
} PowerMainSequenceEvent;

typedef enum {
  DRIVE_FSM_INPUT_EVENT_NEUTRAL = NUM_POWER_MAIN_SEQUENCE_EVENTS,  // 16
  DRIVE_FSM_INPUT_EVENT_PARKING,
  DRIVE_FSM_INPUT_EVENT_REVERSE,
  DRIVE_FSM_INPUT_EVENT_CHARGING,
  DRIVE_FSM_INPUT_EVENT_DRIVE,
  DRIVE_FSM_INPUT_EVENT_FAULT,
  DRIVE_FSM_INPUT_EVENT_MCI_RELAYS_CLOSED_DESTINATION_DRIVE,
  DRIVE_FSM_INPUT_EVENT_MCI_RELAYS_CLOSED_DESTINATION_REVERSE,
  DRIVE_FSM_INPUT_EVENT_MCI_RELAYS_OPENED_DESTINATION_NEUTRAL,
  DRIVE_FSM_INPUT_EVENT_MCI_RELAYS_OPENED_DESTINATION_PARKING,
  DRIVE_FSM_INPUT_EVENT_MCI_EBRAKE_PRESSED,
  DRIVE_FSM_INPUT_EVENT_MCI_EBRAKE_RELEASED_DESTINATION_DRIVE_REVERSE,
  DRIVE_FSM_INPUT_EVENT_MCI_EBRAKE_RELEASED_DESTINATION_NEUTRAL,
  NUM_DRIVE_FSM_INPUT_EVENTS
} DriveFsmInputEvent;

typedef enum {
  DRIVE_FSM_OUTPUT_EVENT_DRIVE = NUM_DRIVE_FSM_INPUT_EVENTS,
  DRIVE_FSM_OUTPUT_EVENT_REVERSE,
  DRIVE_FSM_OUTPUT_EVENT_FAULT,
  DRIVE_FSM_OUTPUT_EVENT_PARKING,
  DRIVE_FSM_OUTPUT_EVENT_NEUTRAL,
  NUM_DRIVE_FSM_OUTPUT_EVENTS
} DriveFsmOutputEvent;

typedef enum {
  BATTERY_HEARTBEAT_EVENT_HEALTH_CHECK_REQUEST = NUM_DRIVE_FSM_OUTPUT_EVENTS,
  NUM_BATTERY_HEARTBEAT_EVENTS
} BatteryHeartbeatEvent;

typedef enum {
  POWER_OFF_SEQUENCE_EVENT_BEGIN = NUM_BATTERY_HEARTBEAT_EVENTS,
  POWER_OFF_SEQUENCE_EVENT_COMPLETE,
  NUM_POWER_OFF_SEQUENCE_EVENTS
} PowerOffSequenceEvent;

typedef enum {
  CENTRE_CONSOLE_BUTTON_PRESS_EVENT_DRIVE = NUM_POWER_OFF_SEQUENCE_EVENTS,
  CENTRE_CONSOLE_BUTTON_PRESS_EVENT_REVERSE,
  CENTRE_CONSOLE_BUTTON_PRESS_EVENT_POWER,
  CENTRE_CONSOLE_BUTTON_PRESS_EVENT_NEUTRAL,
  CENTRE_CONSOLE_BUTTON_PRESS_EVENT_HAZARD,
  CENTRE_CONSOLE_BUTTON_PRESS_EVENT_EMERGENCY_STOP
} CentreConsoleButtonPressEvent;
