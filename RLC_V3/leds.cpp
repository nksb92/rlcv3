#include "leds.h"

CRGB leds[NUM_PIXEL];

void init_led() {
  FastLED.addLeds<CHIPSET, DATA_OUT, COLOR_ORDER>(leds, NUM_PIXEL);
  drive_pixel(CRGB(0,0,0), 0);
}

void hsv_out(C_HSV hsv_val) {
  uint8_t hue = hsv_val.get_hue();
  uint8_t sat = map(hsv_val.get_sat_p(), 0, 100, 0, 255);
  uint8_t val = map(hsv_val.get_val_p(), 0, 100, 0, 255);
  CHSV temp_hsv(hue, sat, val);
  CRGB temp_rgb;
  hsv2rgb_rainbow(temp_hsv, temp_rgb);
  drive_pixel(temp_rgb, 255);
}

void drive_pixel(CRGB rgb_val, uint8_t factor) {
  rgb_val.nscale8_video(factor);
  //FastLED.clear(true);
  for (int i = 0; i < NUM_PIXEL; i ++) {
    leds[i] = rgb_val;
  }
  FastLED.show();
}