#ifndef SEGMENTS_H
#define SEGMENTS_H

#include "common.h"

enum DimmerMode {
  DIMMER_RGB,
  RGB_DIMMER,
  RGB_ONLY
};

enum WhiteMode {
  WHITE_DISABLE,
  WHITE_ONE_CH,
  WHITE_TWO_CH
};

class segments {
 private:
  uint16_t number_segments = 0;
  uint8_t current_segment = 0;
  uint16_t last_segment = 0;
  uint16_t possible_segments[NUM_PIXEL];

  uint8_t dimmer_mode = RGB_DIMMER;
  uint8_t white_mode = WHITE_DISABLE;

  void calc_segments();

 public:
  segments();
  void init_segments();
  uint16_t get_num_seg();
  uint8_t get_current_seg();
  void set_current_segment(uint8_t _current);
  void set_segments(uint8_t pos);
  void add_seg(int value);

  uint8_t get_dimmer_mode();
  void set_dimmer_mode(uint8_t mode);
  void add_dimmer_mode(int value);

  uint8_t get_white_mode();
  void set_white_mode(uint8_t mode);
  void add_white_mode(int value);
};

#endif