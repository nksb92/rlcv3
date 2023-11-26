#include "HWCDC.h"
#include "leds.h"

CRGB red_segment(128, 0, 0);
CRGB blue_segment(0, 0, 128);
Adafruit_NeoPixel pixels(NUM_PIXEL, DATA_OUT, NEO_RGB + NEO_KHZ800);

void init_led() {
  pixels.begin();
  drive_pixel(red_segment, 0);
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

void ramp_up_hsv(C_HSV hsv_val) {
  uint16_t startup_time = 1500;
  uint16_t temp_brightness = hsv_val.get_val_p();
  uint16_t t_delay = startup_time / temp_brightness;

  for (int i = 0; i <= temp_brightness; i++) {
    hsv_val.set_val_p(i);
    hsv_out(hsv_val);
    delay(t_delay);
  }
}

void drive_pixel(CRGB rgb_val, uint8_t factor) {
  rgb_val.nscale8_video(factor);
  for (int i = 0; i < NUM_PIXEL; i++) {
    pixels.setPixelColor(i, pixels.Color(rgb_val.r, rgb_val.g, rgb_val.b));
  }
  pixels.show();
}

void ramp_up_rgb(CRGB rgb_val) {
  uint16_t startup_time = 1500;
  uint8_t temp_brightness = 255;
  uint16_t t_delay = startup_time / temp_brightness;

  for (int i = 0; i <= temp_brightness; i++) {
    drive_pixel(rgb_val, i);
    delay(t_delay);
  }
}

void set_pixel(uint16_t start, uint16_t dimmer_channel, uint16_t pixel_per_section, uint8_t* data) {
  uint16_t data_index = 1;
  uint8_t led_index = 0;
  int remainder = 0;
  int dim_factor = data[dimmer_channel];
  CRGB color(0, 0, 0);

  for (int i = start; i < dimmer_channel; i++) {
    remainder = data_index % 3;
    switch (remainder) {
      case 1:
        color.r = data[i];
        break;
      case 2:
        color.g = data[i];
        break;
      case 0:
        color.b = data[i];
        for (int j = 0; j < pixel_per_section; j++) {
          color.nscale8_video(dim_factor);
          pixels.setPixelColor(led_index, pixels.Color(color.r, color.g, color.b));
          led_index++;
        }
        break;
    }
    data_index++;
  }
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

void output_artnet(rlc_artnet artnet_var) {
  uint16_t sections = artnet_var.get_section_number();
  uint16_t pixel_per_section = NUM_PIXEL / sections;
  uint16_t start = artnet_var.get_start_channel() - 1;
  uint16_t start_next = 0;
  uint16_t end = artnet_var.get_end_channel();
  uint16_t end_next = 0;
  uint8_t* current_universe = artnet_var.get_current_data();
  uint8_t* next_universe = artnet_var.get_next_data();
  uint16_t data_index = 1;
  uint16_t led_index = 0;

  if (end < start) {
    end_next = end;
    end = UNIVERSE_SIZE;
    start_next = 0;
  }

  uint8_t last_red = 0;
  uint8_t last_blue = 0;
  uint8_t last_green = 0;

  for (int i = start; i < end; i++) {
    int remainder = data_index % 3;
    switch (remainder) {
      case 1:
        last_red = current_universe[i];
        break;
      case 2:
        last_green = current_universe[i];
        break;
      case 0:
        last_blue = current_universe[i];
        for (int j = 0; j < pixel_per_section; j++) {
          pixels.setPixelColor(led_index, pixels.Color(last_red, last_green, last_blue));
          led_index++;
        }
        break;
    }
    data_index++;
  }

  if (end_next != start_next) {
    data_index--;
    for (int i = start_next; i < end_next; i++) {
      int remainder = data_index % 3;
      switch (remainder) {
        case 1:
          last_red = next_universe[i];
          break;
        case 2:
          last_green = next_universe[i];
          break;
        case 0:
          last_blue = next_universe[i];
          for (int j = 0; j < pixel_per_section; j++) {
            pixels.setPixelColor(led_index, pixels.Color(last_red, last_green, last_blue));
            led_index++;
          }
          break;
      }
      data_index++;
    }
  }
  pixels.show();
}
