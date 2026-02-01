#include "dmx.h"

#include "hal/uart_ll.h"
#include "soc/system_struct.h"
#include "soc/uart_struct.h"
/*
Pins for the communication with the RS-485 IC
@param TRANSMIT_PIN: pin for sending dmx_data
@param RECEIVE_PIN: pin for receiving dmx_data
@param ENABLE_PIN: pin to pull RS-485 IC high or low; high for sending dmx_data, low
for receiving dmx_data
*/
#define TRANSMIT_PIN D6
#define RECEIVE_PIN D7
#define ENABLE_PIN D3

rgb_dmx dmx_val;

rgb_dmx::rgb_dmx() {}

void rgb_dmx::install_dmx() {
  dmx_driver_install(dmxPort, &config, NULL, 0);
#ifdef SPOT
  // dont use the enable pin, because of a double pin assignment
  // with the fan control on the spotlight hardware
  dmx_set_pin(dmxPort, TRANSMIT_PIN, RECEIVE_PIN, NO_PIN);
#else
  dmx_set_pin(dmxPort, TRANSMIT_PIN, RECEIVE_PIN, ENABLE_PIN);
#endif
}

void rgb_dmx::reset() {
  dmx_driver_disable(dmxPort);

  uart_dev_t* hw = (dmxPort == 1) ? &UART1 : &UART0;

  // Reset FIFOs
  hw->conf0.txfifo_rst = 1;
  hw->conf0.txfifo_rst = 0;
  hw->conf0.rxfifo_rst = 1;
  hw->conf0.rxfifo_rst = 0;

  // Clear Interrupt Flags
  hw->int_clr.val = 0xFFFFFFFF;

  memset(dmx_data, 0, UNIVERSE_SIZE);

  dmx_driver_enable(dmxPort);

  data_received = false;
  delay(10);
}

void rgb_dmx::disable() {
  if (dmx_driver_is_enabled(dmxPort)) {
    dmx_driver_disable(dmxPort);
  }
}

void rgb_dmx::enable() {
  if (!dmx_driver_is_enabled(dmxPort)) {
    dmx_driver_enable(dmxPort);
  }
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

void rgb_dmx::handle_dmx() {
  dmx_packet_t packet;
  if (dmx_receive(dmxPort, &packet, 5)) {
    if (!packet.err) {
      if (packet.size > 0) {
        uint8_t _data[UNIVERSE_SIZE] = {};
        dmx_read(dmxPort, _data, packet.size);
        set_universe(_data);
        data_received = true;
      } else {
        data_received = false;
      }
    } else {
      // handle error cases
      switch (packet.err) {
        case DMX_ERR_UART_OVERFLOW:
          reset();  // Overflow needs a reset to clear buffer
          break;

        case DMX_ERR_IMPROPER_SLOT:
          // Do nothing! Let the driver re-sync on the next frame.
          break;

        default:
          break;
      }
    }
  }
}

bool rgb_dmx::get_rec_status() {
  return data_received;
}

uint16_t rgb_dmx::get_dimmer_address() {
  return start_address + used_addresses - 1;
}

uint8_t* rgb_dmx::get_universe() {
  return dmx_data;
}

void rgb_dmx::set_rec_status(bool status) {
  data_received = status;
}

void rgb_dmx::set_number_segments(uint16_t num_segs) {
  number_segments = num_segs;
  leds_per_segment = NUM_PIXEL / number_segments;
  used_addresses = number_segments * 3 + 1;  // RGB for each segment + one channel for dimmer
  last_address = UNIVERSE_SIZE - used_addresses;
}

void rgb_dmx::set_universe(uint8_t* _data) {
  memcpy(dmx_data, _data, UNIVERSE_SIZE);
}

void rgb_dmx::send_universe() {
  dmx_write(dmxPort, dmx_data, UNIVERSE_SIZE);
  dmx_send(dmxPort);
}
