/**
 * @file segments.cpp
 * @brief Implementation of LED segment layout and configuration options.
 */

#include "segments.h"

segments::segments() {
  number_segments = 1;
}

void segments::init_segments() {
  calc_segments();
  set_segments(0);
}

void segments::calc_segments() {
  uint16_t inc = 0;
  for (int i = 1; i < NUM_PIXEL + 1; i++) {
    if (NUM_PIXEL % i == 0) {
      possible_segments[inc] = i;
      inc++;
    }
  }

  uint16_t* possible_segments = new uint16_t(inc);
  last_segment = inc;
}

uint16_t segments::get_num_seg() {
  return number_segments;
}

uint8_t segments::get_current_seg() {
  return current_segment;
}

void segments::set_current_segment(uint8_t _current) {
  if (_current >= last_segment) {
    _current = 0;
  }
  current_segment = _current;
  add_seg(0);
}

void segments::set_segments(uint8_t pos) {
  number_segments = possible_segments[pos];
}

void segments::add_seg(int value) {
  if (value != 0) {
    if (value < 0) {
      if (current_segment - 1 >= 0) {
        current_segment--;
      } else {
        current_segment = last_segment - 1;
      }
    } else {
      if (current_segment + 1 < last_segment) {
        current_segment++;
      } else {
        current_segment = 0;
      }
    }
  }

  set_segments(current_segment);
}

uint8_t segments::get_dimmer_mode() {
  return dimmer_mode;
}

void segments::set_dimmer_mode(uint8_t mode) {
  dimmer_mode = mode;
}

void segments::add_dimmer_mode(int value) {
  if (value > 0) {
    dimmer_mode = (dimmer_mode + 1) > RGB_ONLY ? DIMMER_RGB : (dimmer_mode + 1);
  } else if (value < 0) {
    dimmer_mode = (dimmer_mode == 0) ? RGB_ONLY : (dimmer_mode - 1);
  }
}

uint8_t segments::get_white_mode() {
  return white_mode;
}

void segments::set_white_mode(uint8_t mode) {
  white_mode = mode;
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGB
  white_mode = WHITE_DISABLE;
#elif LED_COLOR_TYPE == LED_COLOR_TYPE_RGBW
  if (white_mode > WHITE_ONE_CH) white_mode = WHITE_DISABLE;
#elif LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  if (white_mode > WHITE_TWO_CH) white_mode = WHITE_DISABLE;
#endif
}

void segments::add_white_mode(int value) {
#if LED_COLOR_TYPE == LED_COLOR_TYPE_RGB
  white_mode = WHITE_DISABLE;
#elif LED_COLOR_TYPE == LED_COLOR_TYPE_RGBW
  if (value > 0) {
    white_mode = (white_mode + 1) > WHITE_ONE_CH ? WHITE_DISABLE : (white_mode + 1);
  } else if (value < 0) {
    white_mode = (white_mode == 0) ? WHITE_ONE_CH : (white_mode - 1);
  }
#elif LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT
  if (value > 0) {
    white_mode = (white_mode + 1) > WHITE_TWO_CH ? WHITE_DISABLE : (white_mode + 1);
  } else if (value < 0) {
    white_mode = (white_mode == 0) ? WHITE_TWO_CH : (white_mode - 1);
  }
#endif
}

uint8_t segments::get_value_mode() {
  return value_mode;
}

void segments::set_value_mode(uint8_t mode) {
  if (mode <= VALUE_FULL_RANGE) {
    value_mode = mode;
  }
}

void segments::add_value_mode(int value) {
  if (value > 0) {
    value_mode = (value_mode + 1) > VALUE_FULL_RANGE ? VALUE_PERCENTAGE : (value_mode + 1);
  } else if (value < 0) {
    value_mode = (value_mode == 0) ? VALUE_FULL_RANGE : (value_mode - 1);
  }
}
