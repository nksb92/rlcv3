#include "dmx.h"
#include "leds.h"
#include "rotary_encoder.h"
#include "display.h"
#include "nvm.h"
#include "rlc_artnet.h"
#include "segments.h"
#include "common.h"

int16_t encoder_val = 0;
uint8_t main_state = 1;
unsigned long last_millis = 0;
unsigned long saved_timer_start = 0;
unsigned long last_send = 0;
unsigned long last_added_dot = 0;
unsigned long last_scroll_time = 0;
uint16_t standby_time = 30000;
uint16_t display_saved_time = 2000;
uint8_t scroll_time = 100;
uint16_t add_dot_time = 500;

bool artnet_data = false;
bool display_saved = false;
bool change_vals = true;
bool button_pressed = false;
bool button_long_pressed = false;
bool button_double_pressed = false;

C_HSV hsv_val(STD_HUE, STD_SAT_P, STD_VAL_P);
C_RGB rgb_val(STD_RED, STD_GREEN, STD_BLUE);
rgb_dmx dmx_val(CRGB(0, 0, 0));
main main_sw;
segments seg;
rlc_artnet artnet_val;

EncoderButton enc_button(DT_PIN, CLK_PIN, SW_PIN);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void on_artnet_frame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data) {
  uint16_t current_universe = artnet_val.get_start_universe();
  if (universe == current_universe) {
    artnet_val.set_current_universe(data);
  } else if (universe == (current_universe + 1)) {
    artnet_val.set_next_universe(data);
  }
  artnet_data = true;
}

void setup() {
  delay(2000);
  Serial.begin(115200);
  Serial.println("Startup");

  init_eeprom();
  init_led();
  init_display(display);
  init_encoder(enc_button);
  dmx_val.install_dmx();
  seg.init_segments();

  artnet_val.init(on_artnet_frame);
  // read_eeprom(hsv_val, rgb_val, dmx_val, main_sw);
  dmx_val.set_number_segments(seg.get_num_seg());
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
            artnet_val.next_selection();
            display_artnet_rec(display, artnet_val);
            break;

          case SEGMENT_CNTRL:
            seg_display_update(display, seg);
            break;
        }
        break;
    }
    set_press_state(false);
  }

  if (button_long_pressed) {
    main_sw.deeper();
    switch (main_sw.get_deepness()) {
      case MAIN_MENU:
        switch (artnet_val.get_current_fsm()) {
          case CONNECTING:
            artnet_val.set_current_fsm(MENU);
          case ARTNET_REC_PAGE:
            artnet_val.stop_artnet();
            artnet_val.set_current_fsm(MENU);
            break;
        }
        break;
      case SUB_MENU:
        switch (main_state) {
          case ARTNET_NODE:
            break;
          case ARTNET_REC:
            switch (artnet_val.get_current_fsm()) {
              case MENU:
                artnet_val.connect_wifi();
                artnet_val.set_current_fsm(CONNECTING);
                display_connecting_artnet(display, artnet_val);
                last_added_dot = millis();
                break;
            }
            break;
        }
        break;
    }
    Serial.println(artnet_val.get_wifi_status());
    set_event_status(true);
    set_long_press(false);
  }

  // handle everything on event
  if (change_vals) {
    switch (main_sw.get_deepness()) {
      case MAIN_MENU:
        if (encoder_val != 0) {
          main_sw.add_current(encoder_val);
          main_state = main_sw.get_current();
        }
        display_menu(display, main_state);
        drive_pixel(rgb_val.get_rgb(), 0);
        break;

      case SUB_MENU:
        switch (main_state) {
          case HSV_PAGE:
            // if encoder val is zero, don't jump into functions
            if (encoder_val != 0) {
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
            }
            hsv_out(hsv_val);
            hsv_display_update(display, hsv_val);
            break;

          case RGB_PAGE:
            // if encoder val is zero, don't jump into functions
            if (encoder_val != 0) {
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
            }
            drive_pixel(rgb_val.get_rgb(), 255);
            rgb_display_update(display, rgb_val);
            break;

          case DMX_PAGE:
            // if encoder val is zero, don't jump into functions
            if (encoder_val != 0) {
              dmx_val.add_to_adress(encoder_val);
            }
            dmx_display_update(display, dmx_val);
            break;

          case ARTNET_NODE:
            break;

          case ARTNET_REC:
            switch (artnet_val.get_current_fsm()) {
              case ARTNET_REC_PAGE:
                switch (artnet_val.get_current_sel()) {
                  case UNIVERSE:
                    artnet_val.add_universe(encoder_val);
                    break;
                  case CHANNEL:
                    artnet_val.add_channel(encoder_val);
                    break;
                }
                display_artnet_rec(display, artnet_val);
                break;
            }
            break;

          case SEGMENT_CNTRL:
            // if encoder val is zero, don't jump into functions
            if (encoder_val != 0) {
              seg.add_seg(encoder_val);
            }
            show_segments(seg.get_num_seg());
            dmx_val.set_number_segments(seg.get_num_seg());
            artnet_val.set_number_segments(seg.get_num_seg());
            seg_display_update(display, seg);
            break;
        }
        break;
    }
    change_vals = false;
    encoder_val = 0;
    set_dspl_standby(false);
    last_millis = millis();
    set_event_status(change_vals);
  }

  // no action for 30 secs will set the display in standby mode
  if (millis() - last_millis >= standby_time && !get_standby_status()) {
    set_dspl_standby(true);
    display.clearDisplay();
    display.display();
  }

  // hanlde everthing periodically
  switch (main_sw.get_deepness()) {
    case MAIN_MENU:
      break;
    case SUB_MENU:
      switch (main_state) {
        case DMX_PAGE:
          break;

        case ARTNET_NODE:
          break;

        case ARTNET_REC:
          // on connection loss, jump to connecting state
          switch (artnet_val.get_current_fsm()) {
            case CONNECTING:
              if (!get_standby_status()) {
                if (millis() - last_added_dot >= add_dot_time) {
                  display_connecting_artnet(display, artnet_val);
                  artnet_val.add_dot();
                  last_added_dot = millis();
                }
              }
              if (artnet_val.get_wifi_status()) {
                artnet_val.set_current_fsm(ARTNET_REC_PAGE);
                display_artnet_rec(display, artnet_val);
                artnet_val.begin_artnet();
              }
              break;

            case ARTNET_REC_PAGE:
              // check connection 
              if (!artnet_val.get_wifi_status()) {
                artnet_val.set_current_fsm(CONNECTING);
              }

              artnet_val.artnet_parse();
              if (artnet_data) {
                output_artnet(artnet_val);
                artnet_data = false;
              }

              if (artnet_val.get_current_sel() == IP_ADDRESS && !get_standby_status()) {
                if (millis() - last_scroll_time >= scroll_time) {
                  scroll();
                  display_artnet_rec(display, artnet_val);
                  last_scroll_time = millis();
                }
              }
              break;
          }
          break;
      }
      break;
  }


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