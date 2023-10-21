#include "dmx.h"
#include "leds.h"
#include "rotary_encoder.h"
#include "display.h"
#include "nvm.h"
#include "common.h"

int16_t encoder_val = 0;
uint8_t main_state = 1;
unsigned long last_millis;
unsigned long saved_timer_start;
unsigned long last_send;
uint16_t standby_time = 30000;
uint16_t display_saved_time = 2000;
uint8_t pause_time = 10;

bool display_saved = false;
bool change_vals = true;
bool button_pressed = false;
bool button_long_pressed = false;
bool button_double_pressed = false;

C_HSV hsv_val(STD_HUE, STD_SAT_P, STD_VAL_P);
C_RGB rgb_val(STD_RED, STD_GREEN, STD_BLUE);
rgb_dmx dmx_val(CRGB(0, 0, 0));
main main_sw;

EncoderButton enc_button(DT_PIN, CLK_PIN, SW_PIN);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Serial.println("Startup");

  init_eeprom();
  init_led();
  init_display(display);
  init_encoder(enc_button);
  dmx_val.install_dmx();

  // read_eeprom(hsv_val, rgb_val, dmx_val, main_sw);

  Serial.println("Startup complete.");

  last_millis = millis();
  saved_timer_start = millis();
  set_event_status(true);
  main_state = main_sw.get_current();
}

void loop() {
  enc_button.update();
  change_vals = get_event_status();
  button_pressed = get_press_state();
  button_long_pressed = get_long_press();
  button_double_pressed = get_double_press();

  encoder_val = get_encoder_val();
  if (button_pressed) {
    switch (main_sw.get_deepness()) {
      case MAIN_MENU:
        main_sw.next();
        main_state = main_sw.get_current();
        display_menu(display, main_state);
        break;
      case SUB_MENU:
        switch (main_sw.get_current()) {
          case HSV_PAGE:
            hsv_val.next();
            hsv_display_update(display, hsv_val);
            break;
          case RGB_PAGE:
            rgb_val.next();
            rgb_display_update(display, rgb_val);
            break;
          case DMX_PAGE:
            dmx_display_update(display, dmx_val);
            break;
          case ARTNET_NODE:
            break;
          case ARTNET_REC:
            break;
          case SEGMENT_CNTRL:
            break;
        }
        break;
    }
    set_press_state(false);
  }

  if (button_long_pressed) {
    main_sw.deeper();
    set_event_status(true);
    set_long_press(false);
  }

  // handle everything on event
  if (change_vals) {
    switch (main_sw.get_deepness()) {
      case MAIN_MENU:
        display_menu(display, main_state);
        drive_pixel(rgb_val.get_rgb(), 0);
        break;
      case SUB_MENU:
        switch (main_state) {
          case HSV_PAGE:
            switch (hsv_val.get_current()) {
              case HUE:
                hsv_val.add_hue(encoder_val);
                break;
              case SAT:
                hsv_val.add_sat(encoder_val);
                break;
              case VAL:
                hsv_val.add_val(encoder_val);
                break;
            }
            hsv_out(hsv_val);
            hsv_display_update(display, hsv_val);
            break;

          case RGB_PAGE:
            switch (rgb_val.get_current()) {
              case RED:
                rgb_val.add_red(encoder_val);
                break;
              case GREEN:
                rgb_val.add_green(encoder_val);
                break;
              case BLUE:
                rgb_val.add_blue(encoder_val);
                break;
            }
            drive_pixel(rgb_val.get_rgb(), 255);
            rgb_display_update(display, rgb_val);
            break;
        }
        break;
    }
    change_vals = false;
    set_dspl_standby(false);
    last_millis = millis();
    set_event_status(change_vals);
  }

  // no action for 30 secs will set the display in standby mode
  if (millis() - last_millis >= standby_time) {
    set_dspl_standby(true);
    display.clearDisplay();
    display.display();
  }
  // hanlde everthing periodically
  // switch (main_state) {
  //   case DMX_PAGE:
  //     dmx_val.hanlde_dmx();
  //     switch (dmx_val.get_current()) {
  //       case WIRE:
  //         break;
  //       case SENDER:
  //         if (millis() - pause_time >= last_send) {
  //           send(dmx_val);
  //           last_send = millis();
  //         }
  //         break;
  //       case RECEIVER:
  //         get_received_data(dmx_val);
  //         break;
  //     }
  //     rgb_out(dmx_val.get_dmx_message(), 255);
  //     break;
  // }

  // // cycle through display options
  // if (button_pressed) {
  //   switch (main_state) {
  //     case HSV_PAGE:
  //       hsv_val.next();
  //       break;
  //     case RGB_PAGE:
  //       rgb_val.next();
  //       break;
  //     case DMX_PAGE:
  //       dmx_val.next();
  //       switch (dmx_val.get_current()) {
  //         case WIRE:
  //           receiver_deinit();
  //           break;
  //         case SENDER:
  //           sender_init();
  //           last_send = millis();
  //           break;
  //         case RECEIVER:
  //           sender_deinit();
  //           receiver_init();
  //           break;
  //       }
  //       break;
  //     default:
  //       break;
  //   }
  //   set_press_state(false);
  // }

  // // cycle through the main menu
  // if (button_long_pressed) {
  //   main_sw.next();
  //   if (main_sw.get_current() == DMX_PAGE) {
  //     switch (dmx_val.get_current()) {
  //       case SENDER:
  //         sender_init();
  //         break;
  //       case RECEIVER:
  //         receiver_init();
  //         break;
  //     }
  //   }
  //   set_long_press(false);
  // }

  // // save variables to EEPROM and display for two secconds
  // // that the values has been saved
  // if (button_double_pressed) {
  //   write_eeprom(hsv_val, rgb_val, dmx_val, main_sw);
  //   set_double_press(false);
  //   display_saved = true;
  //   display_saved_status(display);
  //   saved_timer_start = millis();
  // }

  // // display for two secconds that the data has been written to the eeprom
  // if (millis() - saved_timer_start >= display_saved_time) {
  //   if (display_saved) {
  //     change_vals = true;
  //     display_saved = false;
  //   }
  // }

  // main_state = main_sw.get_current();
}