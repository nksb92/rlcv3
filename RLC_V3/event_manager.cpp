#include "event_manager.h"

#include "common.h"

EventManager event_manager;

void EventManager::init() {
  head = 0;
  tail = 0;
  count = 0;

  for (uint8_t i = 0; i < EVENT_QUEUE_SIZE; i++) {
    queue[i].valid = false;
  }
}

bool EventManager::get_event(event_t* event) {
  // Skip invalid entries
  while (count > 0 && !queue[head].valid) {
    head = (head + 1) % EVENT_QUEUE_SIZE;
    count--;
  }

  if (count == 0) {
    return false;
  }

  event->id = queue[head].id;
  event->param = queue[head].param;
  queue[head].valid = false;

  head = (head + 1) % EVENT_QUEUE_SIZE;
  count--;

  return true;
}

bool EventManager::post(event_id_t id, uint32_t param) {
  if (count >= EVENT_QUEUE_SIZE) {
    DEBUG_PRINTLN("Event queue full!");
    return false;
  }

  const event_cfg_t* cfg = find_config(id);
  if (cfg == NULL) {
    return false;
  }

  // Check if queueing multiple instances is allowed
  if (!cfg->queue_enabled && is_pending(id)) {
    return false;
  }

  queue[tail].id = id;
  queue[tail].param = param;
  queue[tail].valid = true;

  tail = (tail + 1) % EVENT_QUEUE_SIZE;
  count++;

  return true;
}

bool EventManager::post_urgent(event_id_t id, uint32_t param) {
  if (count >= EVENT_QUEUE_SIZE) {
    return false;
  }

  head = (head == 0) ? (EVENT_QUEUE_SIZE - 1) : (head - 1);

  queue[head].id = id;
  queue[head].param = param;
  queue[head].valid = true;
  count++;

  return true;
}

const event_cfg_t* EventManager::find_config(event_id_t id) const {
  for (uint8_t i = 0; i < event_config_count; i++) {
    if (event_config[i].id == id) {
      return &event_config[i];
    }
  }
  return NULL;
}

bool EventManager::is_pending(event_id_t id) const {
  for (uint8_t i = 0; i < EVENT_QUEUE_SIZE; i++) {
    if (queue[i].valid && queue[i].id == id) {
      return true;
    }
  }
  return false;
}

void EventManager::clear() {
  head = 0;
  tail = 0;
  count = 0;
  for (uint8_t i = 0; i < EVENT_QUEUE_SIZE; i++) {
    queue[i].valid = false;
  }
}

void EventManager::clear_event(event_id_t id) {
  for (uint8_t i = 0; i < EVENT_QUEUE_SIZE; i++) {
    if (queue[i].valid && queue[i].id == id) {
      queue[i].valid = false;
    }
  }
}

uint8_t EventManager::get_pending_count() const {
  return count;
}
