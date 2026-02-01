#include "display_manager.h"

#include "common.h"
#include "soft_timer.h"

extern Adafruit_SSD1306 display;
extern C_HSV hsv_val;
extern C_RGB rgb_val;
extern rgb_dmx dmx_val;
extern menu_structure main_sw;
extern rlc_artnet artnet_var;
extern segments seg;
extern settings_menu option_menu;

bool display_is_standby = false;
bool display_is_saved_screen = false;

void display_show_menu() {
  if (main_sw.get_deepness() != MAIN_MENU) {
    return;
  }

  display_menu(display, main_sw.get_current());
}

void display_show_submenu() {
  if (main_sw.get_deepness() != SUB_MENU) {
    return;
  }

  uint8_t page = main_sw.get_current();

  switch (page) {
    case HSV_PAGE:
      hsv_display_update(display, hsv_val);
      break;
    case RGB_PAGE:
      rgb_display_update(display, rgb_val);
      break;
    case DMX_PAGE:
      dmx_display_update(display, dmx_val);
      break;
    case ARTNET_PAGE:
      display_artnet_rec(display, artnet_var, page);
      break;
    case SETTINGS_PAGE:
      settings_display_update(display, seg, option_menu.get_item(), option_menu.get_deepness());
      break;
  }
}

void display_enter_standby() {
  display_is_standby = true;
  display.clearDisplay();
  display.display();
}

void display_leave_standby() {
  display_is_standby = false;
  display_show_menu();
  display_show_submenu();
}

bool get_standby_status() {
  return display_is_standby;
}

void display_enter_saved_screen() {
  display_is_saved_screen = true;
  display_saved_status(display);
}

void display_leave_saved_screen() {
  display_is_saved_screen = false;
  display_show_menu();
  display_show_submenu();
}

bool get_saved_screen_state() {
  return display_is_saved_screen;
}