/**
 * @file event_manager_cfg.h
 * @brief Configuration definitions for the event manager (IDs, priorities, and structs).
 */

#ifndef EVENT_MANAGER_CFG_H
#define EVENT_MANAGER_CFG_H

#include <stdint.h>

/**
 * @enum event_id_t
 * @brief List of all supported event identifiers.
 */
typedef enum {
  EVT_NONE = 0,               /**< Empty or invalid event. */

  // Input events
  EVT_ENCODER_CHANGED,        /**< Rotary encoder position updated. */
  EVT_BUTTON_CLICK,           /**< Encoder button clicked. */
  EVT_BUTTON_LONG_PRESS,      /**< Encoder button held down. */
  EVT_BUTTON_DOUBLE_PRESS,    /**< Encoder button clicked twice. */

  // Timer events
  EVT_DISPLAY_STANDBY,        /**< Display inactivity standby timeout. */
  EVT_FAN_COOLDOWN,           /**< Trigger fan speed reduction/cooldown. */
  EVT_SCROLL_TICK,            /**< Scroll animation update interval. */
  EVT_CONNECTING_DOTS_TICK,   /**< Connecting loader animation update interval. */
  EVT_RAINBOW_TICK,           /**< Rainbow color effect rotation update interval. */
  EVT_UPDATE_FAN,             /**< Fan temperature control regulation interval. */
  
  // System events
  EVT_SAVE_TO_NVM,            /**< Save variables/state to EEPROM. */
  EVT_DISPLAY_WAKE,           /**< Wake display and reset standby timer. */
  EVT_LEAVE_SAVED_SCREEN,     /**< Re-render normal menu after splash screen duration. */
  EVT_WIFI_CONNECTED,         /**< ArtNet WiFi connection established. */
  EVT_WIFI_DISCONNECTED,      /**< ArtNet WiFi connection lost. */

  EVT_COUNT  /**< Total number of event types. */
} event_id_t;

/**
 * @enum event_priority_t
 * @brief Event dispatching priority level.
 */
typedef enum {
  EVT_PRIORITY_LOW,           /**< Dispatched during idle times. */
  EVT_PRIORITY_NORMAL,        /**< Standard dispatching logic. */
  EVT_PRIORITY_HIGH           /**< Urgent/real-time dispatching. */
} event_priority_t;

/**
 * @struct event_cfg_t
 * @brief Configuration details for a single event type.
 */
typedef struct {
  event_id_t id;              /**< The event ID. */
  const char* name;           /**< User-readable string name for debug logging. */
  event_priority_t priority;  /**< Event dispatch priority. */
  bool queue_enabled;         /**< True to allow multiple copies of this event ID in the queue. */
} event_cfg_t;

extern const event_cfg_t event_config[];  /**< System-wide event configuration table. */
extern const uint8_t event_config_count;   /**< Total number of items in the config table. */

#endif  // EVENT_MANAGER_CFG_H
