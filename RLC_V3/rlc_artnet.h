#ifndef RLC_ARTNET_H
#define RLC_ARTNET_H

#include "common.h"
#include <ArtnetWifi.h>

#define UNIVERSE_SIZE 513
#define LAST_DMX_ADDRESS 512
#define FIRST_DMX_ADDRESS 1
#define LAST_UNIVERSE 99  // theroretical number of supported universes 32768, limited to 100 (0-99)

enum {
  MENU,
  CONNECTING,
  ARTNET_PAGE
};

enum {
  UNIVERSE,
  CHANNEL,
  IP_ADDRESS,
  ARTNET_LAST
};

class rlc_artnet {
private:
  uint16_t current_universe = 0;
  uint16_t last_used_universe = 0;
  uint16_t channel_start = 1;
  uint16_t last_channel = 0;
  uint16_t used_channel = 4;
  uint16_t number_segments = 1;
  uint16_t last_address = UNIVERSE_SIZE - used_channel;
  uint8_t current = UNIVERSE;
  uint8_t current_fsm = MENU;
  volatile uint8_t number_dots = 1;
  uint8_t data_current_universe[UNIVERSE_SIZE] = {};
  uint8_t data_next_universe[UNIVERSE_SIZE] = {};

public:
  rlc_artnet();
  ~rlc_artnet();
  void init(void (*fptr)(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data));
  void begin_artnet();
  void stop_artnet();
  void connect_wifi();
  void disconnect_wifi();

  // channel and universe manipulation
  void next_selection();
  void add_universe(int value);
  void add_channel(int value);
  void add_dot();
  void add_channel_node(int value);

  // artnet and dmx functions
  void artnet_parse();

  /* GETTER FUNCTIONS */
  bool get_wifi_status();
  String get_wifi_local_ip();
  uint16_t get_start_universe();
  uint16_t get_end_universe();
  uint16_t get_start_channel();
  uint16_t get_end_channel();
  uint16_t get_used_channel();
  uint16_t get_section_number();
  uint8_t get_current_sel();
  uint8_t get_current_fsm();
  uint8_t get_number_dots();
  uint8_t* get_current_data();
  uint8_t* get_next_data();

  /* SETTER FUNCTIONS */
  void set_number_segments(uint16_t _segments);
  void set_current_universe(uint8_t* data);
  void set_next_universe(uint8_t* data);
  void set_current_fsm(uint8_t val);
};

#endif