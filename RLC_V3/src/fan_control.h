#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include "common.h"

#define LEVEL_ONE_FAN_TH 128
#define LEVEL_TWO_FAN_TH 256
#define LEVEL_THREE_FAN_TH 384
#define LEVEL_FOUR_FAN_TH 512
#define LEVEL_FIVE_FAN_TH 640

#define LEVEL_TWO_FAN_SPEED 100
#define LEVEL_THREE_FAN_SPEED 125
#define LEVEL_FOUR_FAN_SPEED 175
#define LEVEL_FIVE_FAN_SPEED 200
#define LEVEL_SIX_FAN_SPEED MAX_SPEED

class fan_control
{
private:
  uint8_t current_speed = MIN_SPEED;
  uint8_t target_speed = MIN_SPEED;

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