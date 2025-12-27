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

// External references
extern Adafruit_SSD1306 display;
extern C_HSV hsv_val;
extern C_RGB rgb_val;
extern rgb_dmx dmx_val;
extern menu_structure main_sw;
extern segments seg;
extern rlc_artnet artnet_var;
extern settings_menu option_menu;

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
            case DMX_PAGE:
              break;
            case ARTNET_PAGE:
              artnet_var.next_selection();
              break;
            case SETTINGS_PAGE:
              option_menu.deeper();
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
            case SETTINGS_PAGE:
              if (option_menu.get_item() == FIRMWARE) {
                TimerManager.start(TIMER_RAINBOW_ANIM);
              }
              show_segments(seg.get_num_seg());
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

            case SETTINGS_PAGE:
              switch (option_menu.get_deepness()) {
                case ITEM_SELECTION:
                  option_menu.add_setting(delta_value);
                  if (option_menu.get_item() == SEGMENTS) {
                    show_segments(seg.get_num_seg());
                  }
                  if (option_menu.get_item() == FIRMWARE) {
                    TimerManager.start(TIMER_RAINBOW_ANIM);
                  } else {
                    TimerManager.stop(TIMER_RAINBOW_ANIM);
                  }
                  break;
                case VALUE_SELECTION:
                  if (option_menu.get_item() == SEGMENTS) {
                    seg.add_seg(delta_value);
                    show_segments(seg.get_num_seg());
                    dmx_val.set_number_segments(seg.get_num_seg());
                    artnet_var.set_number_segments(seg.get_num_seg());
                  }
                  break;
              }
#ifdef FAN_USAGE
              fan.evaluate_sum(128);
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
      write_eeprom(hsv_val, rgb_val, dmx_val, main_sw, artnet_var, seg);
      display_saved_status(display);
      display_enter_saved_screen();
      break;

    case EVT_NONE:
    default:
      break;
  }
}
