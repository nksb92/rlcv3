#include "soft_timer.h"

#include <Arduino.h>

#include "event_manager.h"

SoftTimerManager TimerManager;

void SoftTimerManager::init() {
  for (uint8_t i = 0; i < soft_timer_config_count; i++) {
    const soft_timer_cfg_t* cfg = &soft_timer_config[i];
    timers[cfg->id].period_ms = cfg->default_period;
    timers[cfg->id].state = TIMER_STOPPED;
    timers[cfg->id].start_time = 0;

    if (cfg->auto_start) {
      start(cfg->id);
    }
  }
}

void SoftTimerManager::update() {
  uint32_t now = millis();

  for (uint8_t i = 0; i < soft_timer_config_count; i++) {
    const soft_timer_cfg_t* cfg = &soft_timer_config[i];
    timer_runtime_t* rt = &timers[cfg->id];

    if (rt->state != TIMER_RUNNING) {
      continue;
    }

    if ((now - rt->start_time) >= rt->period_ms) {
      handle_expiry(i);
    }
  }
}

void SoftTimerManager::handle_expiry(uint8_t cfg_index) {
  const soft_timer_cfg_t* cfg = &soft_timer_config[cfg_index];
  timer_runtime_t* rt = &timers[cfg->id];

  // Post event if configured
  if (cfg->event_id != EVT_NONE) {
    event_manager.post(cfg->event_id);
  }

  // Handle mode
  if (cfg->mode == TIMER_MODE_PERIODIC) {
    rt->start_time = millis();
  } else {
    rt->state = TIMER_EXPIRED;
  }
}

void SoftTimerManager::start(timer_id_t id) {
  timers[id].start_time = millis();
  timers[id].state = TIMER_RUNNING;
}

void SoftTimerManager::stop(timer_id_t id) {
  timers[id].state = TIMER_STOPPED;
}

void SoftTimerManager::restart(timer_id_t id) {
  timers[id].start_time = millis();
  timers[id].state = TIMER_RUNNING;
}

void SoftTimerManager::set_period(timer_id_t id, uint32_t period_ms) {
  timers[id].period_ms = period_ms;
}

timer_state_t SoftTimerManager::get_state(timer_id_t id) const {
  return timers[id].state;
}

uint32_t SoftTimerManager::get_remaining(timer_id_t id) const {
  if (timers[id].state != TIMER_RUNNING) {
    return 0;
  }
  uint32_t elapsed = millis() - timers[id].start_time;
  if (elapsed >= timers[id].period_ms) {
    return 0;
  }
  return timers[id].period_ms - elapsed;
}

bool SoftTimerManager::is_running(timer_id_t id) const {
  return timers[id].state == TIMER_RUNNING;
}
