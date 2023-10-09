#ifndef LEDS_H
#define LEDS_H

#include "common.h"
#include "pdc.h"

#define RED_PIN 10
#define GREEN_PIN 9
#define BLUE_PIN 8
#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2
#define PWM_FREQ 2000
#define RESOLUTION 8

/**
 * Initializes the LED pins as outputs.
 */
void init_led();

/**
 * Ramps up the brightness from 0 to the last value.
 *
 * @param hsv_val: An HSV value representing the target brightness.
 * @param rgb_val: An RGB value representing the target brightness.
 * @param pdc: The variable of the pdc page to get current color and brightness.
 * @param main_sw: The main menu switching object.
 */
void ramp_up(C_HSV hsv_val, C_RGB rgb_val, pdc_page& pdc, main& main_sw);

/**
 * Sets the output of an RGB LED with the given value and scaling factor.
 *
 * @param led_val: The target RGB value.
 * @param factor: The scaling factor to apply to the LED.
 */
void rgb_out(CRGB led_val, uint8_t factor);

/**
 * Sets the output of an HSV LED with the given value.
 *
 * @param hsv_val: The target HSV value.
 */
void hsv_out(C_HSV hsv_val);

#endif