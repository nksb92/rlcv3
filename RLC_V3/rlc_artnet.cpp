#include "WiFiType.h"
#include "rlc_artnet.h"

ArtnetWifi artnet;
int previousDataLength = 0;
const char* ssid = "ARTNET_RLCV3";
const char* pwd = "123456789";
uint32_t number_channel = 0;

rlc_artnet::rlc_artnet() {
}

rlc_artnet::~rlc_artnet() {
}

void rlc_artnet::init(void (*fptr)(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)) {
  artnet.setArtDmxCallback(fptr);
  add_universe(0);
  add_channel(0);
  stop_artnet();
}

void rlc_artnet::begin_artnet() {
  if (get_wifi_status()) {
    artnet.begin();
  }
}

void rlc_artnet::stop_artnet() {
  // newest version has stop member in class, not updated yet to arduino
  // https://github.com/rstephan/ArtnetWifi/blob/master/src/ArtnetWifi.cpp
  // artnet.stop();

  disconnect_wifi();
  WiFi.mode(WIFI_OFF);
}

void rlc_artnet::connect_wifi() {
  WiFi.begin(ssid, pwd);
}

void rlc_artnet::disconnect_wifi() {
  WiFi.disconnect();
}

void rlc_artnet::next_selection() {
  current++;
  if (current >= ARTNET_LAST) current = UNIVERSE;
}

void rlc_artnet::add_universe(int value) {
  int temp = current_universe + value;
  if (temp < 0) {
    current_universe = 0;
  } else if (temp > LAST_UNIVERSE) {
    current_universe = LAST_UNIVERSE;
  } else {
    current_universe = temp;
  }
  if (channel_start + used_channel > UNIVERSE_SIZE) {
    last_used_universe = current_universe + 1;
  } else {
    last_used_universe = current_universe;
  }
}

void rlc_artnet::add_channel(int value) {
  int temp = channel_start + value;

  if (temp < FIRST_DMX_ADDRESS) {
    channel_start = LAST_DMX_ADDRESS;
  } else if (temp > LAST_DMX_ADDRESS) {
    channel_start = FIRST_DMX_ADDRESS;
  } else {
    channel_start = temp;
  }

  if (channel_start + used_channel > UNIVERSE_SIZE) {
    last_used_universe = current_universe + 1;
    last_channel = ((channel_start + used_channel) % LAST_DMX_ADDRESS) - 1;  // - 1 -> because 0 is not a valid address
  } else {
    last_used_universe = current_universe;
    last_channel = channel_start + used_channel - 1;
  }
}

void rlc_artnet::add_dot() {
  number_dots++;
  if (number_dots > 3) number_dots = 1;
}

void rlc_artnet::add_channel_node(int value) {
  int temp = channel_start + value;
  if (temp > last_address) {
    channel_start = 1;
  } else if (temp < 1) {
    channel_start = last_address;
  } else {
    channel_start = temp;
  }
  last_channel = channel_start + used_channel - 1;
}

void rlc_artnet::artnet_parse() {
  artnet.read();
}

/* GETTER FUNCTIONS */
/* --------------------------------------------------------------- */
bool rlc_artnet::get_wifi_status() {
  bool state = false;
  wl_status_t status = WiFi.status();
  if (status == WL_CONNECTED) state = true;
  return state;
}

String rlc_artnet::get_wifi_local_ip() {
  return WiFi.localIP().toString();
}

uint16_t rlc_artnet::get_start_universe() {
  return current_universe;
}

uint16_t rlc_artnet::get_end_universe() {
  return last_used_universe;
}

uint16_t rlc_artnet::get_start_channel() {
  return channel_start;
}

uint16_t rlc_artnet::get_end_channel() {
  return last_channel;
}

uint16_t rlc_artnet::get_used_channel() {
  return used_channel;
}

uint16_t rlc_artnet::get_section_number() {
  return number_segments;
}

uint8_t rlc_artnet::get_current_sel() {
  return current;
}

uint8_t rlc_artnet::get_current_fsm() {
  return current_fsm;
}

uint8_t rlc_artnet::get_number_dots() {
  return number_dots;
}

uint8_t* rlc_artnet::get_current_data() {
  return data_current_universe;
}

uint8_t* rlc_artnet::get_next_data() {
  return data_next_universe;
}

/* SETTER FUNCTIONS */
/* --------------------------------------------------------------- */
void rlc_artnet::set_number_segments(uint16_t _segments) {
  number_segments = _segments;
  used_channel = number_segments * 3 + 1;  // RGB for each segment + one channel for dimmer
  last_address = UNIVERSE_SIZE - used_channel;
  // update values
  add_channel(0);
  add_universe(0);
}

void rlc_artnet::set_current_universe(uint8_t* data) {
  memcpy(data_current_universe, data, UNIVERSE_SIZE);
}

void rlc_artnet::set_next_universe(uint8_t* data) {
  memcpy(data_next_universe, data, UNIVERSE_SIZE);
}

void rlc_artnet::set_current_fsm(uint8_t val) {
  current_fsm = val;
}

void rlc_artnet::set_current_universe_nmbr(uint16_t val) {
  current_universe = 0;
  add_universe(val);
}

void rlc_artnet::set_current_channel(uint16_t channel) {
  channel_start = 0;
  add_channel(channel);
}

void rlc_artnet::set_dots(uint8_t _dots)
{
  number_dots = _dots;
}
