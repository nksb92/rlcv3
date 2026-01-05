#ifndef SOFT_TIMER_CFG_H
#define SOFT_TIMER_CFG_H

#include <stdint.h>

#include "event_manager_cfg.h"
#include "std_defines.h"

// Timer IDs - add new timers here
typedef enum {
  TIMER_DISPLAY_STANDBY,
  TIMER_FAN_COOLDOWN,
  TIMER_SCROLL_TEXT,
  TIMER_CONNECTING_DOTS,
  TIMER_RAINBOW_ANIM,
  TIMER_UPDATE_FAN,
  TIMER_COUNT  // Must be last
} timer_id_t;

// Timer modes
typedef enum {
  TIMER_MODE_ONE_SHOT,
  TIMER_MODE_PERIODIC
} timer_mode_t;

// Timer state
typedef enum {
  TIMER_STOPPED,
  TIMER_RUNNING,
  TIMER_EXPIRED
} timer_state_t;

// Timer configuration entry
typedef struct {
  timer_id_t id;
  const char* name;         // Debug name
  uint32_t default_period;  // Default timer period in ms
  timer_mode_t mode;        // One-shot or periodic
  event_id_t event_id;      // Event to trigger on expiry (EVT_NONE = no event)
  bool auto_start;          // Start automatically on init
} soft_timer_cfg_t;

// Timer configuration table
extern const soft_timer_cfg_t soft_timer_config[];
extern const uint8_t soft_timer_config_count;

#endif  // SOFT_TIMER_CFG_H
