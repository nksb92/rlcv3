#if !defined(C_GRAD_H)
#define C_GRAD_H

#include <Arduino.h>

enum {
  GRAD_START_HUE,
  GRAD_START_SAT,
  GRAD_START_VAL,
  GRAD_END_HUE,
  GRAD_END_SAT,
  GRAD_END_VAL,
  GRAD_LAST
};

enum {
  GRAD_ITEM_SELECTION,
  GRAD_VALUE_SELECTION
};

class C_GRAD {
  uint8_t start_hue;
  uint8_t start_sat;
  uint8_t start_val;
  uint8_t end_hue;
  uint8_t end_sat;
  uint8_t end_val;

  uint8_t current_menu_item = GRAD_START_HUE;
  uint8_t current_deepness = GRAD_ITEM_SELECTION;

 public:
  C_GRAD(uint8_t _sh, uint8_t _ss, uint8_t _sv, uint8_t _eh, uint8_t _es, uint8_t _ev);
  ~C_GRAD();

  void add_setting(int value);
  void deeper();

  uint8_t get_deepness();
  uint8_t get_item();

  void add_value(int amount);

  uint8_t get_start_hue();
  uint8_t get_start_sat();
  uint8_t get_start_val();
  uint8_t get_end_hue();
  uint8_t get_end_sat();
  uint8_t get_end_val();

  void set_start_hue(uint8_t value);
  void set_start_sat(uint8_t value);
  void set_start_val(uint8_t value);
  void set_end_hue(uint8_t value);
  void set_end_sat(uint8_t value);
  void set_end_val(uint8_t value);
};

#endif  // C_GRAD_H
