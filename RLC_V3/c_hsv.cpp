/**
 * @file c_hsv.cpp
 * @brief Implementation of the HSV color space control class.
 */

#include "c_hsv.h"
#include "segments.h"

extern segments seg;
#define MAX_VALUE_SAT_VAL (seg.get_value_mode() == VALUE_PERCENTAGE ? 100 : 255)

C_HSV::C_HSV(uint8_t _hue, uint8_t _sat, uint8_t _val) {
  hue = _hue;
  sat = _sat;
  val = _val;
}

void C_HSV::add_hue(int amount) {
  hue += amount;
}

void C_HSV::add_sat(int amount) {
  if (sat + amount > MAX_VALUE_SAT_VAL) {
    sat = MAX_VALUE_SAT_VAL;
  } else if (sat + amount <= 0) {
    sat = 0;
  } else {
    sat += amount;
  }
}

void C_HSV::add_val(int amount) {
  if (val + amount > MAX_VALUE_SAT_VAL) {
    val = MAX_VALUE_SAT_VAL;
  } else if (val + amount <= 0) {
    val = 0;
  } else {
    val += amount;
  }
}

uint8_t C_HSV::get_hue() {
  return hue;
}

uint8_t C_HSV::get_sat() {
  return sat;
}

uint8_t C_HSV::get_val() {
  return val;
}

void C_HSV::set_val(uint8_t value) {
  val = 0;
  add_val(value);
}

void C_HSV::set_sat(uint8_t value) {
  sat = 0;
  add_sat(value);
}

void C_HSV::set_hue_byte(uint8_t value) {
  hue = value;
}

uint8_t C_HSV::get_current() {
  return current;
}

void C_HSV::set_current(uint8_t _current) {
  if (_current >= HSV_LAST) {
    current = HSV_LAST - 1;
  } else {
    current = _current;
  }
}

void C_HSV::set_hue() {
  current = HUE;
}

void C_HSV::set_sat() {
  current = SAT;
}

void C_HSV::set_val() {
  current = VAL;
}

void C_HSV::next() {
  current++;
  if (current >= HSV_LAST) {
    set_hue();
  }
}