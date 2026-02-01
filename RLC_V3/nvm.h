#ifndef NVM_H
#define NVM_H

#include <EEPROM.h>

#include "common.h"
#include "dmx.h"
#include "segments.h"

#define EEPROM_ADDRESSES 512

void init_eeprom();

void read_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, rgb_dmx& dmx_val, menu_structure& main_sw, rlc_artnet& artnet_var, segments& segment_var);

void write_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, rgb_dmx& dmx_val, menu_structure& main_sw, rlc_artnet& artnet_var, segments& segment_var);

#endif