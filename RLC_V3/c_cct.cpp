#include "c_cct.h"

c_cct::c_cct(uint16_t _kelvin, uint8_t _brightness) {
  kelvin = _kelvin;
  brightness = _brightness;
  current = CCT_KELVIN;
}

c_cct::~c_cct() {}

void c_cct::add_kelvin(int amount) {
  int32_t temp = kelvin + (amount * CCT_STEP_SIZE);
  if (temp > CCT_MAX_KELVIN) {
    kelvin = CCT_MAX_KELVIN;
  } else if (temp < CCT_MIN_KELVIN) {
    kelvin = CCT_MIN_KELVIN;
  } else {
    kelvin = temp;
  }
}

void c_cct::add_brightness(int amount) {
  int32_t temp = brightness + amount;
  if (temp > 255) {
    brightness = 255;
  } else if (temp < 0) {
    brightness = 0;
  } else {
    brightness = temp;
  }
}

uint16_t c_cct::get_kelvin() { return kelvin; }
uint8_t c_cct::get_brightness() { return brightness; }

void c_cct::set_kelvin(uint16_t _kelvin) { kelvin = _kelvin; }
void c_cct::set_brightness(uint8_t _brightness) { brightness = _brightness; }

uint8_t c_cct::get_current() { return current; }

void c_cct::set_current(uint8_t _current) {
  if (_current >= CCT_LAST) {
    current = CCT_LAST - 1;
  } else {
    current = _current;
  }
}

void c_cct::next() {
  current++;
  if (current >= CCT_LAST) {
    current = CCT_KELVIN;
  }
}
