#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <FastLED.h>
#include "rlc_artnet.h"

#define STD_HUE 0
#define STD_SAT_P 100
#define STD_VAL_P 100
#define STD_RED 128
#define STD_GREEN 0
#define STD_BLUE 128
#define STD_CURRENT 0
#define STD_DEEPNESS 0
#define STD_SEGMENTS 1
#define STD_START_ADDRESS 1
#define STD_UNIVERSE 0
#define NUM_PIXEL 144

/**
* An enum to define the possible hsv modes.
*/
enum {
  HUE,
  SAT,
  VAL,
  HSV_LAST
};

class C_HSV {
  uint8_t hue;    // The hue value between 0 and 255 (in 360/255 steps).
  uint8_t sat_p;  // The saturation value between 0 and 100 (as a percentage).
  uint8_t val_p;  // The value/brightness value between 0 and 100 (as a percentage).

  uint8_t current = HUE;  // The current mode, initialized to HUE.

public:
  /**
  * Constructor that takes the hue, saturation, and value as arguments.
  * @param _hue: The hue value between 0 and 255 (in 360/255 steps).
  * @param _sat_p: The saturation value between 0 and 100 (as a percentage).
  * @param _val_p: The value/brightness value between 0 and 100 (as a percentage).
  */
  C_HSV(uint8_t _hue, uint8_t _sat_p, uint8_t _val_p) {
    hue = _hue;
    sat_p = _sat_p;
    val_p = _val_p;
  }

  /**
  * Adds an amount to the current hue value.
  * @param amount: The amount to add.
  */
  void add_hue(int amount) {
    hue += amount;
  }

  /**
  * Adds an amount to the current saturation value.
  * If the result is greater than 100 or less than 0, it is clamped to the maximum or minimum value, respectively.
  * @param amount: The amount to add.
  */
  void add_sat(int amount) {
    if (sat_p + amount > 100) sat_p = 100;
    else if (sat_p + amount <= 0) sat_p = 0;
    else sat_p += amount;
  }

  /**
  * Adds an amount to the current value/brightness value.
  * If the result is greater than 100 or less than 0, it is clamped to the maximum or minimum value, respectively.
  * @param amount: The amount to add.
  */
  void add_val(int amount) {
    if (val_p + amount > 100) val_p = 100;
    else if (val_p + amount <= 0) val_p = 0;
    else val_p += amount;
  }

  /**
  * Returns the current hue value.
  * @return The hue value between 0 and 255 (in 360/255 steps).
  */
  uint8_t get_hue() {
    return hue;
  }

  /**
  * Returns the current saturation value.
  * @return The saturation value between 0 and 100 (as a percentage).
  */
  uint8_t get_sat_p() {
    return sat_p;
  }

  /**
  * Returns the current value/brightness value.
  * @return The value/brightness value between 0 and 100 (as a percentage).
  */
  uint8_t get_val_p() {
    return val_p;
  }

  /**
  * Sets the value/brightness value to the given value, clamping it to the maximum or minimum value if necessary.
  * @param value: The value to set the value/brightness to.
  */
  void set_val_p(uint8_t value) {
    val_p = 0;
    add_val(value);
  }

  /**
  * Sets the value/brightness value to the given value, clamping it to the maximum or minimum value if necessary.
  * @param value: The value to set the value/brightness to.
  */
  void set_sat_p(uint8_t value) {
    sat_p = 0;
    add_sat(value);
  }

  /**
  * Sets the hue to the given value in 360/255 steps.
  * @param value: The hue value to set.
  */
  void set_hue_byte(uint8_t value) {
    hue = value;
  }

  /**
  * Returns the current mode.
  * @return The current mode.
  */
  uint8_t get_current() {
    return current;
  }

  /**
  * Sets the current mode to the given mode. If the given mode is greater than or equal to the total number of modes,
  * sets the mode to the last available mode.
  * @param _current: The mode to set the current mode to.
  */
  void set_current(uint8_t _current) {
    if (_current >= HSV_LAST) {
      current = HSV_LAST - 1;
    } else {
      current = _current;
    }
  }

  /**
  * Sets the current mode to HUE.
  */
  void set_hue() {
    current = HUE;
  }

  /**
  * Sets the current mode to SAT.
  */
  void set_sat() {
    current = SAT;
  }

  /**
  * Sets the current mode to VAL.
  */
  void set_val() {
    current = VAL;
  }

  /**
  * Sets the current mode to the next mode in the enum.
  * If the current mode is the last one, sets it to HUE.
  */
  void next() {
    current++;
    if (current >= HSV_LAST) {
      set_hue();
    }
  }
};

/**
* An enum to define the possible main modes.
*/
enum {
  HSV_PAGE,
  RGB_PAGE,
  DMX_PAGE,
  ARTNET_NODE,
  ARTNET_REC,
  SEGMENT_CNTRL,
  MAIN_LAST
};

enum {
  MAIN_MENU,
  SUB_MENU,
  MAX_DEEP
};

/**
* A class to control the current main mode.
*/
class main {
  uint8_t current = HSV_PAGE;
  uint8_t deepness = MAIN_MENU;

public:
  /**
  * Returns the current mode.
  */
  uint8_t get_current() {
    return current;
  }

  uint8_t get_deepness() {
    return deepness;
  }

  /**
  * Sets the current mode to the given mode. If the given mode is greater than or equal to the total number of modes,
  * sets the mode to the last available mode.
  * @param _current: The mode to set the current mode to.
  */
  void set_current(uint8_t _current) {
    if (_current >= MAIN_LAST) {
      current = MAIN_LAST - 1;
    } else {
      current = _current;
    }
  }

  void set_deepness(uint8_t _deepness) {
    if (_deepness >= MAX_DEEP) {
      deepness = MAX_DEEP - 1;
    } else {
      deepness = _deepness;
    }
  }

  void add_current(int val) {
    int temp = current + val;
    if (temp >= MAIN_LAST) {
      current = HSV_PAGE;
    } else if (temp < 0) {
      current = MAIN_LAST - 1;
    } else {
      current = temp;
    }
  }

  void deeper() {
    deepness++;
    if (deepness >= MAX_DEEP) {
      deepness = 0;
    }
  }
};

enum {
  RED,
  GREEN,
  BLUE,
  RGB_LAST
};

class C_RGB {
  CRGB rgb_color;
  uint8_t current = RED;

public:
  C_RGB(uint8_t red, uint8_t green, uint8_t blue) {
    rgb_color.r = red;
    rgb_color.g = green;
    rgb_color.b = blue;
  }

  void set_current(uint8_t value) {
    current = value;
  }

  void next() {
    current++;
    if (current >= RGB_LAST) {
      current = RED;
    }
  }

  uint8_t get_current() {
    return current;
  }

  void set_red(uint8_t value) {
    rgb_color.r = value;
  }

  void add_red(int value) {
    rgb_color.r += value;
  }

  uint8_t get_red() {
    return rgb_color.r;
  }

  void set_green(uint8_t value) {
    rgb_color.g = value;
  }

  void add_green(int value) {
    rgb_color.g += value;
  }

  uint8_t get_green() {
    return rgb_color.g;
  }

  void set_blue(uint8_t value) {
    rgb_color.b = value;
  }

  void add_blue(int value) {
    rgb_color.b += value;
  }

  uint8_t get_blue() {
    return rgb_color.b;
  }

  void set_rgb(CRGB rgb_value) {
    rgb_color = rgb_value;
  }

  CRGB get_rgb() {
    return rgb_color;
  }
};
#endif