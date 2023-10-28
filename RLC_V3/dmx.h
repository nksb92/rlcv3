#ifndef DMX_H
#define DMX_H

// https://github.com/someweisguy/esp_dmx
#include <esp_dmx.h>
#include "common.h"

enum {
  WIRE,
  SENDER,
  RECEIVER,
  DMX_LAST
};

// class to handle dmx messages
class rgb_dmx {

  volatile uint8_t current = STD_CURRENT;               // The current menu index
  volatile uint16_t start_address = STD_START_ADDRESS;  // The current start address
  uint16_t used_addresses = 4;
  uint16_t leds_per_segment = 0;
  uint16_t number_segments = 0;
  volatile uint16_t last_address = 512 - used_addresses + 1;  // The last possible address

  CRGB dmx_message;  // Variable to store the color
  uint8_t dim = 0;   // Dimming factor given with the fouth address

  dmx_port_t dmxPort = 0;  // Dmx port for the esp_dmx libarary
  dmx_config_t config = DMX_CONFIG_DEFAULT;
  uint8_t data[DMX_PACKET_SIZE];  // Array to receive the dmx data in
  char* modes[DMX_LAST];          // Array to store the names of the pages

public:
  /**
  * Constructor for the `rgb_dmx` class.
  *
  * @param init_rgb: The initial RGB color to set for the LED.
  */
  rgb_dmx(CRGB init_rgb);

  /**
  * Gets the current mode index.
  *
  * @return The current mode index.
  */
  uint8_t get_current();

  /**
  * Sets the current mode to the given mode. If the given mode is greater than or equal to the total number of modes,
  * sets the mode to the last available mode.
  * @param _current: The mode to set the current mode to.
  */
  void set_current(uint8_t _current);

  /**
  * Advances to the next mode.
  */
  void next();

  /**
  * Gets the name of the current mode.
  *
  * @return The name of the current mode.
  */
  char* get_current_txt();

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

  /**
  * Sets the RGB color and dimming factor from the DMX data.
  */
  void set_rgb();

  /**
  * Receives DMX data and sets the RGB color and dimming factor if in `WIRE` or `MAIN` mode.
  *        Otherwise, only sets the RGB color and dimming factor from the DMX data.
  */
  void hanlde_dmx();

  /**
  * Gets the current RGB color of the LED.
  *
  * @return The current RGB color of the LED.
  */
  CRGB get_dmx_message();

  /**
  * Sets a value in the DMX data at a given index.
  *
  * @param information: The value to set.
  * @param index: The index at which to set the value.
  */
  void set_data(uint8_t information, uint16_t index);

  /**
  * Gets the value at a given index in the DMX data.
  *
  * @param index: The index to retrieve the value from.
  *
  * @return The value at the given index.
  */
  uint8_t get_data(uint16_t index);

  void set_number_segments(uint16_t num_segs);
};
#endif