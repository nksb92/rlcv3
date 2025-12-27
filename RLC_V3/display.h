#include <stdint.h>
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Wire.h>

#include "common.h"
#include "dmx.h"
#include "segments.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define ROTATION_0 0
#define ROTATION_90 1
#define ROTATION_180 2
#define ROTATION_270 3

#define FRAME_DELAY 20
#define STARTUP_TIME 1500

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

void settings_display_update(Adafruit_SSD1306& dp, segments seg, uint8_t setting_index, uint8_t current_deepness);

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

/// @brief displays the main menu on the OLED display
/// @param dp the reference to the Adafruit_SSD1306 object representing the OLED display
/// @param index the index of the current selected menu item
void display_menu(Adafruit_SSD1306& dp, uint8_t index);

/// @brief displays the artnet receive page
/// @param dp the reference to the Adafruit_SSD1306 object representing the OLED display
/// @param artnet_var the rlc_artnet object containing the current artnet state
/// @param menu_index the index of the current selected menu item
void display_artnet_rec(Adafruit_SSD1306& dp, rlc_artnet artnet_var, uint8_t menu_index);

/// @brief scrolls the text on the OLED display
void scroll();

/// @brief displays the connecting artnet screen with a loading animation
/// @param dp the reference to the Adafruit_SSD1306 object representing the OLED display
/// @param artnet_var the rlc_artnet object containing the current artnet state
void display_connecting_artnet(Adafruit_SSD1306& dp, rlc_artnet artnet_var);

/// @brief draws amount n of hollow circles, fills the circle at menu_pos
/// @param dp the reference to the Adafruit_SSD1306 object representing the OLED display
/// @param n the number of circles to draw
/// @param y_position the y position of the circles
/// @param menu_pos the index of the current selected menu item for filling the circle
void draw_circle_menu_orientation(Adafruit_SSD1306& dp, uint8_t n, uint8_t y_position, uint8_t menu_pos);

#endif