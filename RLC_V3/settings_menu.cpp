#include "settings_menu.h"

settings_menu::settings_menu() {
  current_menu_item = SEGMENTS;
}

settings_menu::~settings_menu() {
}

void settings_menu::add_setting(int value) {
  if (value != 0) {
    if (value < 0) {
      if (current_menu_item - 1 >= 0) {
        current_menu_item--;
      } else {
        current_menu_item = SEGMENTS;
      }
    } else {
      if (current_menu_item + 1 < LAST_SETTING) {
        current_menu_item++;
      } else {
        current_menu_item = LAST_SETTING - 1;
      }
    }
  }
}

void settings_menu::deeper() {
  if (++current_deepness > VALUE_SELECTION) {
    current_deepness = ITEM_SELECTION;
  }
}

uint8_t settings_menu::get_deepness() {
  return current_deepness;
}

uint8_t settings_menu::get_item() {
  return current_menu_item;
}