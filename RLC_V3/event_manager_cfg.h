#ifndef EVENT_MANAGER_CFG_H
#define EVENT_MANAGER_CFG_H

#include <stdint.h>

// Event IDs - add new events here
typedef enum {
  EVT_NONE = 0,

  // Input events
  EVT_ENCODER_CHANGED,
  EVT_BUTTON_CLICK,
  EVT_BUTTON_LONG_PRESS,
  EVT_BUTTON_DOUBLE_PRESS,

  // Timer events
  EVT_DISPLAY_STANDBY,
  EVT_FAN_COOLDOWN,
  EVT_SCROLL_TICK,
  EVT_CONNECTING_DOTS_TICK,
  EVT_RAINBOW_TICK,
  
  // System events
  EVT_SAVE_TO_NVM,
  EVT_DISPLAY_WAKE,
  EVT_LEAVE_SAVED_SCREEN,
  EVT_WIFI_CONNECTED,
  EVT_WIFI_DISCONNECTED,

  EVT_COUNT  // Must be last
} event_id_t;

// Event priority
typedef enum {
  EVT_PRIORITY_LOW,
  EVT_PRIORITY_NORMAL,
  EVT_PRIORITY_HIGH
} event_priority_t;

// Event configuration entry
typedef struct {
  event_id_t id;
  const char* name;  // Debug name
  event_priority_t priority;
  bool queue_enabled;  // Allow queuing multiple instances
} event_cfg_t;

// Event configuration table
extern const event_cfg_t event_config[];
extern const uint8_t event_config_count;

#endif  // EVENT_MANAGER_CFG_H
