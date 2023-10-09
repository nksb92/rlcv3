#include "pdc.h"

pdc_page::pdc_page(uint8_t crnt)
  : white_color(255, 200, 190),
    warm_white(255, 138, 18),
    cyan(0, 255, 190),
    pink(255, 0, 65),
    green(0, 255, 0),
    pink_two(255, 0, 255),
    orange(255, 175, 0),
    blue(0, 80, 255),
    purple(120, 0, 255),
    lime(136, 255, 0),
    pdc_names({
      "WHITE",
      "WHITE-2",
      "CYAN",
      "PINK",
      "GREEN",
      "PINK-2",
      "ORANGE",
      "BLUE",
      "PURPLE",
      "LIME",
    }),
    predefined_colors({
      white_color,
      warm_white,
      cyan,
      pink,
      green,
      pink_two,
      orange,
      blue,
      purple,
      lime,
    }) {
  current = crnt;
}

void pdc_page::set_current(uint8_t crnt) {
  current = crnt;
}

uint8_t pdc_page::get_current(){
  return current;
}

void pdc_page::next() {
  current++;
  if (current >= pdc_nmbr) {
    set_current(0);
  }
}

CRGB pdc_page::get_current_color() {
  return predefined_colors[current];
}

char* pdc_page::get_current_name() {
  return pdc_names[current];
}

void pdc_page::add_bright(int val) {
  if (brightness_p + val >= 100) {
    brightness_p = 100;
  } else if (brightness_p + val <= 0) {
    brightness_p = 0;
  } else {
    brightness_p += val;
  }
}

void pdc_page::set_bright(int value){
  brightness_p = 0;
  add_bright(value);
}

uint8_t pdc_page::get_bright() {
  return brightness_p;
}