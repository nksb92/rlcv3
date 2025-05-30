#include "leds.h"

CRGB red_segment(128, 0, 0);
CRGB blue_segment(0, 0, 128);

// rainbow variables
CHSV hsv_value(0, 255, 128);
CHSV temp_val(0, 0, 0);
CRGB rgb_rainbow;

#ifdef LED_OUT_RGBIC
Adafruit_NeoPixel pixels(NUM_PIXEL, DATA_OUT, COLOR_ORDER + NEO_KHZ800);
#endif

void init_led() {
#ifdef LED_OUT_RGBIC
  pixels.begin();
  rgb_out(red_segment, 0);
#endif

#ifdef LED_OUT_MOSFET
  // esp32 boards version 3.0.0 breaks i2c api
  // init of pwm pin also changes
  ledcAttach(RED_PIN, PWM_FREQ, RESOLUTION);
  ledcAttach(GREEN_PIN, PWM_FREQ, RESOLUTION);
  ledcAttach(BLUE_PIN, PWM_FREQ, RESOLUTION);

  // Method before 3.0.0
  // ledcSetup(RED_CHANNEL, PWM_FREQ, RESOLUTION);
  // ledcSetup(GREEN_CHANNEL, PWM_FREQ, RESOLUTION);
  // ledcSetup(BLUE_CHANNEL, PWM_FREQ, RESOLUTION);
  // ledcAttachPin(RED_PIN, RED_CHANNEL);
  // ledcAttachPin(GREEN_PIN, GREEN_CHANNEL);
  // ledcAttachPin(BLUE_PIN, BLUE_CHANNEL);
#endif

#ifdef LED_OUT_I2C
// no init needed for panel i2c mode
#endif
}

void hsv_out(C_HSV hsv_val) {
  uint8_t hue = 0;
  uint8_t sat = 0;
  uint8_t val = 0;

  hue = hsv_val.get_hue();

#if defined(PERCENTAGE)
  sat = map(hsv_val.get_sat(), 0, 100, 0, 255);
  val = map(hsv_val.get_val(), 0, 100, 0, 255);
#endif

#if defined(FULL_RANGE)
  sat = hsv_val.get_sat();
  val = hsv_val.get_val();
#endif

  CHSV temp_hsv(hue, sat, val);
  CRGB temp_rgb;
  hsv2rgb_rainbow(temp_hsv, temp_rgb);
  rgb_out(temp_rgb, 255);
}

void send_data_i2c(CRGB led_val, uint8_t slave_adr) {
  Wire.beginTransmission(slave_adr);
  Wire.write(led_val.r);
  Wire.write(led_val.g);
  Wire.write(led_val.b);
  Wire.endTransmission(true);
}

void rgb_out(CRGB led_val, uint8_t factor) {
  led_val.nscale8_video(factor);

#ifdef LED_OUT_RGBIC
  for (int i = 0; i < NUM_PIXEL; i++) {
    pixels.setPixelColor(i, pixels.Color(led_val.r, led_val.g, led_val.b));
  }
  pixels.show();
#endif

#ifdef LED_OUT_MOSFET
  // ledcWrite(RED_CHANNEL, led_val.r);
  // ledcWrite(GREEN_CHANNEL, led_val.g);
  // ledcWrite(BLUE_CHANNEL, led_val.b);
  ledcWrite(RED_PIN, led_val.r);
  ledcWrite(GREEN_PIN, led_val.g);
  ledcWrite(BLUE_PIN, led_val.b);
#endif

#ifdef LED_OUT_I2C
  for (int i = SLAVE_ADR_STRT; i < SLAVE_ADR_STRT + NUM_PIXEL; i++) {
    send_data_i2c(led_val, i);
  }
#endif
}

void ramp_up_hsv(C_HSV hsv_val) {
  uint16_t startup_time = 1500;
  uint16_t temp_brightness = hsv_val.get_val();
  uint16_t t_delay = startup_time / temp_brightness;

  for (int i = 0; i <= temp_brightness; i++) {
    hsv_val.set_val(i);
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

uint16_t set_pixel(uint16_t start, uint16_t dimmer_channel, uint16_t pixel_per_section, uint8_t *data) {
  uint16_t data_index = 1;
  uint16_t led_index = 0;
  uint16_t sum = 0;
  int dim_factor = data[dimmer_channel];

  CRGB color(0, 0, 0);

  sum = universe_out(start, dimmer_channel, dim_factor, NUM_PIXEL / pixel_per_section, color, data_index, led_index, data, sum);

#ifdef LED_OUT_RGBIC
  pixels.show();
#endif
  return sum;
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

#ifdef LED_OUT_RGBIC
    for (int j = 0; j < pixel_per_seg; j++) {
      pixels.setPixelColor(count, pixels.Color(color.r, color.g, color.b));
      count++;
    }
#endif

#ifdef LED_OUT_MOSFET
    rgb_out(color, 255);
#endif

#ifdef LED_OUT_I2C
    for (int j = 0; j < pixel_per_seg; j++) {
      send_data_i2c(color, SLAVE_ADR_STRT + count);
      count++;
    }
#endif

    col_sel++;
  }
#ifdef LED_OUT_RGBIC
  pixels.show();
#endif
}

uint16_t output_artnet(rlc_artnet artnet_var) {
  uint16_t sections = artnet_var.get_section_number();
  uint16_t pixel_per_section = NUM_PIXEL / sections;
  uint16_t start = artnet_var.get_start_channel() - 1;  // minus one: start artnet data at index 0, smallest address 1
  uint16_t end = artnet_var.get_end_channel() - 1;      // minus one: end artnet data at index 511, highest address 512
  uint16_t start_next = 0;
  uint16_t end_next = 0;
  uint16_t data_index = 1;
  uint16_t led_index = 0;
  uint16_t sum = 0;
  uint8_t *current_universe = artnet_var.get_current_data();
  uint8_t *next_universe = artnet_var.get_next_data();
  uint8_t dimmer_factor = current_universe[end];
  CRGB color(0, 0, 0);

  if (end < start) {
    end_next = end;
    end = UNIVERSE_SIZE;
    start_next = 0;
    dimmer_factor = next_universe[end_next];
  }

  sum = universe_out(start, end, dimmer_factor, pixel_per_section, color, data_index, led_index, current_universe, sum);
  if (start_next != end_next) {
    data_index--;
    sum = universe_out(start_next, end_next, dimmer_factor, pixel_per_section, color, data_index, led_index, next_universe, sum);
  }

#ifdef LED_OUT_RGBIC
  pixels.show();
#endif
  return sum;
}

uint16_t universe_out(uint16_t start_index, uint16_t end_index, uint8_t dimmer_factor, uint16_t pixel_per_section, CRGB &color, uint16_t &data_index, uint16_t &led_index, uint8_t *data, uint16_t sum = 0) {

  uint8_t remainder = 0;
  uint16_t temp_sum = 0;
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
        color.nscale8_video(dimmer_factor);
        for (int j = 0; j < pixel_per_section; j++) {

          temp_sum += color.r + color.g + color.b;

          if (temp_sum > sum) {
            sum = temp_sum;
          }

#ifdef LED_OUT_RGBIC
          pixels.setPixelColor(led_index, pixels.Color(color.r, color.g, color.b));
#endif
#ifdef LED_OUT_MOSFET
          rgb_out(color, 255);
#endif
#ifdef LED_OUT_I2C
          send_data_i2c(color, SLAVE_ADR_STRT + led_index);
#endif
          led_index++;
        }
        break;
    }
    data_index++;
  }
  return sum;
}

void rainbow_fw() {
  hsv_value.hue++;
  temp_val = hsv_value;
  for (int i = 0; i < NUM_PIXEL; i++) {
    hsv2rgb_rainbow(temp_val, rgb_rainbow);
    pixels.setPixelColor(i, pixels.Color(rgb_rainbow.r, rgb_rainbow.g, rgb_rainbow.b));
    temp_val.hue += 5;
  }
  pixels.show();
}
