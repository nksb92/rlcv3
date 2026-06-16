/**
 * @file rotary_encoder_events.h
 * @brief Header file for rotary encoder button and rotation event-handler.
 */

#ifndef ROTARY_ENCODER_EVENTS_H
#define ROTARY_ENCODER_EVENTS_H

// https://github.com/Stutchbury/EncoderButton Encoder Library
#include <EncoderButton.h>

#include "event_manager.h"

#define SW_PIN D0                 /**< The switch (button) pin of the rotary encoder. */
#define CLK_PIN D1                /**< The CLK (clock) pin of the rotary encoder. */
#define DT_PIN D2                 /**< The DT (data) pin of the rotary encoder. */

#define LONG_PRESS_TIME 750       /**< Duration threshold (ms) to recognize a long button press. */
#define ACCERLERATION_SPEED 75    /**< Rotation acceleration factor. */

extern EncoderButton enc_button;  /**< Encoder driver object definition. */
extern EventManager event_manager; /**< Event manager dispatcher reference. */

/**
 * @brief Configures rotary encoder GPIO pins and binds callback handlers.
 */
void init_encoder_with_events();

#endif  // ROTARY_ENCODER_EVENTS_H
