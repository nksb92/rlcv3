#include "rotary_encoder_events.h"

#include "std_defines.h"
#include "display_manager.h"

EncoderButton enc_button(DT_PIN, CLK_PIN, SW_PIN);

int16_t delta = 0;

static void on_click(EncoderButton& eb) {
  if (get_standby_status()) {
    event_manager.post(EVT_DISPLAY_WAKE);
  } else if (get_saved_screen_state()) {
    event_manager.post(EVT_LEAVE_SAVED_SCREEN);
  } else {
    event_manager.post(EVT_BUTTON_CLICK);
  }
}

static void on_long_press(EncoderButton& eb) {
  if (get_standby_status()) {
    event_manager.post(EVT_DISPLAY_WAKE);
  } else {
    if (get_saved_screen_state()) {
      event_manager.post(EVT_LEAVE_SAVED_SCREEN);
    }
    event_manager.post(EVT_BUTTON_LONG_PRESS);
  }
}

static void on_double_click(EncoderButton& eb) {
  if (get_standby_status()) {
    event_manager.post(EVT_DISPLAY_WAKE);
  } else {
    event_manager.post(EVT_BUTTON_DOUBLE_PRESS);
  }
}

static void on_encoder(EncoderButton& eb) {
  if (get_standby_status()) {
    event_manager.post(EVT_DISPLAY_WAKE);
  } else if (get_saved_screen_state()) {
    // do nothing with the values
    // user has to click ok first
    eb.resetPosition();
  } else {
    delta = eb.increment();
    if (delta != 0) {
      event_manager.post(EVT_ENCODER_CHANGED, (uint32_t)(int32_t)delta);
    }
  }
}

void init_encoder_with_events() {
  enc_button.setClickHandler(on_click);
  enc_button.setDoubleClickHandler(on_double_click);
  enc_button.setLongPressHandler(on_long_press);
  enc_button.setEncoderHandler(on_encoder);
  enc_button.setLongClickDuration(750);
  enc_button.setRateLimit(50);
}
