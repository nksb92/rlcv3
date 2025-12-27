#include "menu_structure.h"

menu_structure::menu_structure(/* args */) {
}

menu_structure::~menu_structure() {
}

void menu_structure::init() {
  // if (CURRENT_MODE == RGB) last_menu = MENU_LAST_PAGE - 1;
}

/**
 * Returns the current mode.
 */
uint8_t menu_structure::get_current() {
  return current;
}

uint8_t menu_structure::get_deepness() {
  return deepness;
}

/**
 * Sets the current mode to the given mode. If the given mode is greater than or equal to the total number of modes,
 * sets the mode to the last available mode.
 * @param _current: The mode to set the current mode to.
 */
void menu_structure::set_current(uint8_t _current) {
  if (_current >= MENU_LAST_PAGE) {
    current = MENU_LAST_PAGE - 1;
  } else {
    current = _current;
  }
}

void menu_structure::set_deepness(uint8_t _deepness) {
  if (_deepness >= MAX_DEEP) {
    deepness = MAX_DEEP - 1;
  } else {
    deepness = _deepness;
  }
}

void menu_structure::add_current(int val) {
  int temp = 0;
  if (val > 0) {
    temp = current + 1;
  } else {
    temp = current - 1;
  }

  if (temp >= last_menu) {
    current = MENU_LAST_PAGE - 1;
  } else if (temp < 0) {
    current = HSV_PAGE;
  } else {
    current = temp;
  }
}

void menu_structure::deeper() {
  deepness++;
  if (deepness >= MAX_DEEP) {
    deepness = MAIN_MENU;
  }
}