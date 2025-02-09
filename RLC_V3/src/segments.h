#ifndef SEGMENTS_H
#define SEGMENTS_H

#include "common.h"

class segments
{
private:
  uint16_t number_segments = 0;
  uint8_t current_segment = 0;
  uint16_t last_segment = 0;
  uint16_t possible_segments[NUM_PIXEL];

  void calc_segments();

public:
  segments();
  void init_segments();
  uint16_t get_num_seg();
  uint8_t get_current_seg();
  void set_current_segment(uint8_t _current);
  void set_segments(uint8_t pos);
  void add_seg(int value);
};

#endif