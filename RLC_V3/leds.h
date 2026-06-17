/**
 * @file leds.h
 * @brief Header file for LED driver, mapping, and pattern generation.
 */

#include <sys/types.h>
#ifndef LEDS_H
#define LEDS_H

#include "Wire.h"
#include "common.h"
#include "segments.h"
#include "c_cct.h"
#include "c_grad.h"

#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
#include <NeoPixelBus.h>
#else
#include <Adafruit_NeoPixel.h>
#endif

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2
#define PWM_FREQ 2000
#define RESOLUTION 8
#define CHIPSET WS2812B

/**
 * @brief Initializes the LED controller hardware.
 * Configures the pins and installs library drivers depending on selected hardware profile.
 */
void init_led();

/**
 * @brief Sets the LED outputs using HSV color parameters.
 * @param[in] hsv_val The target HSV color.
 */
void hsv_out(C_HSV hsv_val);

/**
 * @brief Sets the LED outputs using RGB color parameters and a scaling factor.
 * @param[in] led_val FastLED CRGB color.
 * @param[in] factor Scaling factor (0-255).
 */
void rgb_out(CRGB led_val, uint8_t factor);

/**
 * @brief Sets the LED outputs using CCT (color temperature) parameters.
 * @param[in] cct_val The target CCT settings.
 */
void cct_out(c_cct cct_val);

/**
 * @brief Sets the LED outputs using Gradient parameters.
 * @param[in] grad_val The target Gradient color settings.
 */
void grad_out(C_GRAD grad_val);

/**
 * @brief Sets individual pixels/segments based on DMX or universe data buffer.
 * @param[in] start DMX start channel address.
 * @param[in] used_addresses Total number of DMX addresses consumed.
 * @param[in] pixel_per_section Number of pixels mapping to a single segment.
 * @param[in] dimmer_mode Dimmer style configuration.
 * @param[in] white_mode White channel handling mode.
 * @param[in] data Pointer to the channel data array.
 * @return Sum of all channel outputs for fan calculation.
 */
uint16_t set_pixel(uint16_t start, uint16_t used_addresses, uint16_t pixel_per_section, uint8_t dimmer_mode, uint8_t white_mode, uint8_t* data);

/**
 * @brief Briefly lights up segment boundaries for diagnostic/positioning purposes.
 * @param[in] segs Number of segments to highlight.
 */
void show_segments(uint16_t segs);

/**
 * @brief Parses ArtNet packets and updates the pixel outputs.
 * @param[in] artnet_var The ArtNet configuration and state object.
 * @param[in] dimmer_mode Dimmer style configuration.
 * @param[in] white_mode White channel handling mode.
 * @return Sum of all channel outputs for fan calculation.
 */
uint16_t output_artnet(rlc_artnet artnet_var, uint8_t dimmer_mode, uint8_t white_mode);

/**
 * @brief Helper function to output a range of channels from a universe buffer.
 * @param[in] start_index Starting channel index.
 * @param[in] end_index Ending channel index.
 * @param[in] dimmer_factor Scale factor for the dimmer.
 * @param[in] pixel_per_section Pixel segment layout.
 * @param[in,out] color Color value reference.
 * @param[in,out] data_index Buffer pointer tracking.
 * @param[in,out] led_index Physical LED indexing tracker.
 * @param[in] data Universe buffer.
 * @param[in] sum Cumulative load sum tracker.
 * @param[in] white_mode White channel handling mode.
 * @return Accumulated load sum.
 */
uint16_t universe_out(uint16_t start_index, uint16_t end_index, uint8_t dimmer_factor, uint16_t pixel_per_section, CRGB& color, uint16_t& data_index, uint16_t& led_index, uint8_t* data, uint16_t sum, uint8_t white_mode);

/**
 * @brief Runs a firmware update/diagnostic rainbow cycling animation.
 */
void rainbow_fw();

#endif