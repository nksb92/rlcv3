#include "fan_control.h"

fan_control::fan_control() {
}

fan_control::~fan_control() {
}

void fan_control::init_fan() {
  ledcSetup(FAN_CHANNEL, PWM_FAN_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PWM_PIN, FAN_CHANNEL);
  set_speed(MIN_SPEED);
}

void fan_control::set_speed(uint8_t _speed) {
  current_speed = _speed;
  ledcWrite(FAN_CHANNEL, _speed);
}

void fan_control::set_target_speed(uint8_t _target) {
  target_speed = _target;
}

void fan_control::update() {
  if (current_speed < target_speed) {
    set_speed(++current_speed);
  }

  if (current_speed > target_speed) {
    set_speed(--current_speed);
  }
}

void fan_control::calc_hsv_speed(C_HSV color) {
  uint8_t hue = color.get_hue();
  uint8_t sat = map(color.get_sat_p(), 0, 100, 0, 255);
  uint8_t val = map(color.get_val_p(), 0, 100, 0, 255);
  CHSV temp_hsv(hue, sat, val);
  CRGB temp_rgb;
  hsv2rgb_rainbow(temp_hsv, temp_rgb);
  calc_rgb_speed(temp_rgb);
}

void fan_control::calc_rgb_speed(CRGB color) {
  uint16_t sum = 0;
  sum += color.r + color.g + color.b;
  evaluate_sum(sum);
}

void fan_control::evaluate_sum(uint16_t _sum) {
  uint8_t fan_speed = MIN_SPEED;
  if (_sum >= LEVEL_ONE_FAN_TH) {
    fan_speed = LEVEL_TWO_FAN_SPEED;
  }
  if (_sum >= LEVEL_TWO_FAN_TH) {
    fan_speed = LEVEL_THREE_FAN_SPEED;
  }
  if (_sum >= LEVEL_THREE_FAN_TH) {
    fan_speed = LEVEL_FOUR_FAN_SPEED;
  }
  if (_sum >= LEVEL_FOUR_FAN_TH) {
    fan_speed = LEVEL_FIVE_FAN_SPEED;
  }
  if (_sum >= LEVEL_FIVE_FAN_TH) {
    fan_speed = LEVEL_SIX_FAN_SPEED;
  }
  target_speed = fan_speed;
}
