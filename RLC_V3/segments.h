#ifndef SEGMENTS_H
#define SEGMENTS_H

#include "common.h"

class segments {
private:
  uint16_t number_segments = 0;
  uint16_t leds_per_segment = 0;
  uint16_t channel_needed = 0;
  uint8_t current_segment = 0;
  uint16_t last_segment = 0;
  uint16_t possible_segments[NUM_PIXEL];

  void calc_segments();
  void set_segments(uint8_t pos);

public:
  segments();
  void init_segments();
  uint16_t get_num_seg();
  uint16_t get_leds_per_seg();
  uint16_t get_channel_needed();
  uint8_t get_current_seg();
  void add_seg(int value);
};

#endif