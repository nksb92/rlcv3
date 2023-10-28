#include "segments.h"

segments::segments() {
  number_segments = 1;
}

void segments::init_segments() {
  calc_segments();
  set_segments(0);
}

void segments::set_segments(uint8_t pos) {
  number_segments = possible_segments[pos];

}

void segments::calc_segments() {
  uint16_t inc = 0;
  for (int i = 1; i < NUM_PIXEL + 1; i++) {
    if (NUM_PIXEL % i == 0) {
      possible_segments[inc] = i;
      inc++;
    }
  }

  uint16_t *possible_segments = new uint16_t(inc);
  last_segment = inc;
}

uint16_t segments::get_num_seg() {
  return number_segments;
}

uint8_t segments::get_current_seg() {
  return current_segment;
}

void segments::add_seg(int value) {
  // Serial.print(current_segment);
  // Serial.print("; ");
  // Serial.println(value);
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
  // Serial.print(current_segment);
  // Serial.print(";");
  // Serial.println(possible_segments[current_segment]);
  set_segments(current_segment);
}
