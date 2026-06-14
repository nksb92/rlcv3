#if !defined(SETTINGS_MENU_H)
#define SETTINGS_MENU_H

#include <Arduino.h>
// #include "common.h"

enum {
  SEGMENTS,
  DIMMER_OPTION,
  WHITE_OPTION,
  VALUE_MODE_OPTION,
  RESET_OPTION,
  FIRMWARE,
  LAST_SETTING
};

enum {
  ITEM_SELECTION,
  VALUE_SELECTION
};

class settings_menu {
 private:
  /* data */
  uint8_t current_menu_item = SEGMENTS;
  uint8_t current_deepness = ITEM_SELECTION;
  uint8_t reset_confirm = 0; // 0 = NO, 1 = YES

 public:
  settings_menu(/* args */);
  ~settings_menu();

  void add_setting(int value);
  void deeper();

  uint8_t get_deepness();
  uint8_t get_item();

  uint8_t get_reset_confirm();
  void add_reset_confirm(int value);
  void clear_reset_confirm();
};

#endif  // SETTINGS_MENU_H
