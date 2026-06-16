/**
 * @file continuous_tasks.h
 * @brief Header file for continuous polling tasks that run outside the event system.
 */

#ifndef CONTINUOUS_TASKS_H
#define CONTINUOUS_TASKS_H

/**
 * @brief Handles continuous polling tasks (such as DMX and ArtNet).
 * 
 * This function is run repeatedly in the main loop to process real-time
 * high-bandwidth data streams that cannot be modeled as sparse events.
 */
void handle_continuous_tasks();

#endif  // CONTINUOUS_TASKS_H
