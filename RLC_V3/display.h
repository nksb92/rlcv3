/**
 * @file display.h
 * @brief Header file for OLED display rendering functions.
 */

#include <stdint.h>
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "FreeSans7pt7b.h"
#include <Wire.h>

#include "common.h"
#include "dmx.h"
#include "segments.h"
#include "c_cct.h"
#include "c_grad.h"

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
 * @brief Initializes the OLED display with the specified parameters.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 */
void init_display(Adafruit_SSD1306& dp);

/**
 * @brief Updates the OLED display with the current HSV values.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] out_val C_HSV object containing the current HSV values.
 */
void hsv_display_update(Adafruit_SSD1306& dp, C_HSV out_val);

/**
 * @brief Updates the OLED display with the current RGB values.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] rgb_val C_RGB object containing the current RGB values.
 */
void rgb_display_update(Adafruit_SSD1306& dp, C_RGB rgb_val);

/**
 * @brief Updates the OLED display with the current CCT values.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] cct_val c_cct object containing the current CCT values.
 */
void cct_display_update(Adafruit_SSD1306& dp, c_cct cct_val);

/**
 * @brief Updates the OLED display with the current DMX values.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] dmx_val rgb_dmx object containing the current DMX values.
 */
void dmx_display_update(Adafruit_SSD1306& dp, rgb_dmx dmx_val);

/**
 * @brief Updates the OLED display with the settings menu.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] seg The current segment configuration object.
 * @param[in] setting_index Highlighted setting item index.
 * @param[in] current_deepness Current menu navigation depth.
 * @param[in] reset_confirm Level of reset confirmation (0 = normal, 1 = confirm).
 */
void settings_display_update(Adafruit_SSD1306& dp, segments seg, uint8_t setting_index, uint8_t current_deepness, uint8_t reset_confirm);

/**
 * @brief Updates the OLED display with the current Gradient values.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] grad_val C_GRAD object containing the current Gradient values.
 */
void grad_display_update(Adafruit_SSD1306& dp, C_GRAD grad_val);

/**
 * @brief Displays a message indicating that the configuration was successfully saved to EEPROM.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 */
void display_saved_status(Adafruit_SSD1306& dp);

/**
 * @brief Displays the startup splash screen.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 */
void display_startup(Adafruit_SSD1306& dp);

/**
 * @brief Renders the main navigation menu on the OLED.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] index Index of the currently highlighted menu page.
 */
void display_menu(Adafruit_SSD1306& dp, uint8_t index);

/**
 * @brief Renders the ArtNet receiver status page.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] artnet_var The ArtNet state object.
 * @param[in] menu_index Highlighted item index.
 */
void display_artnet_rec(Adafruit_SSD1306& dp, rlc_artnet artnet_var, uint8_t menu_index);

/**
 * @brief Performs screen text scrolling animations.
 */
void scroll();

/**
 * @brief Displays a connection status screen with loading indicator for ArtNet/WiFi.
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] artnet_var The ArtNet/WiFi state object.
 */
void display_connecting_artnet(Adafruit_SSD1306& dp, rlc_artnet artnet_var);

/**
 * @brief Draws menu navigation dots (filled for active position, hollow otherwise).
 * @param[in,out] dp Reference to the Adafruit_SSD1306 display object.
 * @param[in] n Total number of dots to draw.
 * @param[in] y_position Vertical placement of the dots on the screen.
 * @param[in] menu_pos Index of the active dot to be filled.
 */
void draw_circle_menu_orientation(Adafruit_SSD1306& dp, uint8_t n, uint8_t y_position, uint8_t menu_pos);

#endif