#if !defined(C_RGB_H)
#define C_RGB_H

#include <Arduino.h>
#include <FastLED.h>

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
  C_RGB(uint8_t red, uint8_t green, uint8_t blue);

  void set_current(uint8_t value);

  void next();

  uint8_t get_current();

  void set_red(uint8_t value);

  void add_red(int value);

  uint8_t get_red();

  void set_green(uint8_t value);

  void add_green(int value);

  uint8_t get_green();

  void set_blue(uint8_t value);

  void add_blue(int value);

  uint8_t get_blue();

  void set_rgb(CRGB rgb_value);

  CRGB get_rgb();
};

#endif  // C_RGB_H
