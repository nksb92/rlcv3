#include "nvm.h"

#define COUNT_STORED_VALUES 12
#define POLYNOMIAL 0xD8
#define WIDTH (8 * sizeof(uint8_t))
#define TOPBIT (1 << (WIDTH - 1))
#define REFLECT_DATA(X) ((uint8_t)reflect((X), 8))
#define REFLECT_REMAINDER(X) ((uint8_t)reflect((X), WIDTH))
uint8_t crcTable[256];

// crc code from website: https://barrgroup.com/embedded-systems/how-to/crc-calculation-c-code
// explaination can be found there
void crcInit(void) {
  uint8_t remainder;

  for (int dividend = 0; dividend < 256; ++dividend) {

    remainder = dividend << (WIDTH - 8);

    for (uint8_t bit = 8; bit > 0; --bit) {
      if (remainder & TOPBIT) {
        remainder = (remainder << 1) ^ POLYNOMIAL;
      } else {
        remainder = (remainder << 1);
      }
    }
    crcTable[dividend] = remainder;
  }
}

uint8_t crcFast(int message[]) {
  uint8_t data;
  uint8_t remainder = 0;
  int nBytes = sizeof(message);

  for (int byte = 0; byte < nBytes; ++byte) {
    data = message[byte] ^ (remainder >> (WIDTH - 8));
    remainder = crcTable[data] ^ (remainder << 8);
  }

  return (remainder);
}

void init_eeprom() {
  EEPROM.begin(EEPROM_ADDRESSES);
  crcInit();
}

void read_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, rgb_dmx& dmx_val, pdc_page& pdc, main& main_sw) {
  uint16_t eeprom_address = 0;
  int crc_values[COUNT_STORED_VALUES];
  uint8_t crc_index = 0;

  // get all variables from the hsv page
  uint8_t hue = STD_HUE;
  EEPROM.get(eeprom_address, hue);
  eeprom_address += sizeof(hue);
  crc_values[crc_index] = hue;
  crc_index++;

  uint8_t sat_p = STD_SAT_P;
  EEPROM.get(eeprom_address, sat_p);
  eeprom_address += sizeof(sat_p);
  crc_values[crc_index] = sat_p;
  crc_index++;

  uint8_t val_p = STD_VAL_P;
  EEPROM.get(eeprom_address, val_p);
  eeprom_address += sizeof(sat_p);
  crc_values[crc_index] = val_p;
  crc_index++;

  // get all variables from the rgb page
  uint8_t red = STD_RED;
  EEPROM.get(eeprom_address, red);
  eeprom_address += sizeof(red);
  crc_values[crc_index] = red;
  crc_index++;

  uint8_t green = STD_GREEN;
  EEPROM.get(eeprom_address, green);
  eeprom_address += sizeof(green);
  crc_values[crc_index] = green;
  crc_index++;

  uint8_t blue = STD_BLUE;
  EEPROM.get(eeprom_address, blue);
  eeprom_address += sizeof(blue);
  crc_values[crc_index] = blue;
  crc_index++;

  // get all variables from the dmx page
  uint8_t current_dmx = STD_CURRENT;
  EEPROM.get(eeprom_address, current_dmx);
  eeprom_address += sizeof(current_dmx);
  crc_values[crc_index] = current_dmx;
  crc_index++;

  uint16_t start_address = STD_START_ADDRESS;
  EEPROM.get(eeprom_address, start_address);
  eeprom_address += sizeof(start_address);
  crc_values[crc_index] = start_address;
  crc_index++;

  // get all variables from the pre defined color page
  uint8_t current_pdc = STD_CURRENT;
  EEPROM.get(eeprom_address, current_pdc);
  eeprom_address += sizeof(current_pdc);
  crc_values[crc_index] = current_pdc;
  crc_index++;

  uint8_t brightness_p = STD_BRIGHTNESS_PDC;
  EEPROM.get(eeprom_address, brightness_p);
  eeprom_address += sizeof(brightness_p);
  crc_values[crc_index] = brightness_p;
  crc_index++;

  // get the current main state
  uint8_t current_main = STD_CURRENT;
  EEPROM.get(eeprom_address, current_main);
  eeprom_address += sizeof(current_main);
  crc_values[crc_index] = current_main;
  crc_index++;

  uint8_t crc = 0;
  EEPROM.get(eeprom_address, crc);

  // checking if the saved crc matches the calculated
  // and sets the corresponding variables on success
  if (crc == crcFast(crc_values)) {
    hsv_val.set_hue_byte(hue);
    hsv_val.set_sat_p(sat_p);
    hsv_val.set_val_p(val_p);

    rgb_val.set_red(red);
    rgb_val.set_green(green);
    rgb_val.set_blue(blue);

    dmx_val.set_current(current_dmx);
    dmx_val.set_start_address(start_address);

    pdc.set_current(current_pdc);
    pdc.set_bright(brightness_p);

    main_sw.set_current(current_main);
  }
}

void write_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, rgb_dmx& dmx_val, pdc_page& pdc, main& main_sw) {
  uint16_t eeprom_address = 0;
  int crc_values[COUNT_STORED_VALUES];
  uint8_t crc_index = 0;

  // set all variables from the hsv page
  uint8_t hue = hsv_val.get_hue();
  EEPROM.put(eeprom_address, hue);
  eeprom_address += sizeof(hue);
  crc_values[crc_index] = hue;
  crc_index++;

  uint8_t sat_p = hsv_val.get_sat_p();
  EEPROM.put(eeprom_address, sat_p);
  eeprom_address += sizeof(sat_p);
  crc_values[crc_index] = sat_p;
  crc_index++;

  uint8_t val_p = hsv_val.get_val_p();
  EEPROM.put(eeprom_address, val_p);
  eeprom_address += sizeof(val_p);
  crc_values[crc_index] = val_p;
  crc_index++;

  // set all variables from the rgb page
  uint8_t red = rgb_val.get_red();
  EEPROM.put(eeprom_address, red);
  eeprom_address += sizeof(red);
  crc_values[crc_index] = red;
  crc_index++;

  uint8_t green = rgb_val.get_green();
  EEPROM.put(eeprom_address, green);
  eeprom_address += sizeof(green);
  crc_values[crc_index] = green;
  crc_index++;

  uint8_t blue = rgb_val.get_blue();
  EEPROM.put(eeprom_address, blue);
  eeprom_address += sizeof(blue);
  crc_values[crc_index] = blue;
  crc_index++;

  // set all variables from the dmx page
  uint8_t current_dmx = dmx_val.get_current();
  EEPROM.put(eeprom_address, current_dmx);
  eeprom_address += sizeof(current_dmx);
  crc_values[crc_index] = current_dmx;
  crc_index++;

  uint16_t start_address = dmx_val.get_start();
  EEPROM.put(eeprom_address, start_address);
  eeprom_address += sizeof(start_address);
  crc_values[crc_index] = start_address;
  crc_index++;

  // set all variables from the pre defined color page
  uint8_t current_pdc = pdc.get_current();
  EEPROM.put(eeprom_address, current_pdc);
  eeprom_address += sizeof(current_pdc);
  crc_values[crc_index] = current_pdc;
  crc_index++;

  uint8_t brightness_p = pdc.get_bright();
  EEPROM.put(eeprom_address, brightness_p);
  eeprom_address += sizeof(brightness_p);
  crc_values[crc_index] = brightness_p;
  crc_index++;

  // set the current main state
  uint8_t current_main = main_sw.get_current();
  EEPROM.put(eeprom_address, current_main);
  eeprom_address += sizeof(current_main);
  crc_values[crc_index] = current_main;

  // calculate the crc and saving it in the eeprom
  EEPROM.put(eeprom_address, crcFast(crc_values));

  EEPROM.commit();
}