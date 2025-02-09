#ifndef RLC_DMX_H
#define RLC_DMX_H

// https://github.com/someweisguy/esp_dmx
#include <esp_dmx.h>
#include "common.h"

// class to handle dmx messages
class rgb_dmx
{
  volatile uint16_t start_address = STD_START_ADDRESS; // The current start address
  uint16_t used_addresses = 4;
  uint16_t leds_per_segment = 0;
  uint16_t number_segments = 0;
  volatile uint16_t last_address = UNIVERSE_SIZE - used_addresses; // The last possible address
  bool data_received = false;
  dmx_port_t dmxPort = 0; // Dmx port for the esp_dmx libarary
  dmx_config_t config = DMX_CONFIG_DEFAULT;
  uint8_t data[UNIVERSE_SIZE] = {}; // Array to receive the dmx data in

public:
  /**
   * Constructor for the `rgb_dmx` class.
   *
   * @param init_rgb: The initial RGB color to set for the LED.
   */
  rgb_dmx();

  /**
   * Installs the DMX driver.
   */
  void install_dmx();

  /**
   * Gets the start address of the DMX data.
   *
   * @return The start address of the DMX data.
   */
  uint16_t get_start();

  /**
   * Gets the number of DMX addresses used.
   *
   * @return The number of DMX addresses used.
   */
  uint16_t get_used_nbr();

  /**
   * Adds an offset value to the start address.
   *
   * @param value: The offset value to add.
   */
  void add_to_adress(int value);

  /**
   * Sets the start address for the DMX addresses.
   * @param start: The start address to set for DMX.
   */
  void set_start_address(int start);

  void hanlde_dmx();

  bool get_rec_status();
  uint16_t get_dimmer_address();
  uint8_t *get_universe();

  void set_rec_status(bool status);
  void set_number_segments(uint16_t num_segs);
  void set_universe(uint8_t *_data);
  void send_universe();
};
#endif