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
uint8_t current_deepness = 0;
unsigned long last_millis = 0;
unsigned long last_added_dot = 0;
unsigned long last_scroll_time = 0;
uint16_t standby_time = 30000;
uint8_t scroll_time = 110;
uint16_t add_dot_time = 500;

bool artnet_data = false;
bool change_vals = true;
bool button_pressed = false;
bool button_long_pressed = false;
bool long_press_triggered = false;
bool button_double_pressed = false;

C_HSV hsv_val(STD_HUE, STD_SAT_P, STD_VAL_P);
C_RGB rgb_val(STD_RED, STD_GREEN, STD_BLUE);
rgb_dmx dmx_val;
main main_sw;
segments seg;
rlc_artnet artnet_var;
EncoderButton enc_button(DT_PIN, CLK_PIN, SW_PIN);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void on_artnet_frame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data) {
  uint16_t current_universe = artnet_var.get_start_universe();
  if (universe == current_universe) {
    artnet_var.set_current_universe(data);
  } else if (universe == (current_universe + 1)) {
    artnet_var.set_next_universe(data);
  }
  artnet_data = true;
}

void setup() {
  delay(2000);
  Serial.begin(115200);
  Serial.println("Startup");

  // init all classes and functions
  init_eeprom();
  init_led();
  init_display(display);
  init_encoder(enc_button);
  dmx_val.install_dmx();
  seg.init_segments();
  artnet_var.init(on_artnet_frame);

  // read non volatile memory and set variables accordingly
  read_eeprom(hsv_val, rgb_val, dmx_val, main_sw, artnet_var, seg);
  switch (artnet_var.get_current_fsm()) {
    case CONNECTING:
    case ARTNET_PAGE:
      artnet_var.connect_wifi();
      artnet_var.set_current_fsm(CONNECTING);
      break;
  }
  current_deepness = main_sw.get_deepness();
  main_state = main_sw.get_current();
  Serial.println("Startup complete.");
  last_millis = millis();
  set_event_status(true);
}

void loop() {
  enc_button.update();
  change_vals = get_event_status();
  button_pressed = get_press_state();
  button_double_pressed = get_double_press();
  encoder_val = get_encoder_val();

  if (get_long_press()) {
    long_press_triggered = false;
    set_long_press(false);
  }

  if (enc_button.isPressed()) {
    if (enc_button.currentDuration() > LONG_PRESS_TIME && !long_press_triggered) {
      button_long_pressed = true;
      long_press_triggered = true;
    }
  }

  if (button_pressed) {
    switch (current_deepness) {
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
          case ARTNET_REC:
            if (artnet_var.get_current_fsm() == ARTNET_PAGE) {
              artnet_var.next_selection();
              display_artnet_rec(display, artnet_var);
            }
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
    current_deepness = main_sw.get_deepness();
    switch (current_deepness) {
      case MAIN_MENU:
        switch (artnet_var.get_current_fsm()) {
          case CONNECTING:
            artnet_var.set_current_fsm(MENU);
          case ARTNET_PAGE:
            artnet_var.stop_artnet();
            artnet_var.set_current_fsm(MENU);
            break;
        }
        break;
      case SUB_MENU:
        switch (main_state) {
          case ARTNET_NODE:
            artnet_var.add_channel_node(0);
            artnet_var.add_universe(0);
          case ARTNET_REC:
            switch (artnet_var.get_current_fsm()) {
              case MENU:
                artnet_var.connect_wifi();
                artnet_var.set_current_fsm(CONNECTING);
                display_connecting_artnet(display, artnet_var);
                last_added_dot = millis();
                break;
            }
            break;
        }
        break;
    }
    set_event_status(true);
    button_long_pressed = false;
  }

  // handle everything on event
  if (change_vals) {
    switch (current_deepness) {
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

          case ARTNET_REC:
            if (encoder_val != 0) {
              switch (artnet_var.get_current_fsm()) {
                case ARTNET_PAGE:
                  switch (artnet_var.get_current_sel()) {
                    case UNIVERSE:
                      artnet_var.add_universe(encoder_val);
                      break;
                    case CHANNEL:
                      if (main_state == ARTNET_NODE) {
                        artnet_var.add_channel_node(encoder_val);
                      } else {
                        artnet_var.add_channel(encoder_val);
                      }
                      break;
                  }
                  display_artnet_rec(display, artnet_var);
                  break;
              }
            }
            break;

          case SEGMENT_CNTRL:
            // if encoder val is zero, don't jump into functions
            if (encoder_val != 0) {
              seg.add_seg(encoder_val);
            }
            show_segments(seg.get_num_seg());
            dmx_val.set_number_segments(seg.get_num_seg());
            artnet_var.set_number_segments(seg.get_num_seg());
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
  switch (current_deepness) {
    case MAIN_MENU:
      break;
    case SUB_MENU:
      // save variables to EEPROM
      if (button_double_pressed) {
        write_eeprom(hsv_val, rgb_val, dmx_val, main_sw, artnet_var, seg);
        set_double_press(false);
        display_saved_status(display);
      }

      switch (main_state) {
        case DMX_PAGE:
          dmx_val.hanlde_dmx();
          if (dmx_val.get_rec_status()) {
            set_pixel(dmx_val.get_start(), dmx_val.get_dimmer_address(), seg.get_num_seg(), dmx_val.get_universe());
            dmx_val.set_rec_status(false);
          }
          break;

        case ARTNET_NODE:
          set_pixel(artnet_var.get_start_channel(), artnet_var.get_end_channel(), seg.get_num_seg(), artnet_var.get_current_data());
          dmx_val.send_universe();
        case ARTNET_REC:
          // on connection loss, jump to connecting state
          switch (artnet_var.get_current_fsm()) {
            case CONNECTING:
              if (!get_standby_status()) {
                if (millis() - last_added_dot >= add_dot_time) {
                  display_connecting_artnet(display, artnet_var);
                  artnet_var.add_dot();
                  last_added_dot = millis();
                }
              }
              if (artnet_var.get_wifi_status()) {
                artnet_var.set_current_fsm(ARTNET_PAGE);
                display_artnet_rec(display, artnet_var);
                artnet_var.begin_artnet();
              }
              break;

            case ARTNET_PAGE:
              // check connection is still available
              if (!artnet_var.get_wifi_status()) {
                artnet_var.set_current_fsm(CONNECTING);
              }

              artnet_var.artnet_parse();
              if (artnet_data) {
                output_artnet(artnet_var);
                artnet_data = false;
              }

              if (artnet_var.get_current_sel() == IP_ADDRESS && !get_standby_status()) {
                if (millis() - last_scroll_time >= scroll_time) {
                  scroll();
                  display_artnet_rec(display, artnet_var);
                  last_scroll_time = millis();
                }
              }
              break;
          }
          break;
      }
      break;
  }
}