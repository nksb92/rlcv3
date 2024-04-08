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
#define COLOR_ORDER_WS2815 NEO_GRB
#define COLOR_ORDER_WS2811 NEO_RGB
#define COLOR_ORDER COLOR_ORDER_WS2815

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

void rgb_out(CRGB led_val, uint8_t factor);

void ramp_up_hsv(C_HSV hsv_val);

void drive_pixel(CRGB rgb_val, uint8_t factor);

void ramp_up_rgb(CRGB rgb_val);

void set_pixel(uint16_t start, uint16_t dimmer_channel, uint16_t pixel_per_section, uint8_t* data);

void show_segments(uint16_t segs);

void output_artnet(rlc_artnet artnet_var);

void universe_out(uint16_t start_index, uint16_t end_index, uint8_t dimmer_factor, uint16_t pixel_per_section, CRGB& color, uint16_t& data_index, uint16_t& led_index, uint8_t* data);
#endif