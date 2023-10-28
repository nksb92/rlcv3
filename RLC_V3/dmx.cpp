#include "dmx.h"

/*
Pins for the communication with the RS-485 IC
@param TRANSMIT_PIN: pin for sending data
@param RECEIVE_PIN: pin for receiving data
@param ENABLE_PIN: pin to pull RS-485 IC high or low; high for sending data, low for receiving data
*/
#define TRANSMIT_PIN 21
#define RECEIVE_PIN 20
#define ENABLE_PIN 5

rgb_dmx::rgb_dmx(CRGB init_rgb)
  : modes({ "Wire", "Sender", "Receiver" }) {

  dmx_message = init_rgb;
}

uint8_t rgb_dmx::get_current() {
  return current;
}

void rgb_dmx::set_current(uint8_t _current) {
  if (_current >= DMX_LAST) {
    current = DMX_LAST - 1;
  } else {
    current = _current;
  }
}

void rgb_dmx::next() {
  current++;
  if (current >= DMX_LAST) {
    current = 0;
  }
}

char* rgb_dmx::get_current_txt() {
  return modes[current];
}

void rgb_dmx::install_dmx() {
  dmx_driver_install(dmxPort, &config, DMX_INTR_FLAGS_DEFAULT);
  dmx_set_pin(dmxPort, TRANSMIT_PIN, RECEIVE_PIN, ENABLE_PIN);
}

uint16_t rgb_dmx::get_start() {
  return start_address;
}

uint16_t rgb_dmx::get_used_nbr() {
  return used_addresses;
}

void rgb_dmx::add_to_adress(int value) {
  int temp = start_address + value;
  if (temp > last_address) {
    start_address = 1;
  } else if (temp < 1) {
    start_address = last_address;
  } else {
    start_address = temp;
  }
}

void rgb_dmx::set_start_address(int start) {
  start_address = 1;
  add_to_adress(start - 1);
}

void rgb_dmx::set_rgb() {
  dmx_message.r = data[start_address + 0];
  dmx_message.g = data[start_address + 1];
  dmx_message.b = data[start_address + 2];
  dim = data[start_address + 3];  // dimming factor
  dmx_message.nscale8(dim);
}

void rgb_dmx::hanlde_dmx() {
  if (current == WIRE || current == SENDER) {
    dmx_packet_t packet;
    if (dmx_receive(dmxPort, &packet, 5)) {
      if (!packet.err) {
        dmx_read(dmxPort, data, packet.size);
        set_rgb();
      }
    }
  } else if (current == RECEIVER) {
    set_rgb();
  }
}

CRGB rgb_dmx::get_dmx_message() {
  return dmx_message;
}

void rgb_dmx::set_data(uint8_t information, uint16_t index) {
  data[index] = information;
}

uint8_t rgb_dmx::get_data(uint16_t index) {
  return data[index];
}

void rgb_dmx::set_number_segments(uint16_t num_segs) {
  number_segments = num_segs;
  leds_per_segment = NUM_PIXEL / number_segments;
  used_addresses = number_segments * 3 + 1;  // RGB for each segment + one channel for dimmer
  last_address = 512 - used_addresses + 1;
}