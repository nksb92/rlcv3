/**
 * @file c_rgb.h
 * @brief Header file for the RGB color space control class.
 */

#if !defined(C_RGB_H)
#define C_RGB_H

#include <Arduino.h>

#define FASTLED_RMT_BUILTIN 0
#define FASTLED_ESP32_I2S 1
#include <FastLED.h>

/**
 * @brief Enum defining menu items for RGB mode.
 */
enum {
  RED,      /**< Red component adjustment mode. */
  GREEN,    /**< Green component adjustment mode. */
  BLUE,     /**< Blue component adjustment mode. */
  RGB_LAST  /**< Sentinel for boundaries. */
};

/**
 * @class C_RGB
 * @brief Manages lighting parameters in the RGB color space.
 */
class C_RGB {
  CRGB rgb_color;          /**< FastLED CRGB color representation. */
  uint8_t current = RED;   /**< Currently active color channel mode. */

 public:
  /**
   * @brief Constructor for C_RGB.
   * @param[in] red Initial red intensity (0-255).
   * @param[in] green Initial green intensity (0-255).
   * @param[in] blue Initial blue intensity (0-255).
   */
  C_RGB(uint8_t red, uint8_t green, uint8_t blue);

  /**
   * @brief Sets the currently active color channel.
   * @param[in] value The channel index (RED, GREEN, or BLUE).
   */
  void set_current(uint8_t value);

  /**
   * @brief Cycles to the next color channel (RED -> GREEN -> BLUE -> RED).
   */
  void next();

  /**
   * @brief Gets the currently active color channel.
   * @return The active channel index.
   */
  uint8_t get_current();

  /**
   * @brief Sets the red color intensity directly.
   * @param[in] value The red intensity (0-255).
   */
  void set_red(uint8_t value);

  /**
   * @brief Adds a relative value to the red color intensity.
   * Clamps the result between 0 and 255.
   * @param[in] value The adjustment value.
   */
  void add_red(int value);

  /**
   * @brief Gets the current red intensity.
   * @return The red value (0-255).
   */
  uint8_t get_red();

  /**
   * @brief Sets the green color intensity directly.
   * @param[in] value The green intensity (0-255).
   */
  void set_green(uint8_t value);

  /**
   * @brief Adds a relative value to the green color intensity.
   * Clamps the result between 0 and 255.
   * @param[in] value The adjustment value.
   */
  void add_green(int value);

  /**
   * @brief Gets the current green intensity.
   * @return The green value (0-255).
   */
  uint8_t get_green();

  /**
   * @brief Sets the blue color intensity directly.
   * @param[in] value The blue intensity (0-255).
   */
  void set_blue(uint8_t value);

  /**
   * @brief Adds a relative value to the blue color intensity.
   * Clamps the result between 0 and 255.
   * @param[in] value The adjustment value.
   */
  void add_blue(int value);

  /**
   * @brief Gets the current blue intensity.
   * @return The blue value (0-255).
   */
  uint8_t get_blue();

  /**
   * @brief Sets all RGB components directly.
   * @param[in] rgb_value FastLED CRGB color.
   */
  void set_rgb(CRGB rgb_value);

  /**
   * @brief Gets all RGB components as a FastLED CRGB color.
   * @return The color object.
   */
  CRGB get_rgb();
};

#endif  // C_RGB_H
