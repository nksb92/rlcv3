/**
 * @file dmx.h
 * @brief Header file for the DMX lighting control receiver class.
 */

#ifndef DMX_H
#define DMX_H

// https://github.com/someweisguy/esp_dmx
#include <esp_dmx.h>

#include "common.h"

/**
 * @class rgb_dmx
 * @brief Manages DMX-512 reception and address mapping for multi-segment outputs.
 */
class rgb_dmx {
  volatile uint16_t start_address = STD_START_ADDRESS;  /**< The current start address. */
  uint16_t used_addresses = 4;
  uint16_t leds_per_segment = 0;
  uint16_t number_segments = 0;
  volatile uint16_t last_address = UNIVERSE_SIZE - used_addresses;  /**< The last possible address. */
  bool data_received = false;
  dmx_port_t dmxPort = 0;  /**< Dmx port for the esp_dmx library. */
  dmx_config_t config = DMX_CONFIG_DEFAULT;
  uint8_t dmx_data[UNIVERSE_SIZE] = {};  /**< Array to receive the dmx data in. */

 public:
  /**
   * @brief Constructor for the `rgb_dmx` class.
   */
  rgb_dmx();

  /**
   * @brief Installs the DMX driver.
   */
  void install_dmx();

  /**
   * @brief Resets the DMX receiver and clears any received data.
   * Initializes the DMX driver afterwards.
   */
  void reset();

  /**
   * @brief Disables the DMX driver.
   */
  void disable();

  /**
   * @brief Enables the DMX driver.
   */
  void enable();

  /**
   * @brief Gets the start address of the DMX data.
   * @return The start address of the DMX data.
   */
  uint16_t get_start();

  /**
   * @brief Gets the number of DMX addresses used.
   * @return The number of DMX addresses used.
   */
  uint16_t get_used_nbr();

  /**
   * @brief Adds an offset value to the start address.
   * @param[in] value The offset value to add.
   */
  void add_to_adress(int value);

  /**
   * @brief Sets the start address for the DMX addresses.
   * @param[in] start The start address to set for DMX.
   */
  void set_start_address(int start);

  /**
   * @brief Handles the DMX communication.
   * Checks for received packets, reads data, and handles errors.
   */
  void handle_dmx();

  /**
   * @brief Gets the status of data reception.
   * @return True if data has been received, false otherwise.
   */
  bool get_rec_status();

  /**
   * @brief Gets the DMX address of the dimmer channel.
   * @return The DMX address of the dimmer channel.
   */
  uint16_t get_dimmer_address();

  /**
   * @brief Gets the pointer to the current universe data.
   * @return Pointer to the universe data array.
   */
  uint8_t* get_universe();

  /**
   * @brief Sets the data reception status.
   * @param[in] status The status to set (true for received, false otherwise).
   */
  void set_rec_status(bool status);

  /**
   * @brief Sets the number of LED segments and updates address calculations.
   * @param[in] num_segs The number of segments to configure.
   * @param[in] dimmer_mode Segment dimmer configuration mode.
   * @param[in] white_mode White channel configuration mode.
   */
  void set_number_segments(uint16_t num_segs, uint8_t dimmer_mode, uint8_t white_mode);

  /**
   * @brief Sets the universe data from a provided buffer.
   * @param[in] _data Pointer to the source data buffer.
   */
  void set_universe(uint8_t* _data);

  /**
   * @brief Sends the current universe data via the DMX port.
   */
  void send_universe();
};
#endif

extern rgb_dmx dmx_val;