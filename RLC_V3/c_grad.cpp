/**
 * @file c_grad.cpp
 * @brief Implementation of the gradient color control class.
 */

#include "c_grad.h"
#include "segments.h"

extern segments seg;
#define MAX_VALUE_SAT_VAL (seg.get_value_mode() == VALUE_PERCENTAGE ? 100 : 255)

C_GRAD::C_GRAD(uint8_t _sh, uint8_t _ss, uint8_t _sv, uint8_t _eh, uint8_t _es, uint8_t _ev) {
  start_hue = _sh;
  start_sat = _ss;
  start_val = _sv;
  end_hue = _eh;
  end_sat = _es;
  end_val = _ev;
  dimmer = MAX_VALUE_SAT_VAL;
  current_menu_item = GRAD_START_HUE;
  current_deepness = GRAD_ITEM_SELECTION;
}

C_GRAD::~C_GRAD() {}

void C_GRAD::add_setting(int value) {
  if (value != 0) {
    if (value < 0) {
      if (current_menu_item - 1 >= 0) {
        current_menu_item--;
      } else {
        current_menu_item = GRAD_START_HUE; // don't wrap around or wrap if you want, let's stop at ends
      }
    } else {
      if (current_menu_item + 1 < GRAD_LAST) {
        current_menu_item++;
      } else {
        current_menu_item = GRAD_LAST - 1;
      }
    }
  }
}

void C_GRAD::deeper() {
  if (++current_deepness > GRAD_VALUE_SELECTION) {
    current_deepness = GRAD_ITEM_SELECTION;
  }
}

uint8_t C_GRAD::get_deepness() {
  return current_deepness;
}

uint8_t C_GRAD::get_item() {
  return current_menu_item;
}

void C_GRAD::add_value(int amount) {
  if (amount == 0) return;

  switch (current_menu_item) {
    case GRAD_START_HUE:
      start_hue += amount; // Wraps naturally 0-255
      break;
    case GRAD_START_SAT: {
      int temp = start_sat + amount;
      if (temp > MAX_VALUE_SAT_VAL) temp = MAX_VALUE_SAT_VAL;
      if (temp < 0) temp = 0;
      start_sat = temp;
      break;
    }
    case GRAD_START_VAL: {
      int temp = start_val + amount;
      if (temp > MAX_VALUE_SAT_VAL) temp = MAX_VALUE_SAT_VAL;
      if (temp < 0) temp = 0;
      start_val = temp;
      break;
    }
    case GRAD_END_HUE:
      end_hue += amount; // Wraps naturally 0-255
      break;
    case GRAD_END_SAT: {
      int temp = end_sat + amount;
      if (temp > MAX_VALUE_SAT_VAL) temp = MAX_VALUE_SAT_VAL;
      if (temp < 0) temp = 0;
      end_sat = temp;
      break;
    }
    case GRAD_END_VAL: {
      int temp = end_val + amount;
      if (temp > MAX_VALUE_SAT_VAL) temp = MAX_VALUE_SAT_VAL;
      if (temp < 0) temp = 0;
      end_val = temp;
      break;
    }
    case GRAD_DIMMER: {
      int temp = dimmer + amount;
      if (temp > MAX_VALUE_SAT_VAL) temp = MAX_VALUE_SAT_VAL;
      if (temp < 0) temp = 0;
      dimmer = temp;
      break;
    }
  }
}

uint8_t C_GRAD::get_start_hue() { return start_hue; }
uint8_t C_GRAD::get_start_sat() { return start_sat; }
uint8_t C_GRAD::get_start_val() { return start_val; }
uint8_t C_GRAD::get_end_hue() { return end_hue; }
uint8_t C_GRAD::get_end_sat() { return end_sat; }
uint8_t C_GRAD::get_end_val() { return end_val; }
uint8_t C_GRAD::get_dimmer() { return dimmer; }

void C_GRAD::set_start_hue(uint8_t value) { start_hue = value; }
void C_GRAD::set_start_sat(uint8_t value) { start_sat = value > MAX_VALUE_SAT_VAL ? MAX_VALUE_SAT_VAL : value; }
void C_GRAD::set_start_val(uint8_t value) { start_val = value > MAX_VALUE_SAT_VAL ? MAX_VALUE_SAT_VAL : value; }
void C_GRAD::set_end_hue(uint8_t value) { end_hue = value; }
void C_GRAD::set_end_sat(uint8_t value) { end_sat = value > MAX_VALUE_SAT_VAL ? MAX_VALUE_SAT_VAL : value; }
void C_GRAD::set_end_val(uint8_t value) { end_val = value > MAX_VALUE_SAT_VAL ? MAX_VALUE_SAT_VAL : value; }
void C_GRAD::set_dimmer(uint8_t value) { dimmer = value > MAX_VALUE_SAT_VAL ? MAX_VALUE_SAT_VAL : value; }
