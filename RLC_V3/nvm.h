#ifndef NVM_H
#define NVM_H

#include "common.h"
#include "dmx.h"
#include "segments.h"
#include <EEPROM.h>

#define EEPROM_ADDRESSES 512

void init_eeprom();

void read_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, rgb_dmx& dmx_val, main& main_sw, rlc_artnet& artnet_var, segments& segment_var);

void write_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, rgb_dmx& dmx_val, main& main_sw, rlc_artnet& artnet_var, segments& segment_var);

#endif