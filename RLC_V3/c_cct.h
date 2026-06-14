#if !defined(C_CCT_H)
#define C_CCT_H

#include <Arduino.h>
#include "config.h"

enum {
  CCT_KELVIN,
  CCT_BRIGHTNESS,
  CCT_LAST
};

class c_cct {
 private:
  uint16_t kelvin;
  uint8_t brightness;
  uint8_t current;

 public:
  c_cct(uint16_t _kelvin = (CCT_MIN_KELVIN + (((CCT_MAX_KELVIN - CCT_MIN_KELVIN) / 2) / CCT_STEP_SIZE) * CCT_STEP_SIZE), uint8_t _brightness = 100);
  ~c_cct();

  void add_kelvin(int amount);
  void add_brightness(int amount);

  uint16_t get_kelvin();
  uint8_t get_brightness();

  void set_kelvin(uint16_t _kelvin);
  void set_brightness(uint8_t _brightness);

  uint8_t get_current();
  void set_current(uint8_t _current);
  void next();
};

#endif // C_CCT_H
