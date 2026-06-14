#include <sys/types.h>
#ifndef LEDS_H
#define LEDS_H

#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
#include <NeoPixelBus.h>
#else
#include <Adafruit_NeoPixel.h>
#endif

#include "Wire.h"
#include "common.h"
#include "segments.h"
#include "c_cct.h"
#include "c_grad.h"

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2
#define PWM_FREQ 2000
#define RESOLUTION 8
#define CHIPSET WS2812B
#define COLOR_ORDER_WS2815 NEO_GRB
#define COLOR_ORDER_WS2811 NEO_RGB
#define COLOR_ORDER_COB_RGBIC NEO_RGB
// #define COLOR_ORDER COLOR_ORDER_WS2815
// #define COLOR_ORDER COLOR_ORDER_WS2811
#define COLOR_ORDER COLOR_ORDER_COB_RGBIC

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

void cct_out(c_cct cct_val);

void grad_out(C_GRAD grad_val);

uint16_t set_pixel(uint16_t start, uint16_t used_addresses, uint16_t pixel_per_section, uint8_t dimmer_mode, uint8_t white_mode, uint8_t* data);

void show_segments(uint16_t segs);

uint16_t output_artnet(rlc_artnet artnet_var, uint8_t dimmer_mode, uint8_t white_mode);

uint16_t universe_out(uint16_t start_index, uint16_t end_index, uint8_t dimmer_factor, uint16_t pixel_per_section, CRGB& color, uint16_t& data_index, uint16_t& led_index, uint8_t* data, uint16_t sum, uint8_t white_mode);

void rainbow_fw();
#endif