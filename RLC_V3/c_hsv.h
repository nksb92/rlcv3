/**
 * @file c_hsv.h
 * @brief Header file for the HSV (Hue, Saturation, Value) color space control class.
 */

#if !defined(C_HSV_H)
#define C_HSV_H

#include <Arduino.h>

/**
 * @brief Enum defining active parameter modes for HSV.
 */
enum {
  HUE,      /**< Hue adjustment mode. */
  SAT,      /**< Saturation adjustment mode. */
  VAL,      /**< Value/brightness adjustment mode. */
  HSV_LAST  /**< Sentinel for boundaries. */
};

/**
 * @class C_HSV
 * @brief Manages lighting parameters in the HSV color space.
 */
class C_HSV {
  uint8_t hue;  /**< The hue value between 0 and 255 (in 360/255 steps). */
  uint8_t sat;  /**< The saturation value between 0 and MAX_VALUE_SAT_VAL. */
  uint8_t val;  /**< The value/brightness value between 0 and MAX_VALUE_SAT_VAL. */

  uint8_t current = HUE;  /**< The current mode, initialized to HUE. */

 public:
  /**
   * @brief Constructor that takes the hue, saturation, and value as arguments.
   * @param[in] _hue The hue value between 0 and 255 (in 360/255 steps).
   * @param[in] _sat The saturation value between 0 and MAX_VALUE_SAT_VAL.
   * @param[in] _val The value/brightness value between 0 and MAX_VALUE_SAT_VAL.
   */
  C_HSV(uint8_t _hue, uint8_t _sat, uint8_t _val);

  /**
   * @brief Adds an amount to the current hue value.
   * @param[in] amount The amount to add.
   */
  void add_hue(int amount);

  /**
   * @brief Adds an amount to the current saturation value.
   * Clamps the result between 0 and MAX_VALUE_SAT_VAL.
   * @param[in] amount The amount to add.
   */
  void add_sat(int amount);

  /**
   * @brief Adds an amount to the current value/brightness value.
   * Clamps the result between 0 and MAX_VALUE_SAT_VAL.
   * @param[in] amount The amount to add.
   */
  void add_val(int amount);

  /**
   * @brief Returns the current hue value.
   * @return The hue value between 0 and 255.
   */
  uint8_t get_hue();

  /**
   * @brief Returns the current saturation value.
   * @return The saturation value.
   */
  uint8_t get_sat();

  /**
   * @brief Returns the current value/brightness value.
   * @return The value/brightness value.
   */
  uint8_t get_val();

  /**
   * @brief Sets the value/brightness directly, clamping it within range.
   * @param[in] value The brightness value.
   */
  void set_val(uint8_t value);

  /**
   * @brief Sets the saturation directly, clamping it within range.
   * @param[in] value The saturation value.
   */
  void set_sat(uint8_t value);

  /**
   * @brief Sets the hue to the given value in 360/255 steps.
   * @param[in] value The hue byte value to set.
   */
  void set_hue_byte(uint8_t value);

  /**
   * @brief Returns the current mode index.
   * @return The current mode.
   */
  uint8_t get_current();

  /**
   * @brief Sets the current mode index.
   * @param[in] _current The mode index to set.
   */
  void set_current(uint8_t _current);

  /**
   * @brief Sets the current mode to HUE.
   */
  void set_hue();

  /**
   * @brief Sets the current mode to SAT.
   */
  void set_sat();

  /**
   * @brief Sets the current mode to VAL.
   */
  void set_val();

  /**
   * @brief Cycles to the next mode (HUE -> SAT -> VAL -> HUE).
   */
  void next();
};

#endif  // C_HSV_H
