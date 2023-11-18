#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H
// https://github.com/Stutchbury/EncoderButton Encoder Libary
#include <EncoderButton.h>
#include "common.h"

// These defines are used to specify the pin numbers for the switch,
// data, and clock pins of the rotary encoder.

// The pin number for the switch pin of the rotary encoder
// the EncoderButton libary sets this pin to pull-up
#define SW_PIN 2

// The pin number for the CLK (clock) pin of the rotary encoder
#define CLK_PIN 3

// The pin number for the DT (data) pin of the rotary encoder
#define DT_PIN 4

#define LONG_PRESS_TIME 750

/**
 * Initialize the rotary encoder module with the specified EncoderButton object.
 *
 * @param eb: The EncoderButton object to use for handling button events.
 */
void init_encoder(EncoderButton& eb);

/**
 * Handle the encoder event.
 *
 * @param eb: The EncoderButton object that generated the event.
 */
void encoder_handler(EncoderButton& eb);

/**
 * Get the current encoder value and reset it.
 *
 * @return The current encoder value.
 */
int16_t get_encoder_val();

/**
 * Handle the long press event.
 *
 * @param eb: The EncoderButton object that generated the event.
 */
void long_press_handler(EncoderButton& eb);

/**
 * Get the state of the long press flag.
 *
 * @return The state of the long press flag.
 */
bool get_long_press();

/**
 * Set the state of the long press flag.
 *
 * @param state: The state to set the long press flag to.
 */
void set_long_press(bool state);

/**
 * Handle the press event.
 *
 * @param eb: The EncoderButton object that generated the event.
 */
void press_handler(EncoderButton& eb);

/**
 * Get the state of the press flag.
 *
 * @return The state of the press flag.
 */
bool get_press_state();

/**
 * Set the state of the press flag.
 *
 * @param state: The state to set the press flag to.
 */
void set_press_state(bool state);

/**
 * Handle the double press event.
 *
 * @param eb: The EncoderButton object that generated the event.
 */
void double_press_handler(EncoderButton& eb);

/**
 * Get the state of the double press flag.
 *
 * @return The state of the double press flag.
 */
bool get_double_press();

/**
 * Set the state of the double press flag.
 *
 * @param state: The state to set the double press flag to.
 */
void set_double_press(bool state);

/**
 * Get the state of the event status flag and reset it.
 *
 * @return The state of the event status flag.
 */
bool get_event_status();

/**
 * Set the state of the event status flag.
 *
 * @param state: The state to set the event status flag to.
 */
void set_event_status(bool state);

/**
 * Set the standby state of the display.
 *
 * @param state: The state to set the standby flag to.
 */
void set_dspl_standby(bool state);

bool get_standby_status();

#endif