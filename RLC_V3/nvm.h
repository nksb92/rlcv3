/**
 * @file nvm.h
 * @brief Header file for Non-Volatile Memory (EEPROM) read/write operations.
 */

#ifndef NVM_H
#define NVM_H

#include <EEPROM.h>

#include "common.h"
#include "dmx.h"
#include "segments.h"
#include "c_cct.h"
#include "c_grad.h"

#define EEPROM_ADDRESSES 512 /**< Allocated size for simulated EEPROM storage. */

/**
 * @brief Initializes the simulated EEPROM storage.
 */
void init_eeprom();

/**
 * @brief Clears simulated EEPROM storage, writes default values, and triggers reboot.
 */
void factory_reset();

/**
 * @brief Reads system settings from simulated EEPROM.
 * @param[out] hsv_val HSV configuration object to write to.
 * @param[out] rgb_val RGB configuration object to write to.
 * @param[out] cct_val CCT configuration object to write to.
 * @param[out] dmx_val DMX configuration object to write to.
 * @param[out] main_sw Main menu state object to write to.
 * @param[out] artnet_var ArtNet state object to write to.
 * @param[out] segment_var Segment structure object to write to.
 * @param[out] grad_val Gradient config object to write to.
 */
void read_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, c_cct& cct_val, rgb_dmx& dmx_val, menu_structure& main_sw, rlc_artnet& artnet_var, segments& segment_var, C_GRAD& grad_val);

/**
 * @brief Writes current system settings to simulated EEPROM.
 * @param[in] hsv_val Current HSV config.
 * @param[in] rgb_val Current RGB config.
 * @param[in] cct_val Current CCT config.
 * @param[in] dmx_val Current DMX config.
 * @param[in] main_sw Current main menu state.
 * @param[in] artnet_var Current ArtNet state.
 * @param[in] segment_var Current segment configuration.
 * @param[in] grad_val Current gradient configuration.
 */
void write_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, c_cct& cct_val, rgb_dmx& dmx_val, menu_structure& main_sw, rlc_artnet& artnet_var, segments& segment_var, C_GRAD& grad_val);

#endif