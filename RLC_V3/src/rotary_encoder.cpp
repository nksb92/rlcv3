#include "rotary_encoder.h"

// Current value of the encoder
volatile int16_t enc_val = 0;

// Indicates whether there has been a change in the encoder or button state
bool change = true;

// Indicates whether the display is in standby mode
bool standby = false;

// Indicates whether the save screen is shown
bool save_screen = false;

// Indicates whether the button has been pressed
bool press = false;

bool long_press = false;

bool double_press = false;

void init_encoder(EncoderButton &eb)
{
  eb.setClickHandler(press_handler);
  eb.setDoubleClickHandler(double_press_handler);
  eb.setLongClickHandler(long_press_handler);
  eb.setEncoderHandler(encoder_handler);
  eb.setLongClickDuration(500);
  eb.setRateLimit(50);
  change = true;
}

void encoder_handler(EncoderButton &eb)
{
  if (!standby && !save_screen)
  {
    int temp = eb.increment();
    if (temp >= 0)
    {
      enc_val += temp * temp;
    }
    else
    {
      enc_val += (-1 * (temp * temp));
    }
  }
  if (!save_screen)
  {
    change = true;
  }
}

int16_t get_encoder_val()
{
  int16_t temp = enc_val;
  enc_val = 0;
  return temp;
}

void long_press_handler(EncoderButton &eb)
{
  if (!standby && !save_screen)
  {
    long_press = true;
  }
}

bool get_long_press()
{
  return long_press;
}

void set_long_press(bool state)
{
  long_press = state;
}

void press_handler(EncoderButton &eb)
{
  if (!standby)
  {
    press = true;
  }
  change = true;
}

bool get_press_state()
{
  return press;
}

void set_press_state(bool state)
{
  press = state;
}

void double_press_handler(EncoderButton &eb)
{
  if (!standby && !save_screen)
  {
    double_press = true;
  }
}

bool get_double_press()
{
  return double_press;
}

void set_double_press(bool state)
{
  double_press = state;
}

bool get_event_status()
{
  return change;
}

void set_event_status(bool state)
{
  change = state;
}

void set_dspl_standby(bool state)
{
  standby = state;
}

bool get_standby_status()
{
  return standby;
}

bool get_saved_screen_state()
{
  return save_screen;
}

void set_saved_screen(bool state)
{
  save_screen = state;
}
