#include "fan_control.h"

#define STEP_UP 5    // Ramp Up Time:   255 * 150 ms / 5 = 7,65 s
#define STEP_DOWN 1  // Ramp Down Time: 255 * 150 ms / 1 = 38,25 s

fan_control::fan_control() {
}

fan_control::~fan_control() {
}

void fan_control::init_fan() {
  pinMode(PWM_PIN, OUTPUT);
  analogWriteFrequency(PWM_PIN, PWM_FAN_FREQ);

  set_speed(FAN_MIN_SPEED);
}

void fan_control::set_speed(uint8_t _speed) {
  // check FAN_MIN_SPEED and FAN_ZERO_RPM mode
  // if target speed is smaller (or equal) than FAN_MIN_SPEED and FAN_ZERO_RPM is true
  // set fan to off
  if (_speed <= FAN_MIN_SPEED) {
    if (FAN_ZERO_RPM) {
      _speed = 0;
    } else {
      _speed = FAN_MIN_SPEED;
    }
  }

  analogWrite(PWM_PIN, _speed);
}

void fan_control::set_target_speed(uint8_t _target) {
  target_speed = _target;
}

void fan_control::update() {
  if (current_speed < target_speed) {
    if (target_speed - current_speed < STEP_UP) {
      current_speed = target_speed;
    } else {
      current_speed += STEP_UP;
    }
    set_speed(current_speed);
  }

  if (current_speed > target_speed) {
    if (current_speed - target_speed < STEP_DOWN) {
      current_speed = target_speed;
    } else {
      current_speed -= STEP_DOWN;
    }
    set_speed(current_speed);
  }
}

void fan_control::calc_hsv_speed(C_HSV color) {
  uint8_t hue = 0;
  uint8_t sat = 0;
  uint8_t val = 0;

  hue = color.get_hue();

#if defined(PERCENTAGE)
  sat = map(color.get_sat(), 0, 100, 0, 255);
  val = map(color.get_val(), 0, 100, 0, 255);
#endif

#if defined(FULL_RANGE)
  sat = color.get_sat();
  val = color.get_val();
#endif
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
  uint8_t fan_speed = FAN_MIN_SPEED;

  // set fan target to values between 0 and FAN_MAX_SPEED
  // FAN_MIN_SPEED is not used to check for FAN_ZERO_RPM mode
  // in function set_speed()
  fan_speed = map(_sum, 0, 765, FAN_MIN_SPEED, FAN_MAX_SPEED);

  set_target_speed(fan_speed);
}
