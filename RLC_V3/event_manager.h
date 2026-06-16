/**
 * @file event_manager.h
 * @brief Header file for the cooperative multitasking event manager.
 */

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "event_manager_cfg.h"

#define EVENT_QUEUE_SIZE 16 /**< Maximum number of events the queue can hold. */

/**
 * @struct event_t
 * @brief Representation of an event containing its ID and parameters.
 */
typedef struct {
  event_id_t id;      /**< Identifier of the event. */
  uint32_t param;     /**< Optional 32-bit payload parameter. */
} event_t;

/**
 * @class EventManager
 * @brief Event queue manager for scheduling and dispatching system events.
 */
class EventManager {
 public:
  /**
   * @brief Initializes the event queue.
   */
  void init();

  /**
   * @brief Retrieves the next pending event from the queue.
   * @param[out] event Pointer to the structure where the event will be copied.
   * @return True if an event was successfully retrieved, false if queue was empty.
   */
  bool get_event(event_t* event);

  /**
   * @brief Posts an event to the back of the queue.
   * @param[in] id The ID of the event to post.
   * @param[in] param Optional 32-bit parameter associated with the event.
   * @return True if the event was successfully queued, false if queue is full.
   */
  bool post(event_id_t id, uint32_t param = 0);

  /**
   * @brief Posts an event to the front of the queue for immediate execution.
   * @param[in] id The ID of the event to post.
   * @param[in] param Optional 32-bit parameter associated with the event.
   * @return True if successfully queued, false if queue is full.
   */
  bool post_urgent(event_id_t id, uint32_t param = 0);

  /**
   * @brief Checks if a specific event type is already pending in the queue.
   * @param[in] id The event ID to look for.
   * @return True if the event is pending, false otherwise.
   */
  bool is_pending(event_id_t id) const;

  /**
   * @brief Clears all events in the queue.
   */
  void clear();

  /**
   * @brief Invalidates all pending instances of a specific event ID.
   * @param[in] id The event ID to remove.
   */
  void clear_event(event_id_t id);

  /**
   * @brief Gets the number of valid pending events currently in the queue.
   * @return Count of pending events.
   */
  uint8_t get_pending_count() const;

 private:
  /**
   * @struct event_entry_t
   * @brief Internal queue slot holding details of a queued event.
   */
  struct event_entry_t {
    event_id_t id;
    uint32_t param;
    bool valid;
  };

  event_entry_t queue[EVENT_QUEUE_SIZE];  /**< Circular buffer array holding events. */
  uint8_t head;                            /**< Index of the head of the queue. */
  uint8_t tail;                            /**< Index of the tail of the queue. */
  uint8_t count;                           /**< Current number of elements in the queue. */

  /**
   * @brief Resolves configuration for a given event ID.
   * @param[in] id Event ID to look up.
   * @return Pointer to configuration entry, or NULL if not found.
   */
  const event_cfg_t* find_config(event_id_t id) const;
};

extern EventManager event_manager;

#endif  // EVENT_MANAGER_H
