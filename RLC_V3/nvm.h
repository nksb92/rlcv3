#ifndef NVM_H
#define NVM_H

#include "common.h"
#include "dmx.h"
#include "pdc.h"
#include <EEPROM.h>

#define EEPROM_ADDRESSES 512

void init_eeprom();

void read_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, rgb_dmx& dmx_val, pdc_page& pdc, main& main_sw);

void write_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, rgb_dmx& dmx_val, pdc_page& pdc, main& main_sw);

#endif