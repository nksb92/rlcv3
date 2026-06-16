/**
 * @file c_cct.h
 * @brief Header file for the Correlated Color Temperature (CCT) control class.
 */

#if !defined(C_CCT_H)
#define C_CCT_H

#include <Arduino.h>
#include "config.h"

/**
 * @brief Enum defining menu items for CCT mode.
 */
enum {
  CCT_KELVIN,     /**< Kelvin temperature setting. */
  CCT_BRIGHTNESS, /**< Brightness level setting. */
  CCT_LAST        /**< Sentinel for boundaries. */
};

/**
 * @class c_cct
 * @brief Manages CCT lighting parameters, including Kelvin temperature and brightness.
 */
class c_cct {
 private:
  uint16_t kelvin;     /**< Color temperature in Kelvin. */
  uint8_t brightness;  /**< Brightness level (0-100 or 0-255). */
  uint8_t current;     /**< Current active sub-item/mode. */

 public:
  /**
   * @brief Constructor for c_cct.
   * @param[in] _kelvin Initial Kelvin temperature value.
   * @param[in] _brightness Initial brightness value.
   */
  c_cct(uint16_t _kelvin = (CCT_MIN_KELVIN + (((CCT_MAX_KELVIN - CCT_MIN_KELVIN) / 2) / CCT_STEP_SIZE) * CCT_STEP_SIZE), uint8_t _brightness = 100);
  
  /**
   * @brief Destructor for c_cct.
   */
  ~c_cct();

  /**
   * @brief Adds a relative amount to the Kelvin temperature.
   * @param[in] amount The amount of steps to add (multiplied by CCT_STEP_SIZE).
   */
  void add_kelvin(int amount);

  /**
   * @brief Adds a relative amount to the brightness.
   * @param[in] amount The amount to add.
   */
  void add_brightness(int amount);

  /**
   * @brief Gets the current color temperature in Kelvin.
   * @return The temperature in Kelvin.
   */
  uint16_t get_kelvin();

  /**
   * @brief Gets the current brightness.
   * @return The brightness value.
   */
  uint8_t get_brightness();

  /**
   * @brief Sets the color temperature in Kelvin directly.
   * @param[in] _kelvin The temperature in Kelvin.
   */
  void set_kelvin(uint16_t _kelvin);

  /**
   * @brief Sets the brightness level directly.
   * @param[in] _brightness The brightness value.
   */
  void set_brightness(uint8_t _brightness);

  /**
   * @brief Gets the currently selected sub-mode (Kelvin or Brightness).
   * @return The active mode index.
   */
  uint8_t get_current();

  /**
   * @brief Sets the currently selected sub-mode.
   * @param[in] _current The mode index to set.
   */
  void set_current(uint8_t _current);

  /**
   * @brief Cycles to the next sub-mode.
   */
  void next();
};

#endif // C_CCT_H
