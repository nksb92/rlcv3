#ifndef LEDS_H
#define LEDS_H

#include "common.h"
#include <Adafruit_NeoPixel.h>
#include "segments.h"

#define RED_PIN 10
#define GREEN_PIN 9
#define BLUE_PIN 8
#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2
#define PWM_FREQ 2000
#define RESOLUTION 8
#define DATA_OUT 8
#define CHIPSET WS2812B
#define COLOR_ORDER RGB

/**
 * Initializes the LED pins as outputs.
 */
void init_led();

/**
 * Sets the output of an HSV LED with the given value.
 *
 * @param hsv_val: The target HSV value.
 */
void hsv_out(C_HSV hsv_val);

void drive_pixel(CRGB rgb_val, uint8_t factor);

void show_segments(uint16_t segs);

#endif