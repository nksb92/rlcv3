/**
 * @file soft_timer.h
 * @brief Header file for the software timer manager system.
 */

#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H

#include "soft_timer_cfg.h"

/**
 * @class SoftTimerManager
 * @brief Handles simulated non-blocking software timers, posting events upon expiration.
 */
class SoftTimerManager {
 public:
  /**
   * @brief Initializes timer configurations and starts auto-start timers.
   */
  void init();

  /**
   * @brief Periodic check of all running timers, triggering event dispatch on expiry.
   * Must be called frequently in the main loop.
   */
  void update();

  /**
   * @brief Starts a timer.
   * @param[in] id The timer identifier to start.
   */
  void start(timer_id_t id);

  /**
   * @brief Stops/pauses a running timer.
   * @param[in] id The timer identifier to stop.
   */
  void stop(timer_id_t id);

  /**
   * @brief Restarts a running or stopped timer, resetting its start baseline.
   * @param[in] id The timer identifier to restart.
   */
  void restart(timer_id_t id);

  /**
   * @brief Alters a timer's period at runtime.
   * @param[in] id The timer identifier to modify.
   * @param[in] period_ms New period duration in milliseconds.
   */
  void set_period(timer_id_t id, uint32_t period_ms);

  /**
   * @brief Queries the operational state of a timer.
   * @param[in] id The timer identifier.
   * @return Active state (running, stopped, expired).
   */
  timer_state_t get_state(timer_id_t id) const;

  /**
   * @brief Retrieves remaining time before next expiration.
   * @param[in] id The timer identifier.
   * @return Remaining time in milliseconds.
   */
  uint32_t get_remaining(timer_id_t id) const;

  /**
   * @brief Checks if a timer is currently active/running.
   * @param[in] id The timer identifier.
   * @return True if running, false otherwise.
   */
  bool is_running(timer_id_t id) const;

 private:
  /**
   * @struct timer_runtime_t
   * @brief State information tracked at runtime for a single timer.
   */
  struct timer_runtime_t {
    uint32_t start_time;          /**< Timestamp (millis) when the timer was started/reset. */
    uint32_t period_ms;           /**< Expiration period in milliseconds. */
    timer_state_t state;          /**< Active state of the timer. */
  };

  timer_runtime_t timers[TIMER_COUNT]; /**< List of runtime timer slots. */

  /**
   * @brief Internal helper to trigger callbacks and manage periodic recycling on expiry.
   * @param[in] cfg_index Index of the timer in configuration table.
   */
  void handle_expiry(uint8_t cfg_index);
};

extern SoftTimerManager TimerManager;

#endif  // SOFT_TIMER_H
