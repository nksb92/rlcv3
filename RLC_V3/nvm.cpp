/**
 * @file nvm.cpp
 * @brief Implementation of Non-Volatile Memory (EEPROM) read/write operations.
 */

#include "nvm.h"

#define COUNT_STORED_VALUES 26
#define POLYNOMIAL 0xD8
#define WIDTH (8 * sizeof(uint8_t))
#define TOPBIT (1 << (WIDTH - 1))
#define REFLECT_DATA(X) ((uint8_t)reflect((X), 8))
#define REFLECT_REMAINDER(X) ((uint8_t)reflect((X), WIDTH))
uint8_t crcTable[256];

// crc code from website: https://barrgroup.com/embedded-systems/how-to/crc-calculation-c-code
// explaination can be found there
void crcInit() {
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

void factory_reset() {
  EEPROM.begin(EEPROM_ADDRESSES);
  for (int i = 0; i < EEPROM_ADDRESSES; i++) {
    EEPROM.write(i, 255);
  }
  EEPROM.commit();
  ESP.restart();
}

void read_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, c_cct& cct_val, rgb_dmx& dmx_val, menu_structure& main_sw, rlc_artnet& artnet_var, segments& segment_var, C_GRAD& grad_val) {
  uint16_t eeprom_address = 0;
  int crc_values[COUNT_STORED_VALUES] = {};
  uint8_t crc_index = 0;

  // get all variables from the hsv page
  uint8_t hue = STD_HUE;
  EEPROM.get(eeprom_address, hue);
  eeprom_address += sizeof(hue);
  crc_values[crc_index] = hue;
  crc_index++;

  uint8_t sat = STD_SAT;
  EEPROM.get(eeprom_address, sat);
  eeprom_address += sizeof(sat);
  crc_values[crc_index] = sat;
  crc_index++;

  uint8_t val = STD_VAL;
  EEPROM.get(eeprom_address, val);
  eeprom_address += sizeof(sat);
  crc_values[crc_index] = val;
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

  // get all variables from the cct page
  uint16_t kelvin = (CCT_MIN_KELVIN + (((CCT_MAX_KELVIN - CCT_MIN_KELVIN) / 2) / CCT_STEP_SIZE) * CCT_STEP_SIZE);
  EEPROM.get(eeprom_address, kelvin);
  eeprom_address += sizeof(kelvin);
  crc_values[crc_index] = kelvin;
  crc_index++;

  uint8_t brightness = 100;
  EEPROM.get(eeprom_address, brightness);
  eeprom_address += sizeof(brightness);
  crc_values[crc_index] = brightness;
  crc_index++;

  // get all variables from the segment page
  uint8_t segment_pos = STD_SEGMENTS;
  EEPROM.get(eeprom_address, segment_pos);
  eeprom_address += sizeof(segment_pos);
  crc_values[crc_index] = segment_pos;
  crc_index++;

  uint8_t dimmer_mode = RGB_DIMMER;
  EEPROM.get(eeprom_address, dimmer_mode);
  eeprom_address += sizeof(dimmer_mode);
  crc_values[crc_index] = dimmer_mode;
  crc_index++;

  uint8_t white_mode = WHITE_DISABLE;
  EEPROM.get(eeprom_address, white_mode);
  eeprom_address += sizeof(white_mode);
  crc_values[crc_index] = white_mode;
  crc_index++;

  uint8_t value_mode = VALUE_PERCENTAGE;
  EEPROM.get(eeprom_address, value_mode);
  eeprom_address += sizeof(value_mode);
  crc_values[crc_index] = value_mode;
  crc_index++;

  // get all variables from the dmx page
  uint16_t start_address = STD_START_ADDRESS;
  EEPROM.get(eeprom_address, start_address);
  eeprom_address += sizeof(start_address);
  crc_values[crc_index] = start_address;
  crc_index++;

  // get the current main state
  uint8_t current_main = STD_CURRENT;
  EEPROM.get(eeprom_address, current_main);
  eeprom_address += sizeof(current_main);
  crc_values[crc_index] = current_main;
  crc_index++;

  uint8_t deepness_main = STD_DEEPNESS;
  EEPROM.get(eeprom_address, deepness_main);
  eeprom_address += sizeof(deepness_main);
  crc_values[crc_index] = deepness_main;
  crc_index++;

  // get all variables from the artnet page
  uint16_t artnet_universe = STD_UNIVERSE;
  EEPROM.get(eeprom_address, artnet_universe);
  eeprom_address += sizeof(artnet_universe);
  crc_values[crc_index] = artnet_universe;
  crc_index++;

  uint16_t artnet_start = STD_START_ADDRESS;
  EEPROM.get(eeprom_address, artnet_start);
  eeprom_address += sizeof(artnet_start);
  crc_values[crc_index] = artnet_start;
  crc_index++;

  uint8_t artnet_fsm = MENU;
  EEPROM.get(eeprom_address, artnet_fsm);
  eeprom_address += sizeof(artnet_fsm);
  crc_values[crc_index] = artnet_fsm;
  crc_index++;

  // get all variables from grad page
  uint8_t g_sh = 0, g_ss = 100, g_sv = 100, g_eh = 160, g_es = 100, g_ev = 100, g_dim = 100;
  EEPROM.get(eeprom_address, g_sh); eeprom_address += sizeof(g_sh); crc_values[crc_index++] = g_sh;
  EEPROM.get(eeprom_address, g_ss); eeprom_address += sizeof(g_ss); crc_values[crc_index++] = g_ss;
  EEPROM.get(eeprom_address, g_sv); eeprom_address += sizeof(g_sv); crc_values[crc_index++] = g_sv;
  EEPROM.get(eeprom_address, g_eh); eeprom_address += sizeof(g_eh); crc_values[crc_index++] = g_eh;
  EEPROM.get(eeprom_address, g_es); eeprom_address += sizeof(g_es); crc_values[crc_index++] = g_es;
  EEPROM.get(eeprom_address, g_ev); eeprom_address += sizeof(g_ev); crc_values[crc_index++] = g_ev;
  EEPROM.get(eeprom_address, g_dim); eeprom_address += sizeof(g_dim); crc_values[crc_index] = g_dim;

  uint8_t crc = 0;
  EEPROM.get(eeprom_address, crc);

  // checking if the saved crc matches the calculated
  // and sets the corresponding variables on success
  if (crc == crcFast(crc_values)) {
    segment_var.set_value_mode(value_mode);

    hsv_val.set_hue_byte(hue);
    hsv_val.set_sat(sat);
    hsv_val.set_val(val);

    rgb_val.set_red(red);
    rgb_val.set_green(green);
    rgb_val.set_blue(blue);

    cct_val.set_kelvin(kelvin);
    cct_val.set_brightness(brightness);

    segment_var.set_current_segment(segment_pos);
    segment_var.set_dimmer_mode(dimmer_mode);
    segment_var.set_white_mode(white_mode);

    dmx_val.set_number_segments(segment_var.get_num_seg(), segment_var.get_dimmer_mode(), segment_var.get_white_mode());
    artnet_var.set_number_segments(segment_var.get_num_seg(), segment_var.get_dimmer_mode(), segment_var.get_white_mode());

    dmx_val.set_start_address(start_address);

    main_sw.set_current(current_main);
    main_sw.set_deepness(deepness_main);

    artnet_var.set_current_universe_nmbr(artnet_universe);
    artnet_var.set_current_channel(artnet_start);
    artnet_var.set_current_fsm(artnet_fsm);

    grad_val.set_start_hue(g_sh);
    grad_val.set_start_sat(g_ss);
    grad_val.set_start_val(g_sv);
    grad_val.set_end_hue(g_eh);
    grad_val.set_end_val(g_ev);
    grad_val.set_dimmer(g_dim);
  }
}

void write_eeprom(C_HSV& hsv_val, C_RGB& rgb_val, c_cct& cct_val, rgb_dmx& dmx_val, menu_structure& main_sw, rlc_artnet& artnet_var, segments& segment_var, C_GRAD& grad_val) {
  uint16_t eeprom_address = 0;
  int crc_values[COUNT_STORED_VALUES] = {};
  uint8_t crc_index = 0;

  // set all variables from the hsv page
  uint8_t hue = hsv_val.get_hue();
  EEPROM.put(eeprom_address, hue);
  eeprom_address += sizeof(hue);
  crc_values[crc_index] = hue;
  crc_index++;

  uint8_t sat = hsv_val.get_sat();
  EEPROM.put(eeprom_address, sat);
  eeprom_address += sizeof(sat);
  crc_values[crc_index] = sat;
  crc_index++;

  uint8_t val = hsv_val.get_val();
  EEPROM.put(eeprom_address, val);
  eeprom_address += sizeof(val);
  crc_values[crc_index] = val;
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

  // set all variables from the cct page
  uint16_t kelvin = cct_val.get_kelvin();
  EEPROM.put(eeprom_address, kelvin);
  eeprom_address += sizeof(kelvin);
  crc_values[crc_index] = kelvin;
  crc_index++;

  uint8_t brightness = cct_val.get_brightness();
  EEPROM.put(eeprom_address, brightness);
  eeprom_address += sizeof(brightness);
  crc_values[crc_index] = brightness;
  crc_index++;

  // set all variables from the segment page
  uint8_t segment_pos = segment_var.get_current_seg();
  EEPROM.put(eeprom_address, segment_pos);
  eeprom_address += sizeof(segment_pos);
  crc_values[crc_index] = segment_pos;
  crc_index++;

  uint8_t dimmer_mode = segment_var.get_dimmer_mode();
  EEPROM.put(eeprom_address, dimmer_mode);
  eeprom_address += sizeof(dimmer_mode);
  crc_values[crc_index] = dimmer_mode;
  crc_index++;

  uint8_t white_mode = segment_var.get_white_mode();
  EEPROM.put(eeprom_address, white_mode);
  eeprom_address += sizeof(white_mode);
  crc_values[crc_index] = white_mode;
  crc_index++;

  uint8_t value_mode = segment_var.get_value_mode();
  EEPROM.put(eeprom_address, value_mode);
  eeprom_address += sizeof(value_mode);
  crc_values[crc_index] = value_mode;
  crc_index++;

  // set all variables from the dmx page
  uint16_t start_address = dmx_val.get_start();
  EEPROM.put(eeprom_address, start_address);
  eeprom_address += sizeof(start_address);
  crc_values[crc_index] = start_address;
  crc_index++;

  // set the all variables from main state
  uint8_t current_main = main_sw.get_current();
  EEPROM.put(eeprom_address, current_main);
  eeprom_address += sizeof(current_main);
  crc_values[crc_index] = current_main;
  crc_index++;

  uint8_t deepness_main = main_sw.get_deepness();
  EEPROM.put(eeprom_address, deepness_main);
  eeprom_address += sizeof(deepness_main);
  crc_values[crc_index] = deepness_main;
  crc_index++;

  // set all variables from the artnet page
  uint16_t artnet_universe = artnet_var.get_start_universe();
  EEPROM.put(eeprom_address, artnet_universe);
  eeprom_address += sizeof(artnet_universe);
  crc_values[crc_index] = artnet_universe;
  crc_index++;

  uint16_t artnet_start = artnet_var.get_start_channel();
  EEPROM.put(eeprom_address, artnet_start);
  eeprom_address += sizeof(artnet_start);
  crc_values[crc_index] = artnet_start;
  crc_index++;

  uint8_t artnet_fsm = artnet_var.get_current_fsm();
  EEPROM.put(eeprom_address, artnet_fsm);
  eeprom_address += sizeof(artnet_fsm);
  crc_values[crc_index] = artnet_fsm;
  crc_index++;

  // set grad variables
  uint8_t g_sh = grad_val.get_start_hue();
  EEPROM.put(eeprom_address, g_sh); eeprom_address += sizeof(g_sh); crc_values[crc_index++] = g_sh;
  uint8_t g_ss = grad_val.get_start_sat();
  EEPROM.put(eeprom_address, g_ss); eeprom_address += sizeof(g_ss); crc_values[crc_index++] = g_ss;
  uint8_t g_sv = grad_val.get_start_val();
  EEPROM.put(eeprom_address, g_sv); eeprom_address += sizeof(g_sv); crc_values[crc_index++] = g_sv;
  uint8_t g_eh = grad_val.get_end_hue();
  EEPROM.put(eeprom_address, g_eh); eeprom_address += sizeof(g_eh); crc_values[crc_index++] = g_eh;
  uint8_t g_es = grad_val.get_end_sat();
  EEPROM.put(eeprom_address, g_es); eeprom_address += sizeof(g_es); crc_values[crc_index++] = g_es;
  uint8_t g_ev = grad_val.get_end_val();
  EEPROM.put(eeprom_address, g_ev); eeprom_address += sizeof(g_ev); crc_values[crc_index++] = g_ev;
  uint8_t g_dim = grad_val.get_dimmer();
  EEPROM.put(eeprom_address, g_dim); eeprom_address += sizeof(g_dim); crc_values[crc_index] = g_dim;

  // calculate the crc and saving it in the eeprom
  EEPROM.put(eeprom_address, crcFast(crc_values));

  EEPROM.commit();
}