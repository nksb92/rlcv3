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
  if (_speed >= MIN_SPEED && _speed <= MAX_SPEED) {
    current_speed = _speed;
    ledcWrite(FAN_CHANNEL, _speed);
  }
}
