#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "event_manager_cfg.h"

#define EVENT_QUEUE_SIZE 16

typedef struct {
  event_id_t id;
  uint32_t param;
} event_t;

class EventManager {
 public:
  void init();

  // Get next event from queue (returns false if empty)
  bool get_event(event_t* event);

  // Post events
  bool post(event_id_t id, uint32_t param = 0);
  bool post_urgent(event_id_t id, uint32_t param = 0);

  // Queue management
  bool is_pending(event_id_t id) const;
  void clear();
  void clear_event(event_id_t id);
  uint8_t get_pending_count() const;

 private:
  struct event_entry_t {
    event_id_t id;
    uint32_t param;
    bool valid;
  };

  event_entry_t queue[EVENT_QUEUE_SIZE];
  uint8_t head;
  uint8_t tail;
  uint8_t count;

  const event_cfg_t* find_config(event_id_t id) const;
};

extern EventManager event_manager;

#endif  // EVENT_MANAGER_H
