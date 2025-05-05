#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include "common.h"

class fan_control
{
private:
  uint8_t current_speed = FAN_MIN_SPEED;
  uint8_t target_speed = FAN_MIN_SPEED;

public:
  fan_control();
  ~fan_control();
  void init_fan();
  void set_speed(uint8_t _speed);
  void set_target_speed(uint8_t _target);
  void update();
  void calc_hsv_speed(C_HSV color);
  void calc_rgb_speed(CRGB color);
  void evaluate_sum(uint16_t _sum);
};

#endif