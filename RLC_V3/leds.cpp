#include "leds.h"

CRGB red_segment(255, 0, 0);
CRGB blue_segment(0, 0, 200);

extern segments seg;

// rainbow variables
CHSV hsv_value(0, 255, 255);
CHSV temp_val(0, 0, 0);
CRGB rgb_rainbow;

uint8_t temp_brightness = 0;

#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
NeoPixelBus<NeoRgbwwFeature, NeoEsp32BitBangWs2805Method> strip(NUM_PIXEL, DATA_OUT);
#else
Adafruit_NeoPixel pixels(NUM_PIXEL, DATA_OUT, COLOR_ORDER + NEO_KHZ800);
#endif
#endif

void init_led() {
#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  strip.Begin();
  strip.Show();
#else
  pixels.begin();
  rgb_out(red_segment, 0);
#endif
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

  if (seg.get_value_mode() == VALUE_PERCENTAGE) {
    sat = map(hsv_val.get_sat(), 0, 100, 0, 255);
    val = map(hsv_val.get_val(), 0, 100, 0, 255);
  } else {
    sat = hsv_val.get_sat();
    val = hsv_val.get_val();
  }

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
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  for (int i = 0; i < NUM_PIXEL; i++) {
    strip.SetPixelColor(i, RgbwwColor(led_val.g, led_val.r, led_val.b, 0, 0));
  }
  strip.Show();
#else
  for (int i = 0; i < NUM_PIXEL; i++) {
    pixels.setPixelColor(i, pixels.Color(led_val.r, led_val.g, led_val.b));
  }
  pixels.show();
#endif
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

uint16_t set_pixel(uint16_t start, uint16_t used_addresses, uint16_t pixel_per_section, uint8_t dimmer_mode, uint8_t white_mode, uint8_t* data) {
  uint16_t data_index = 1;
  uint16_t led_index = 0;
  uint16_t sum = 0;
  
  uint16_t start_data = start;
  uint16_t end_data = start + used_addresses;
  uint8_t dim_factor = 255;

  if (dimmer_mode == DIMMER_RGB) {
    dim_factor = data[start];
    start_data = start + 1;
  } else if (dimmer_mode == RGB_DIMMER) {
    dim_factor = data[start + used_addresses - 1];
    end_data = start + used_addresses - 1;
  }

  CRGB color(0, 0, 0);

  sum = universe_out(start_data, end_data, dim_factor, NUM_PIXEL / pixel_per_section, color, data_index, led_index, data, sum, white_mode);

#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  strip.Show();
#else
  pixels.show();
#endif
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
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
    for (int j = 0; j < pixel_per_seg; j++) {
      strip.SetPixelColor(count, RgbwwColor(color.g, color.r, color.b, 0, 0));
      count++;
    }
#else
    for (int j = 0; j < pixel_per_seg; j++) {
      pixels.setPixelColor(count, pixels.Color(color.r, color.g, color.b));
      count++;
    }
#endif
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
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  strip.Show();
#else
  pixels.show();
#endif
#endif
}

uint16_t output_artnet(rlc_artnet artnet_var, uint8_t dimmer_mode, uint8_t white_mode) {
  uint16_t sections = artnet_var.get_section_number();
  uint16_t pixel_per_section = NUM_PIXEL / sections;
  uint16_t start = artnet_var.get_start_channel() - 1;  // minus one: start artnet data at index 0, smallest address 1
  uint16_t end = artnet_var.get_end_channel() - 1;      // minus one: end artnet data at index 511, highest address 512
  uint16_t start_next = 0;
  uint16_t end_next = 0;
  uint16_t data_index = 1;
  uint16_t led_index = 0;
  uint16_t sum = 0;
  uint8_t* current_universe = artnet_var.get_current_data();
  uint8_t* next_universe = artnet_var.get_next_data();
  
  uint8_t dimmer_factor = 255;
  uint16_t start_data = start;
  uint16_t end_data = end + 1; // normally processes up to end_data (exclusive)
  
  if (dimmer_mode == DIMMER_RGB) {
    dimmer_factor = current_universe[start];
    start_data = start + 1;
    if (start_data >= UNIVERSE_SIZE) {
      start_data = 0;
      current_universe = next_universe;
    }
  } else if (dimmer_mode == RGB_DIMMER) {
    if (end < start) {
      dimmer_factor = next_universe[end];
    } else {
      dimmer_factor = current_universe[end];
    }
    end_data = end;
  }
  // For RGB_ONLY, dimmer remains 255 and end_data is end + 1

  CRGB color(0, 0, 0);

  // If there's wrap-around
  if (end_data < start_data) {
    end_next = end_data;
    end_data = UNIVERSE_SIZE;
    start_next = 0;
    
    sum = universe_out(start_data, end_data, dimmer_factor, pixel_per_section, color, data_index, led_index, current_universe, sum, white_mode);
    if (start_next != end_next) {
      data_index--;
      sum = universe_out(start_next, end_next, dimmer_factor, pixel_per_section, color, data_index, led_index, next_universe, sum, white_mode);
    }
  } else {
    sum = universe_out(start_data, end_data, dimmer_factor, pixel_per_section, color, data_index, led_index, current_universe, sum, white_mode);
  }

#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  strip.Show();
#else
  pixels.show();
#endif
#endif
  return sum;
}

uint16_t universe_out(uint16_t start_index, uint16_t end_index, uint8_t dimmer_factor, uint16_t pixel_per_section, CRGB& color, uint16_t& data_index, uint16_t& led_index, uint8_t* data, uint16_t sum, uint8_t white_mode) {
  uint16_t temp_sum = 0;

  uint8_t channels_per_seg = 3;
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBW
  if (white_mode == 1) channels_per_seg = 4; // WHITE_ONE_CH
#elif LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  if (white_mode == 1) channels_per_seg = 4; // WHITE_ONE_CH
  else if (white_mode == 2) channels_per_seg = 5; // WHITE_TWO_CH
#endif

  uint8_t r = 0, g = 0, b = 0, cw = 0, ww = 0;

  for (int i = start_index; i < end_index; i++) {
    uint8_t remainder = data_index % channels_per_seg;
    if (remainder == 1) r = data[i];
    else if (remainder == 2) g = data[i];
    else if (remainder == 3 && channels_per_seg > 3) b = data[i];
    else if (remainder == 4 && channels_per_seg > 4) cw = data[i];
    
    if (remainder == 0) {
      if (channels_per_seg == 3) {
        b = data[i];
        cw = 0; ww = 0;
      } else if (channels_per_seg == 4) {
        ww = data[i];
        cw = 0;
      } else if (channels_per_seg == 5) {
        ww = data[i];
      }

      r = (r * dimmer_factor) / 255;
      g = (g * dimmer_factor) / 255;
      b = (b * dimmer_factor) / 255;
      cw = (cw * dimmer_factor) / 255;
      ww = (ww * dimmer_factor) / 255;

      for (int j = 0; j < pixel_per_section; j++) {
        temp_sum += r + g + b + cw + ww;
        if (temp_sum > sum) sum = temp_sum;

#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
        strip.SetPixelColor(led_index, RgbwwColor(g, r, b, ww, cw));
#else
        pixels.setPixelColor(led_index, pixels.Color(r, g, b));
#endif
#endif

#ifdef LED_OUT_MOSFET
        color.r = r; color.g = g; color.b = b;
        rgb_out(color, 255);
#endif
#ifdef LED_OUT_I2C
        color.r = r; color.g = g; color.b = b;
        send_data_i2c(color, SLAVE_ADR_STRT + led_index);
#endif
        led_index++;
      }
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

#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
    strip.SetPixelColor(i, RgbwwColor(rgb_rainbow.g, rgb_rainbow.r, rgb_rainbow.b, 0, 0));
#else
    pixels.setPixelColor(i, pixels.Color(rgb_rainbow.r, rgb_rainbow.g, rgb_rainbow.b));
#endif
#endif

#ifdef LED_OUT_MOSFET
    rgb_out(rgb_rainbow, 255);
#endif

#ifdef LED_OUT_I2C
    send_data_i2c(rgb_rainbow, SLAVE_ADR_STRT + i);
#endif

    temp_val.hue += 5;
  }

#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  strip.Show();
#else
  pixels.show();
#endif
#endif
}

void grad_out(C_GRAD grad_val) {
  uint8_t sh = grad_val.get_start_hue();
  uint8_t ss = grad_val.get_start_sat();
  uint8_t sv = grad_val.get_start_val();
  
  uint8_t eh = grad_val.get_end_hue();
  uint8_t es = grad_val.get_end_sat();
  uint8_t ev = grad_val.get_end_val();

  if (seg.get_value_mode() == VALUE_PERCENTAGE) {
    ss = map(ss, 0, 100, 0, 255);
    sv = map(sv, 0, 100, 0, 255);
    es = map(es, 0, 100, 0, 255);
    ev = map(ev, 0, 100, 0, 255);
  }

  // calculate distance always counting upwards
  uint16_t h_dist = (uint8_t)(eh - sh);

  for (int i = 0; i < NUM_PIXEL; i++) {
    float fraction = (NUM_PIXEL > 1) ? ((float)i / (float)(NUM_PIXEL - 1)) : 0;
    
    uint8_t curr_h = sh + (uint8_t)(h_dist * fraction);
    uint8_t curr_s = ss + (int16_t)((es - ss) * fraction);
    uint8_t curr_v = sv + (int16_t)((ev - sv) * fraction);

    CHSV temp_hsv(curr_h, curr_s, curr_v);
    CRGB temp_rgb;
    hsv2rgb_rainbow(temp_hsv, temp_rgb);

#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
    strip.SetPixelColor(i, RgbwwColor(temp_rgb.g, temp_rgb.r, temp_rgb.b, 0, 0));
#else
    pixels.setPixelColor(i, pixels.Color(temp_rgb.r, temp_rgb.g, temp_rgb.b));
#endif
#endif

#ifdef LED_OUT_MOSFET
    if (i == NUM_PIXEL / 2) rgb_out(temp_rgb, 255); // Output middle color for MOSFET
#endif

#ifdef LED_OUT_I2C
    send_data_i2c(temp_rgb, SLAVE_ADR_STRT + i);
#endif
  }

#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  strip.Show();
#else
  pixels.show();
#endif
#endif
}

void cct_out(c_cct cct_val) {
  uint16_t kelvin = cct_val.get_kelvin();
  uint8_t brightness = cct_val.get_brightness();

  if (seg.get_value_mode() == VALUE_PERCENTAGE) {
    brightness = map(brightness, 0, 100, 0, 255);
  }

  uint8_t ww = 0;
  uint8_t cw = 0;

  if (kelvin <= CCT_MIN_KELVIN) {
    ww = 255;
    cw = 0;
  } else if (kelvin >= CCT_MAX_KELVIN) {
    ww = 0;
    cw = 255;
  } else {
    float cw_percent = (float)(kelvin - CCT_MIN_KELVIN) / (float)(CCT_MAX_KELVIN - CCT_MIN_KELVIN);
    cw = cw_percent * 255;
    ww = 255 - cw;
  }

#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGB
  uint8_t r = 255;
  uint8_t g = (cw * 255 + ww * 197) / 255;
  uint8_t b = (cw * 255 + ww * 143) / 255;
  CRGB color(r, g, b);
  rgb_out(color, brightness);
#endif

  ww = (ww * brightness) / 255;
  cw = (cw * brightness) / 255;

#ifdef LED_OUT_RGBIC
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  for (int i = 0; i < NUM_PIXEL; i++) {
    strip.SetPixelColor(i, RgbwwColor(0, 0, 0, ww, cw));
  }
  strip.Show();
#endif
#endif
}
