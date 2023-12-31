#include "HWCDC.h"
#include "leds.h"

CRGB red_segment(128, 0, 0);
CRGB blue_segment(0, 0, 128);
Adafruit_NeoPixel pixels(NUM_PIXEL, DATA_OUT, NEO_RGB + NEO_KHZ800);

void init_led() {
  switch (CURRENT_MODE) {
    case RGB_IC:
      pixels.begin();
      rgb_out(red_segment, 0);
      break;

    case RGB:
      ledcSetup(RED_CHANNEL, PWM_FREQ, RESOLUTION);
      ledcSetup(GREEN_CHANNEL, PWM_FREQ, RESOLUTION);
      ledcSetup(BLUE_CHANNEL, PWM_FREQ, RESOLUTION);
      ledcAttachPin(RED_PIN, RED_CHANNEL);
      ledcAttachPin(GREEN_PIN, GREEN_CHANNEL);
      ledcAttachPin(BLUE_PIN, BLUE_CHANNEL);
      break;
  }
}

void hsv_out(C_HSV hsv_val) {
  uint8_t hue = hsv_val.get_hue();
  uint8_t sat = map(hsv_val.get_sat_p(), 0, 100, 0, 255);
  uint8_t val = map(hsv_val.get_val_p(), 0, 100, 0, 255);
  CHSV temp_hsv(hue, sat, val);
  CRGB temp_rgb;
  hsv2rgb_rainbow(temp_hsv, temp_rgb);
  rgb_out(temp_rgb, 255);
}

void rgb_out(CRGB led_val, uint8_t factor) {
  led_val.nscale8_video(factor);

  switch (CURRENT_MODE) {
    case RGB_IC:
      for (int i = 0; i < NUM_PIXEL; i++) {
        pixels.setPixelColor(i, pixels.Color(led_val.r, led_val.g, led_val.b));
      }
      pixels.show();
      break;

    case RGB:
      ledcWrite(RED_CHANNEL, led_val.r);
      ledcWrite(GREEN_CHANNEL, led_val.g);
      ledcWrite(BLUE_CHANNEL, led_val.b);
      break;
  }
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

void ramp_up_rgb(CRGB rgb_val) {
  uint16_t startup_time = 1500;
  uint8_t temp_brightness = 255;
  uint16_t t_delay = startup_time / temp_brightness;

  for (int i = 0; i <= temp_brightness; i++) {
    rgb_out(rgb_val, i);
    delay(t_delay);
  }
}

void set_pixel(uint16_t start, uint16_t dimmer_channel, uint16_t pixel_per_section, uint8_t* data) {
  uint16_t data_index = 1;
  uint16_t led_index = 0;
  int remainder = 0;
  int dim_factor = data[dimmer_channel];
  CRGB color(0, 0, 0);

  universe_out(start, dimmer_channel, dim_factor, pixel_per_section, color, data_index, led_index, data);
  
  if (CURRENT_MODE == RGB_IC) pixels.show();
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
  uint16_t start = artnet_var.get_start_channel() - 1;  // minus one: start artnet data at index 0, smallest address 1
  uint16_t end = artnet_var.get_end_channel() - 1;      // minus one: end artnet data at index 511, highest address 512
  uint16_t start_next = 0;
  uint16_t end_next = 0;
  uint16_t data_index = 1;
  uint16_t led_index = 0;
  uint8_t* current_universe = artnet_var.get_current_data();
  uint8_t* next_universe = artnet_var.get_next_data();
  uint8_t dimmer_factor = current_universe[end];
  CRGB color(0, 0, 0);

  if (end < start) {
    end_next = end;
    end = UNIVERSE_SIZE;
    start_next = 0;
    dimmer_factor = next_universe[end_next];
  }

  universe_out(start, end, dimmer_factor, pixel_per_section, color, data_index, led_index, current_universe);
  if (start_next != end_next) {
    data_index--;
    universe_out(start_next, end_next, dimmer_factor, pixel_per_section, color, data_index, led_index, next_universe);
  }

  if (CURRENT_MODE == RGB_IC) pixels.show();
}

void universe_out(uint16_t start_index, uint16_t end_index, uint8_t dimmer_factor, uint16_t pixel_per_section, CRGB& color, uint16_t& data_index, uint16_t& led_index, uint8_t* data) {
  uint8_t remainder = 0;
  for (int i = start_index; i < end_index; i++) {
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
          color.nscale8_video(dimmer_factor);
          switch (CURRENT_MODE) {
            case RGB_IC:
              pixels.setPixelColor(led_index, pixels.Color(color.r, color.g, color.b));
              break;
            case RGB:
              rgb_out(color, 255);
              break;
          }
          led_index++;
        }
        break;
    }
    data_index++;
  }
}
