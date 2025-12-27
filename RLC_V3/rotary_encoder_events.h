#ifndef ROTARY_ENCODER_EVENTS_H
#define ROTARY_ENCODER_EVENTS_H

// https://github.com/Stutchbury/EncoderButton Encoder Libary
#include <EncoderButton.h>

#include "event_manager.h"

// The pin number for the switch pin of the rotary encoder
// the EncoderButton libary sets this pin to pull-up
#define SW_PIN D0

// The pin number for the CLK (clock) pin of the rotary encoder
#define CLK_PIN D1

// The pin number for the DT (data) pin of the rotary encoder
#define DT_PIN D2

#define LONG_PRESS_TIME 750
#define ACCERLERATION_SPEED 75

extern EncoderButton enc_button;
extern EventManager event_manager;

// Initialize encoder with event-posting callbacks
void init_encoder_with_events();

#endif  // ROTARY_ENCODER_EVENTS_H
