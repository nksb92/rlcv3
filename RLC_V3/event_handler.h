#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "event_manager.h"

// Process a single event - called from main loop
void process_event(const event_t* event);

#endif  // EVENT_HANDLER_H
