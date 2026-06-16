/**
 * @file event_handler.h
 * @brief Header file for the event-handling logic.
 */

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "event_manager.h"

/**
 * @brief Processes a single event from the event manager queue.
 * 
 * Dispatcher function that maps events (such as button clicks, encoder changes,
 * timer expirations, WiFi changes, or save triggers) to their respective state changes.
 * 
 * @param[in] event Pointer to the event to process.
 */
void process_event(const event_t* event);

#endif  // EVENT_HANDLER_H
