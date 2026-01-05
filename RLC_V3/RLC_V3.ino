/*

  Project:          RLC_V3
  Author:           Niko Kassubek
  Microcontroller:  SeeedStudio XIAO ESP32-C3

*/

/*
  Architecture Overview:
  This project utilizes a hybrid Event-Driven architecture combined with a polling loop for real-time tasks.

  1. Event System: User inputs (Rotary Encoder), Timers, and System changes generate events posted to a queue (EventManager).
  2. Event Handler: The main loop processes these events to update the application state (Menu, LED values, Settings) and trigger UI updates.
  3. Continuous Tasks: High-bandwidth tasks like DMX and ArtNet processing run continuously in the main loop to ensure low latency.
  4. Modularity: Hardware abstraction layers exist for Display, LEDs, DMX, and NVM (EEPROM), keeping the main logic decoupled from hardware specifics.
*/

/* ************ LIBRARY DEPENDENCIES ************ **

  Make sure, to have these library versions installed,
  otherwise it may break this code!

  esp core:             version 3.30.3

  Adafruit GFX Library: version 1.12.1
  Adafruit NeoPixel:    version 1.13.0
  Adafruit SSD1306:     version 2.5.14
  ArtnetWifi:           version 1.6.1
  EncoderButton:        version 1.0.6
  FastLED:              version 3.9.16
  esp_dmx:              version 4.1.0 -> needs fix https://github.com/someweisguy/esp_dmx/issues/181#issuecomment-2619261884

** ************ LIBRARY DEPENDENCIES ************ */

#include "continuous_tasks.h"
#include "display.h"
#include "dmx.h"
#include "event_handler.h"
#include "event_manager.h"
#include "leds.h"
#include "nvm.h"
#include "rlc_artnet.h"
#include "rotary_encoder_events.h"
#include "segments.h"
#include "soft_timer.h"

#ifdef FAN_USAGE
#include "fan_control.h"
#endif

#include "common.h"

// --- Globals: State ---
bool artnet_data = false;

// --- Globals: Objects ---
C_HSV hsv_val(STD_HUE, STD_SAT, STD_VAL);
C_RGB rgb_val(STD_RED, STD_GREEN, STD_BLUE);
rlc_artnet artnet_var;
menu_structure main_sw;
segments seg;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
settings_menu option_menu;

event_t event;

#ifdef FAN_USAGE
fan_control fan;
#endif

void startup_wrapper();
void startup_wrapper() {
  uint8_t current_deepness = main_sw.get_deepness();
  uint8_t main_state = main_sw.get_current();
  int steps = STARTUP_TIME / FRAME_DELAY;

  if (current_deepness == SUB_MENU) {
    uint8_t target_val = hsv_val.get_val();

    for (int i = 0; i <= steps; i++) {
      display_startup(display);
      if (main_state == HSV_PAGE) {
        C_HSV temp_hsv = hsv_val;
        int val = map(i, 0, steps, 0, target_val);
        temp_hsv.set_val(val);
        hsv_out(temp_hsv);
      } else if (RGB_PAGE == main_state) {
        int factor = map(i, 0, steps, 0, 255);
        rgb_out(rgb_val.get_rgb(), factor);
      }
      delay(FRAME_DELAY);
    }
    if (main_state == ARTNET_PAGE) {
      artnet_var.connect_wifi();
      artnet_var.set_current_fsm(CONNECTING);
      TimerManager.start(TIMER_CONNECTING_DOTS);
    }
  } else {
    for (int i = 0; i < steps; i++) {
      display_startup(display);
      delay(FRAME_DELAY);
    }
  }
}

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
// init fan instantly
#ifdef DEBUGGING_ENABLED
  Serial.begin(115200);
#endif

#ifdef FAN_USAGE
  fan.init_fan();
  DEBUG_PRINTLN("FAN INIT DONE");
#endif

  // sanity delay
  delay(500);

  DEBUG_PRINTLN("Startup");

  // init event system
  event_manager.init();
  DEBUG_PRINTLN("EVENT MANAGER INIT DONE");

  TimerManager.init();
  DEBUG_PRINTLN("SOFT TIMER INIT DONE");

  // init all classes and functions
  main_sw.init();
  DEBUG_PRINTLN("MAIN INIT DONE");

  init_eeprom();
  DEBUG_PRINTLN("EEPROM INIT DONE");

  init_display(display);
  DEBUG_PRINTLN("DISPLAY INIT DONE");

  init_led();
  DEBUG_PRINTLN("LED INIT DONE");

  init_encoder_with_events();
  DEBUG_PRINTLN("ENCODER INIT DONE");

  dmx_val.install_dmx();
  DEBUG_PRINTLN("DMX INIT DONE");

  seg.init_segments();
  DEBUG_PRINTLN("SEGMENT INIT DONE");

  artnet_var.init(on_artnet_frame);
  DEBUG_PRINTLN("ARTNET INIT DONE");

  // read non volatile memory and set variables accordingly
  read_eeprom(hsv_val, rgb_val, dmx_val, main_sw, artnet_var, seg);

  startup_wrapper();

  // wake up display and Start display standby timer
  event_manager.post(EVT_DISPLAY_WAKE);
  TimerManager.start(TIMER_DISPLAY_STANDBY);

#ifdef FAN_USAGE
  TimerManager.start(TIMER_UPDATE_FAN);
  if (main_sw.get_deepness() == SUB_MENU) {
    if (main_sw.get_current() == HSV_PAGE) {
      fan.calc_hsv_speed(hsv_val);
    } else if (main_sw.get_current() == RGB_PAGE) {
      fan.calc_rgb_speed(rgb_val.get_rgb());
    }
  }
#endif

  DEBUG_PRINTLN("Startup complete.");
}

void loop() {
  enc_button.update();

  // Update timers (posts events on expiry)
  TimerManager.update();

  // Process all pending events
  if (event_manager.get_event(&event)) {
    process_event(&event);
  }

  // Handle continuous tasks (DMX, Artnet - NOT event driven)
  handle_continuous_tasks();
}