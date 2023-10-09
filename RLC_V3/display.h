#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include "dmx.h"
#include "pdc.h"
#include "common.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

/**
 * Initializes the OLED display with the specified parameters.
 *
 * @param dp: the reference to the Adafruit_SSD1306 object representing the OLED display
 */
void init_display(Adafruit_SSD1306& dp);

/**
 * Updates the OLED display with the current HSV values.
 *
 * @param dp: the reference to the Adafruit_SSD1306 object representing the OLED display
 * @param out_val: the C_HSV object containing the current HSV values
 */
void hsv_display_update(Adafruit_SSD1306& dp, C_HSV out_val);

/**
 * Updates the OLED display with the current RGB values.
 *
 * @param dp: the reference to the Adafruit_SSD1306 object representing the OLED display
 * @param rgb_val: the C_RGB object containing the current RGB values
 */
void rgb_display_update(Adafruit_SSD1306& dp, C_RGB rgb_val);

/**
 * Updates the OLED display with the current DMX values.
 *
 * @param dp: the reference to the Adafruit_SSD1306 object representing the OLED display
 * @param dmx_val: the rgb_dmx object containing the current DMX values
 */
void dmx_display_update(Adafruit_SSD1306& dp, rgb_dmx dmx_val);

/**
 * Updates the OLED display with the current PDC values.
 *
 * @param dp: the reference to the Adafruit_SSD1306 object representing the OLED display
 * @param pdc_val: the pdc_page object containing the current PDC values
 */
void pdc_display_update(Adafruit_SSD1306& dp, pdc_page pdc_val);

/**
 * Displays that the EEPROM data has been saved.
 *
 * @param dp: the reference to the Adafruit_SSD1306 object representing the OLED display
 */
void display_saved_status(Adafruit_SSD1306& dp);

/**
 * Displays the startup message.
 *
 * @param dp: the reference to the Adafruit_SSD1306 object representing the OLED display
 */
void display_startup(Adafruit_SSD1306& dp);

#endif