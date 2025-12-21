#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H

#include "soft_timer_cfg.h"

class SoftTimerManager {
 public:
  void init();
  void update();

  // Timer control
  void start(timer_id_t id);
  void stop(timer_id_t id);
  void restart(timer_id_t id);

  // Modify period at runtime
  void set_period(timer_id_t id, uint32_t period_ms);

  // Status
  timer_state_t get_state(timer_id_t id) const;
  uint32_t get_remaining(timer_id_t id) const;
  bool is_running(timer_id_t id) const;

 private:
  struct timer_runtime_t {
    uint32_t start_time;
    uint32_t period_ms;
    timer_state_t state;
  };

  timer_runtime_t timers[TIMER_COUNT];

  void handle_expiry(uint8_t cfg_index);
};

extern SoftTimerManager TimerManager;

#endif  // SOFT_TIMER_H
