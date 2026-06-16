/**
 * @file fan_control.h
 * @brief Header file for cooling fan control.
 */

#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include "common.h"

/**
 * @class fan_control
 * @brief Regulates cooling fan speed based on active LED thermal/power load.
 */
class fan_control {
 private:
  uint8_t current_speed = FAN_MIN_SPEED; /**< Current 8-bit PWM speed. */
  uint8_t target_speed = FAN_MIN_SPEED;  /**< Target 8-bit PWM speed. */

 public:
  /**
   * @brief Constructor for fan_control.
   */
  fan_control();

  /**
   * @brief Destructor for fan_control.
   */
  ~fan_control();

  /**
   * @brief Initializes the fan PWM output pins and frequency.
   */
  void init_fan();

  /**
   * @brief Directly sets the fan speed, respecting clamps and zero-RPM config.
   * @param[in] _speed Raw speed value (0-255).
   */
  void set_speed(uint8_t _speed);

  /**
   * @brief Sets the target speed for the ramping controller.
   * @param[in] _target Target speed value (0-255).
   */
  void set_target_speed(uint8_t _target);

  /**
   * @brief Ramps the fan speed towards the target speed based on step settings.
   */
  void update();

  /**
   * @brief Calculates target fan speed based on an HSV color.
   * @param[in] color HSV color value.
   */
  void calc_hsv_speed(C_HSV color);

  /**
   * @brief Calculates target fan speed based on an RGB color.
   * @param[in] color RGB color value.
   */
  void calc_rgb_speed(CRGB color);

  /**
   * @brief Evaluates the total sum of LED channel loads to determine cooling needs.
   * @param[in] _sum Sum of R+G+B intensities (0 to 765).
   */
  void evaluate_sum(uint16_t _sum);
};

#endif