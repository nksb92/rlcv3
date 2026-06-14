#include "event_handler.h"

#include "common.h"
#include "display.h"
#include "display_manager.h"
#include "leds.h"
#include "nvm.h"
#include "soft_timer.h"
#include "std_defines.h"

#ifdef FAN_USAGE
#include "fan_control.h"
#endif

#include "c_grad.h"

// External references
extern Adafruit_SSD1306 display;
extern C_HSV hsv_val;
extern C_RGB rgb_val;
extern c_cct cct_val;
extern rgb_dmx dmx_val;
extern menu_structure main_sw;
extern segments seg;
extern rlc_artnet artnet_var;
extern settings_menu option_menu;
extern C_GRAD grad_val;

int16_t delta_value = 0;

#ifdef FAN_USAGE
extern fan_control fan;
#endif

void process_event(const event_t* event) {
  uint8_t current_deepness = main_sw.get_deepness();
  uint8_t main_state = main_sw.get_current();

  switch (event->id) {
    // ===================== INPUT EVENTS =====================
    case EVT_BUTTON_CLICK:
      DEBUG_PRINTLN("PRESS");
      TimerManager.restart(TIMER_DISPLAY_STANDBY);

      switch (current_deepness) {
        case MAIN_MENU:
          display_show_menu();
          break;

        case SUB_MENU:
          switch (main_state) {
            case HSV_PAGE:
              hsv_val.next();
              break;
            case RGB_PAGE:
              rgb_val.next();
              break;
            case CCT_PAGE:
              cct_val.next();
              break;
            case DMX_PAGE:
              break;
            case ARTNET_PAGE:
              artnet_var.next_selection();
              break;
#if NUM_PIXEL > 1
            case GRAD_PAGE:
              grad_val.deeper();
              break;
#endif
            case SETTINGS_PAGE:
              if (option_menu.get_deepness() == VALUE_SELECTION && option_menu.get_item() == RESET_OPTION && option_menu.get_reset_confirm() == 1) {
                factory_reset();
              } else {
                if (option_menu.get_item() == RESET_OPTION) {
                  option_menu.clear_reset_confirm();
                }
                option_menu.deeper();
              }
              break;
          }
          display_show_submenu();
          break;
      }
      break;

    case EVT_BUTTON_LONG_PRESS:
      DEBUG_PRINTLN("LONG PRESS");
      TimerManager.restart(TIMER_DISPLAY_STANDBY);

      main_sw.deeper();
      current_deepness = main_sw.get_deepness();

      switch (current_deepness) {
        case MAIN_MENU:
          dmx_val.disable();
          TimerManager.start(TIMER_FAN_COOLDOWN);

          if (artnet_var.get_current_fsm() == CONNECTING || artnet_var.get_current_fsm() == ARTNET_CONNECTED) {
            artnet_var.stop_artnet();
            artnet_var.set_current_fsm(MENU);
          }

          TimerManager.stop(TIMER_SCROLL_TEXT);
          TimerManager.stop(TIMER_CONNECTING_DOTS);
          TimerManager.stop(TIMER_RAINBOW_ANIM);
          rgb_out(rgb_val.get_rgb(), 0);
          display_show_menu();
          break;

        case SUB_MENU:
          TimerManager.stop(TIMER_FAN_COOLDOWN);

          switch (main_state) {
            case HSV_PAGE:
              hsv_out(hsv_val);
#ifdef FAN_USAGE
              fan.calc_hsv_speed(hsv_val);
#endif
              break;
            case RGB_PAGE:
              rgb_out(rgb_val.get_rgb(), 255);
#ifdef FAN_USAGE
              fan.calc_rgb_speed(rgb_val.get_rgb());
#endif
              break;
            case CCT_PAGE:
              cct_out(cct_val);
#ifdef FAN_USAGE
              fan.calc_hsv_speed(hsv_val); // Fallback to HSV speed logic for fan when in CCT, or omit if not desired
#endif
              break;
            case DMX_PAGE:
              dmx_val.enable();
              dmx_val.reset();
              break;
            case ARTNET_PAGE:
              if (artnet_var.get_current_fsm() == MENU) {
                artnet_var.connect_wifi();
                artnet_var.set_current_fsm(CONNECTING);
                TimerManager.start(TIMER_CONNECTING_DOTS);
                TimerManager.start(TIMER_SCROLL_TEXT);
              }
              break;
#if NUM_PIXEL > 1
            case GRAD_PAGE:
              grad_out(grad_val);
              break;
#endif
            case SETTINGS_PAGE:
              if (option_menu.get_item() == FIRMWARE) {
                TimerManager.start(TIMER_RAINBOW_ANIM);
              } else if (option_menu.get_item() == SEGMENTS) {
                show_segments(seg.get_num_seg());
              } else {
                rgb_out(rgb_val.get_rgb(), 0);
              }
              break;
          }
          display_show_submenu();
          break;
      }
      break;

    case EVT_BUTTON_DOUBLE_PRESS:
      DEBUG_PRINTLN("DOUBLE PRESS");
      TimerManager.restart(TIMER_DISPLAY_STANDBY);

      if (current_deepness == SUB_MENU && main_state != SETTINGS_PAGE) {
        event_manager.post(EVT_SAVE_TO_NVM);
      }
      break;

    case EVT_ENCODER_CHANGED:
      DEBUG_PRINTLN("ENCODER CHANGE");
      TimerManager.restart(TIMER_DISPLAY_STANDBY);
      delta_value = (int16_t)event->param;

      switch (current_deepness) {
        case MAIN_MENU:
          main_sw.add_current(delta_value);
          display_show_menu();
          rgb_out(rgb_val.get_rgb(), 0);
          break;

        case SUB_MENU:
          switch (main_state) {
            case HSV_PAGE:
              switch (hsv_val.get_current()) {
                case HUE:
                  hsv_val.add_hue(delta_value);
                  break;
                case SAT:
                  hsv_val.add_sat(delta_value);
                  break;
                case VAL:
                  hsv_val.add_val(delta_value);
                  break;
              }
              hsv_out(hsv_val);
#ifdef FAN_USAGE
              fan.calc_hsv_speed(hsv_val);
#endif
              break;

            case RGB_PAGE:
              switch (rgb_val.get_current()) {
                case RED:
                  rgb_val.add_red(delta_value);
                  break;
                case GREEN:
                  rgb_val.add_green(delta_value);
                  break;
                case BLUE:
                  rgb_val.add_blue(delta_value);
                  break;
              }
              rgb_out(rgb_val.get_rgb(), 255);
#ifdef FAN_USAGE
              fan.calc_rgb_speed(rgb_val.get_rgb());
#endif
              break;

            case CCT_PAGE:
              switch (cct_val.get_current()) {
                case CCT_KELVIN:
                  cct_val.add_kelvin(delta_value);
                  break;
                case CCT_BRIGHTNESS:
                  cct_val.add_brightness(delta_value);
                  break;
              }
              cct_out(cct_val);
#ifdef FAN_USAGE
              fan.calc_hsv_speed(hsv_val);
#endif
              break;

            case DMX_PAGE:
              dmx_val.add_to_adress(delta_value);

              break;

            case ARTNET_PAGE:
              switch (artnet_var.get_current_sel()) {
                case UNIVERSE:
                  artnet_var.add_universe(delta_value);
                  break;
                case CHANNEL:
                  artnet_var.add_channel(delta_value);
                  break;
              }
              break;

#if NUM_PIXEL > 1
            case GRAD_PAGE:
              switch (grad_val.get_deepness()) {
                case GRAD_ITEM_SELECTION:
                  grad_val.add_setting(delta_value);
                  break;
                case GRAD_VALUE_SELECTION:
                  grad_val.add_value(delta_value);
                  grad_out(grad_val);
                  break;
              }
              break;
#endif

            case SETTINGS_PAGE:
              switch (option_menu.get_deepness()) {
                case ITEM_SELECTION:
                  option_menu.add_setting(delta_value);
                  if (option_menu.get_item() == SEGMENTS) {
                    show_segments(seg.get_num_seg());
                  } else if (option_menu.get_item() == FIRMWARE) {
                    TimerManager.start(TIMER_RAINBOW_ANIM);
                  } else {
                    TimerManager.stop(TIMER_RAINBOW_ANIM);
                    rgb_out(rgb_val.get_rgb(), 0);
                  }
                  break;
                case VALUE_SELECTION:
                  if (option_menu.get_item() == SEGMENTS) {
                    seg.add_seg(delta_value);
                    show_segments(seg.get_num_seg());
                    dmx_val.set_number_segments(seg.get_num_seg(), seg.get_dimmer_mode(), seg.get_white_mode());
                    artnet_var.set_number_segments(seg.get_num_seg(), seg.get_dimmer_mode(), seg.get_white_mode());
                  } else if (option_menu.get_item() == DIMMER_OPTION) {
                    seg.add_dimmer_mode(delta_value);
                    dmx_val.set_number_segments(seg.get_num_seg(), seg.get_dimmer_mode(), seg.get_white_mode());
                    artnet_var.set_number_segments(seg.get_num_seg(), seg.get_dimmer_mode(), seg.get_white_mode());
                  } else if (option_menu.get_item() == WHITE_OPTION) {
                    seg.add_white_mode(delta_value);
                    dmx_val.set_number_segments(seg.get_num_seg(), seg.get_dimmer_mode(), seg.get_white_mode());
                    artnet_var.set_number_segments(seg.get_num_seg(), seg.get_dimmer_mode(), seg.get_white_mode());
                  } else if (option_menu.get_item() == VALUE_MODE_OPTION) {
                    uint8_t old_mode = seg.get_value_mode();
                    seg.add_value_mode(delta_value);
                    if (old_mode != seg.get_value_mode()) {
                      if (seg.get_value_mode() == VALUE_PERCENTAGE) {
                        hsv_val.set_sat(map(hsv_val.get_sat(), 0, 255, 0, 100));
                        hsv_val.set_val(map(hsv_val.get_val(), 0, 255, 0, 100));
                        cct_val.set_brightness(map(cct_val.get_brightness(), 0, 255, 0, 100));
#if NUM_PIXEL > 1
                        grad_val.set_start_sat(map(grad_val.get_start_sat(), 0, 255, 0, 100));
                        grad_val.set_start_val(map(grad_val.get_start_val(), 0, 255, 0, 100));
                        grad_val.set_end_sat(map(grad_val.get_end_sat(), 0, 255, 0, 100));
                        grad_val.set_end_val(map(grad_val.get_end_val(), 0, 255, 0, 100));
#endif
                      } else {
                        hsv_val.set_sat(map(hsv_val.get_sat(), 0, 100, 0, 255));
                        hsv_val.set_val(map(hsv_val.get_val(), 0, 100, 0, 255));
                        cct_val.set_brightness(map(cct_val.get_brightness(), 0, 100, 0, 255));
#if NUM_PIXEL > 1
                        grad_val.set_start_sat(map(grad_val.get_start_sat(), 0, 100, 0, 255));
                        grad_val.set_start_val(map(grad_val.get_start_val(), 0, 100, 0, 255));
                        grad_val.set_end_sat(map(grad_val.get_end_sat(), 0, 100, 0, 255));
                        grad_val.set_end_val(map(grad_val.get_end_val(), 0, 100, 0, 255));
#endif
                      }
                    }
                  } else if (option_menu.get_item() == RESET_OPTION) {
                    option_menu.add_reset_confirm(delta_value);
                  }
                  break;
              }
#ifdef FAN_USAGE
              fan.evaluate_sum(510);
#endif
              break;
          }
          display_show_submenu();
          break;
      }
      break;

    // ===================== TIMER EVENTS =====================
    case EVT_DISPLAY_STANDBY:
      DEBUG_PRINTLN("STANDBY");
      TimerManager.stop(TIMER_DISPLAY_STANDBY);
      display_enter_standby();
      break;

    case EVT_FAN_COOLDOWN:
#ifdef FAN_USAGE
      fan.set_target_speed(FAN_MIN_SPEED);
#endif
      break;

    case EVT_UPDATE_FAN:
#ifdef FAN_USAGE
      fan.update();
#endif
      break;

    case EVT_SCROLL_TICK:
      if (!get_standby_status() && !get_saved_screen_state()) {
        scroll();
        display_show_submenu();
      }
      break;

    case EVT_CONNECTING_DOTS_TICK:
      if (!get_standby_status() && !get_saved_screen_state()) {
        display_show_submenu();
        artnet_var.add_dot();
      }
      break;

    case EVT_RAINBOW_TICK:
      rainbow_fw();
      break;

    // ===================== SYSTEM EVENTS =====================
    case EVT_DISPLAY_WAKE:
      DEBUG_PRINTLN("WAKEUP");
      TimerManager.restart(TIMER_DISPLAY_STANDBY);
      display_leave_standby();
      break;

    case EVT_LEAVE_SAVED_SCREEN:
      DEBUG_PRINTLN("LEAVE SAVED SCREEN");
      display_leave_saved_screen();
      break;

    case EVT_WIFI_CONNECTED:
      DEBUG_PRINTLN("WIFI CONNECTED");
      artnet_var.set_current_fsm(ARTNET_CONNECTED);
      artnet_var.set_dots(3);
      artnet_var.begin_artnet();
      TimerManager.stop(TIMER_CONNECTING_DOTS);
      TimerManager.start(TIMER_SCROLL_TEXT);
      if (!get_standby_status() && !get_saved_screen_state()) {
        display_show_submenu();
      }
      break;

    case EVT_WIFI_DISCONNECTED:
      DEBUG_PRINTLN("WIFI DISCONNECTED");
      artnet_var.set_current_fsm(CONNECTING);
      TimerManager.start(TIMER_SCROLL_TEXT);
      TimerManager.start(TIMER_CONNECTING_DOTS);
      break;

    case EVT_SAVE_TO_NVM:
      DEBUG_PRINTLN("SAVE TO NVM");
      write_eeprom(hsv_val, rgb_val, cct_val, dmx_val, main_sw, artnet_var, seg, grad_val);
      display_saved_status(display);
      display_enter_saved_screen();
      break;

    case EVT_NONE:
    default:
      break;
  }
}
