#include "leds.h"

void init_led() {
  ledcSetup(RED_CHANNEL, PWM_FREQ, RESOLUTION);
  ledcSetup(GREEN_CHANNEL, PWM_FREQ, RESOLUTION);
  ledcSetup(BLUE_CHANNEL, PWM_FREQ, RESOLUTION);
  ledcAttachPin(RED_PIN, RED_CHANNEL);
  ledcAttachPin(GREEN_PIN, GREEN_CHANNEL);
  ledcAttachPin(BLUE_PIN, BLUE_CHANNEL);
}

void ramp_up(C_HSV hsv_val, C_RGB rgb_val, pdc_page& pdc, main& main_sw) {
  uint16_t start_up_time = 1500;
  uint16_t t_delay = 0;
  uint8_t temp_brightness = 0;
  uint16_t temp_v = 0;

  switch (main_sw.get_current()) {
    case HSV_PAGE:
      temp_v = hsv_val.get_val_p();
      t_delay = start_up_time / temp_v;
      for (int i = 0; i <= temp_v; i++) {
        hsv_val.set_val_p(i);
        hsv_out(hsv_val);
        delay(t_delay);
      }
      break;

    case RGB_PAGE:
      temp_v = 255;
      t_delay = start_up_time / temp_v;
      for (int i = 0; i <= temp_v; i++) {
        rgb_out(rgb_val.get_rgb(), i);
        delay(t_delay);
      }
      break;

    case PDC_PAGE:
      temp_brightness = pdc.get_bright();
      t_delay = start_up_time / temp_brightness;
      for (int i = 0; i <= temp_brightness; i++) {
        pdc.set_bright(i);
        rgb_out(pdc.get_current_color(), pdc.get_bright());
        delay(t_delay);
      }
      break;
    default:
      delay(start_up_time);
      break;
  }
}

void rgb_out(CRGB led_val, uint8_t factor) {
  led_val.nscale8_video(factor);
  ledcWrite(RED_CHANNEL, led_val.r);
  ledcWrite(GREEN_CHANNEL, led_val.g);
  ledcWrite(BLUE_CHANNEL, led_val.b);
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