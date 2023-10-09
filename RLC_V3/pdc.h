#ifndef PDC_H
#define PDC_H

#include "common.h"

class pdc_page {
  // current: the index of the current color being used
  uint8_t current = STD_CURRENT;

  // brightness_p: the brightness percentage of the LEDs
  uint8_t brightness_p = STD_BRIGHTNESS_PDC;

  // pdc_nmbr: the number of predefined colors
  static const uint8_t pdc_nmbr = 10;

  // white_color: a predefined color object with RGB values for white
  CRGB white_color;

  // warm_white: a predefined color object with RGB values for warm white
  CRGB warm_white;

  // cyan: a predefined color object with RGB values for cyan
  CRGB cyan;

  // pink: a predefined color object with RGB values for pink
  CRGB pink;

  // green: a predefined color object with RGB values for green
  CRGB green;

  // pink_two: a predefined color object with RGB values for magenta
  CRGB pink_two;

  // orange: a predefined color object with RGB values for orange
  CRGB orange;

  // blue: a predefined color object with RGB values for blue
  CRGB blue;

  // purple: a predefined color object with RGB values for purple
  CRGB purple;

  // lime: a predefined color object with RGB values for lime
  CRGB lime;

  // pdc_names: an array of strings containing the names of the predefined colors
  char* pdc_names[pdc_nmbr];

  // predefined_colors: an array of CRGB objects containing the predefined colors
  CRGB predefined_colors[pdc_nmbr];

public:
  /**
  * Constructor for the PDC page
  * @param crnt: Current color index
  */
  pdc_page(uint8_t crnt);

  /**
  * Set the current color index
  * @param crnt: Current color index
  */
  void set_current(uint8_t crnt);

  /**
  * Gets the current color index
  * @return uint8_t value of the current index
  */
  uint8_t get_current();

  /**
  * Move to the next color index
  */
  void next();

  /**
  * Get the current color in CRGB format
  * @return CRGB color value
  */
  CRGB get_current_color();

  /**
  * Get the name of the current color
  * @return Name of the color as a string
  */
  char* get_current_name();

  /**
  * Increase or decrease the brightness of the current color
  * @param val: Brightness value to be added/subtracted
  */
  void add_bright(int val);

  /**
  * Sets the brightness percentage value to the given value, clamping it to the maximum or minimum value if necessary.
  * @param value: The value to set the brightness percentage to.
  */
  void set_bright(int value);

  /**
  * Get the brightness percentage
  * @return Brightness percentage value
  */
  uint8_t get_bright();
};
#endif