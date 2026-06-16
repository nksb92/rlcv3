/**
 * @file soft_timer_cfg.h
 * @brief Configuration definitions for software timers (IDs, modes, and states).
 */

#ifndef SOFT_TIMER_CFG_H
#define SOFT_TIMER_CFG_H

#include <stdint.h>

#include "event_manager_cfg.h"
#include "std_defines.h"

/**
 * @enum timer_id_t
 * @brief List of all supported software timer identifiers.
 */
typedef enum {
  TIMER_DISPLAY_STANDBY,      /**< Timer regulating display standby inactivity blanking. */
  TIMER_FAN_COOLDOWN,         /**< Timer regulating fan cooldown period after turning off load. */
  TIMER_SCROLL_TEXT,          /**< Timer managing IP scrolling speed. */
  TIMER_CONNECTING_DOTS,      /**< Timer managing loading dot progress intervals. */
  TIMER_RAINBOW_ANIM,         /**< Timer managing color cycling updates in rainbow mode. */
  TIMER_UPDATE_FAN,           /**< Timer managing PWM adjustment cycle for thermal control. */
  TIMER_COUNT                 /**< Total count of timer slots. */
} timer_id_t;

/**
 * @enum timer_mode_t
 * @brief Periodic vs single-execution timer execution modes.
 */
typedef enum {
  TIMER_MODE_ONE_SHOT,        /**< Timer expires once and stops. */
  TIMER_MODE_PERIODIC         /**< Timer automatically restarts upon expiration. */
} timer_mode_t;

/**
 * @enum timer_state_t
 * @brief Runtime states of a software timer.
 */
typedef enum {
  TIMER_STOPPED,              /**< Timer is paused/inactive. */
  TIMER_RUNNING,              /**< Timer is active and counting down. */
  TIMER_EXPIRED               /**< Timer has reached zero (one-shot mode). */
} timer_state_t;

/**
 * @struct soft_timer_cfg_t
 * @brief Configuration data structure defining a static timer template.
 */
typedef struct {
  timer_id_t id;              /**< Unique timer ID. */
  const char* name;           /**< User-readable string name for debugging. */
  uint32_t default_period;    /**< Expiration duration in milliseconds. */
  timer_mode_t mode;          /**< Execution mode (one-shot/periodic). */
  event_id_t event_id;        /**< ID of the event to post when timer expires. */
  bool auto_start;            /**< True if the timer starts active upon boot/init. */
} soft_timer_cfg_t;

extern const soft_timer_cfg_t soft_timer_config[]; /**< System-wide static timer config table. */
extern const uint8_t soft_timer_config_count;      /**< Total count of configured timers. */

#endif  // SOFT_TIMER_CFG_H
