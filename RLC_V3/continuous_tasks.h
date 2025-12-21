#ifndef CONTINUOUS_TASKS_H
#define CONTINUOUS_TASKS_H

// Handle continuous polling tasks (DMX, Artnet)
// These are NOT event-driven as they are continuous data streams
void handle_continuous_tasks();

#endif  // CONTINUOUS_TASKS_H
