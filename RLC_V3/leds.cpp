#include "leds.h"

CRGB leds[NUM_PIXEL];
CRGB red_segment(128, 0, 0);
CRGB blue_segment(0, 0, 128);
Adafruit_NeoPixel pixels(NUM_PIXEL, DATA_OUT, NEO_RGB + NEO_KHZ800);

void init_led() {
  pixels.begin();
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
  for (int i = 0; i < NUM_PIXEL; i++) {
    pixels.setPixelColor(i, pixels.Color(rgb_val.r, rgb_val.g, rgb_val.b));
  }
  pixels.show();
}

void show_segments(uint16_t segs) {
  uint16_t count = 0;
  uint16_t col_sel = 0;
  uint16_t pixel_per_seg = NUM_PIXEL / segs;

  CRGB color(0, 0, 0);
  for (int i = 0; i < segs; i++) {
    if (col_sel % 2 == 0) {
      color = red_segment;
    } else {
      color = blue_segment;
    }
    for (int j = 0; j < pixel_per_seg; j++) {
      pixels.setPixelColor(count, pixels.Color(color.r, color.g, color.b));
      count++;
    }
    col_sel++;
  }
  pixels.show();
}