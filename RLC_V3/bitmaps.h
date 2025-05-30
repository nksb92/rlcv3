#ifndef BITMAPS_H
#define BITMAPS_H

#include <Arduino.h>

// 'ARTNET_REC_MENU', 19x21px
const unsigned char BITMAP_ARTNET_REC_MENU[] PROGMEM = {
  0x18, 0x7c, 0xfe, 0x18, 0x6e, 0x10, 0x3c, 0x62, 0x10, 0x34, 0x66, 0x10, 0x26, 0x7e, 0x10, 0x66,
  0x6c, 0x10, 0x7e, 0x66, 0x10, 0xc3, 0x63, 0x10, 0xc1, 0x63, 0x10, 0x00, 0x00, 0x00, 0xc2, 0x7f,
  0xfe, 0xe6, 0x60, 0x30, 0xe6, 0x60, 0x30, 0xf6, 0x60, 0x30, 0xd6, 0x7e, 0x30, 0xde, 0x60, 0x30,
  0xce, 0x60, 0x30, 0xce, 0x60, 0x30, 0xc6, 0x7e, 0x30
};
// 'DMX_PAGE', 35x12px
const unsigned char BITMAP_DMX_MENU [] PROGMEM = {
	0xfe, 0x1c, 0x06, 0xe0, 0xe0, 0xff, 0x1c, 0x0e, 0x70, 0xc0, 0xc3, 0x9e, 0x0e, 0x39, 0xc0, 0xc1, 
	0x9e, 0x1e, 0x3b, 0x80, 0xc1, 0xdf, 0x1e, 0x1f, 0x00, 0xc1, 0xdb, 0x3e, 0x0e, 0x00, 0xc1, 0xdb, 
	0xb6, 0x0f, 0x00, 0xc1, 0xd9, 0xf6, 0x1f, 0x00, 0xc1, 0xd9, 0xe6, 0x3b, 0x80, 0xc3, 0x98, 0xe6, 
	0x31, 0xc0, 0xff, 0x18, 0x06, 0x70, 0xc0, 0xfe, 0x18, 0x06, 0xe0, 0xe0
};
// 'HSV_PAGE', 33x12px
const unsigned char BITMAP_HSV_MENU [] PROGMEM = {
	0xe0, 0xe3, 0xf7, 0x03, 0x80, 0xe0, 0xe7, 0xf7, 0x03, 0x80, 0xe0, 0xee, 0x03, 0x03, 0x00, 0xe0, 
	0xee, 0x03, 0x87, 0x00, 0xe0, 0xee, 0x03, 0x86, 0x00, 0xff, 0xe7, 0xe1, 0x8e, 0x00, 0xff, 0xe3, 
	0xf1, 0xce, 0x00, 0xe0, 0xe0, 0x79, 0xcc, 0x00, 0xe0, 0xe0, 0x38, 0xfc, 0x00, 0xe0, 0xe0, 0x38, 
	0xfc, 0x00, 0xe0, 0xef, 0xf0, 0x78, 0x00, 0xe0, 0xef, 0xe0, 0x78, 0x00
};
// 'RGB_PAGE', 32x12px
const unsigned char BITMAP_RGB_MENU [] PROGMEM = {
	0xfe, 0x03, 0xf1, 0xfc, 0xff, 0x0f, 0xf1, 0xff, 0xe1, 0x8e, 0x01, 0x87, 0xe1, 0x9c, 0x01, 0x83, 
	0xe1, 0x98, 0x01, 0x87, 0xe7, 0x98, 0x01, 0xfe, 0xff, 0x18, 0xf9, 0xfe, 0xfe, 0x18, 0xf9, 0x83, 
	0xe7, 0x1c, 0x39, 0x83, 0xe3, 0x1e, 0x39, 0x83, 0xe3, 0x8f, 0xf9, 0xff, 0xe1, 0xc3, 0xf9, 0xfe
};
// 'SETTINGS_MENU', 35x19px
const unsigned char BITMAP_SETTINGS_MENU[] PROGMEM = {
  0x1c, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0xe3, 0xff, 0xff, 0xf8, 0x36, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xd8, 0x00, 0xff, 0xff, 0x8f, 0xf8, 0x00, 0x00, 0xd8, 0x00,
  0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0xe3, 0xff, 0xff, 0xf8, 0x36, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00
};
// 'left_end_menu', 12x21px
const unsigned char BITMAP_LEFT_END_MENU[] PROGMEM = {
  0xe0, 0x00, 0xf0, 0x00, 0xf8, 0x00, 0xfc, 0x00, 0x7e, 0x00, 0x3f, 0x00, 0x1f, 0x80, 0x0f, 0xc0,
  0x07, 0xe0, 0x03, 0xf0, 0x01, 0xf0, 0x03, 0xf0, 0x07, 0xe0, 0x0f, 0xc0, 0x1f, 0x80, 0x3f, 0x00,
  0x7e, 0x00, 0xfc, 0x00, 0xf8, 0x00, 0xf0, 0x00, 0xe0, 0x00
};
// 'right_end_menu', 12x21px
const unsigned char BITMAP_RIGHT_END_MENU[] PROGMEM = {
  0x00, 0x70, 0x00, 0xf0, 0x01, 0xf0, 0x03, 0xf0, 0x07, 0xe0, 0x0f, 0xc0, 0x1f, 0x80, 0x3f, 0x00,
  0x7e, 0x00, 0xfc, 0x00, 0xf8, 0x00, 0xfc, 0x00, 0x7e, 0x00, 0x3f, 0x00, 0x1f, 0x80, 0x0f, 0xc0,
  0x07, 0xe0, 0x03, 0xf0, 0x01, 0xf0, 0x00, 0xf0, 0x00, 0x70
};

enum {
  LEFT_END_MENU,
  ARTNET_REC_MENU,
  DMX_MENU,
  HSV_MENU,
  RGB_MENU,
  SETTINGS_MENU,
  RIGHT_END_MENU
};

enum {
  WIDTH,
  HEIGHT
};

enum {
  x,
  y
};

#define BITMAP_MAIN_MENU_LEN 7

int W_H_MATRIX_MAIN_MENU[BITMAP_MAIN_MENU_LEN][2] = {
  { 12, 21 }, // Left end menu
  { 23, 19 }, // artnet_rec menu
  { 35, 12 }, // DMX menu
  { 33, 12 }, // HSV menu
  { 32, 12 }, // RGB menu
  { 29, 21 }, // Settings menu
  { 12, 21 }  // right end menu
};

int X_Y_MATRIX_MAIN_MENU[BITMAP_MAIN_MENU_LEN][2] = {
  { 58, 2 },
  { 53, 3 },
  { 47, 6 },
  { 48, 6 },
  { 48, 6 },
  { 49, 2 },
  { 58, 3 }
};

const unsigned char *BITMAP_MAIN_MENU_ARRAY[BITMAP_MAIN_MENU_LEN] = {
  BITMAP_LEFT_END_MENU,
  BITMAP_ARTNET_REC_MENU,
  BITMAP_DMX_MENU,
  BITMAP_HSV_MENU,
  BITMAP_RGB_MENU,
  BITMAP_SETTINGS_MENU,
  BITMAP_RIGHT_END_MENU
};

// 'SELECTION', 40x23px
const unsigned char BITMAP_MAIN_MENU_SEL[] PROGMEM = {
	0xc0, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 
	0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 
	0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 
	0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 
	0x00, 0x00, 0x03
};

// 'ARTNET_REC_PAGE', 63x12px
const unsigned char BITMAP_ARTNET_REC_PAGE[] PROGMEM = {
  0x0e, 0x0f, 0xc7, 0xfe, 0xe1, 0x8f, 0xf7, 0xfe, 0x0e, 0x0f, 0xe7, 0xfe, 0xe1, 0x8f, 0xf7, 0xfe,
  0x0e, 0x0c, 0x30, 0x60, 0xf1, 0x8c, 0x00, 0x60, 0x1b, 0x0c, 0x30, 0x60, 0xf1, 0x8c, 0x00, 0x60,
  0x1b, 0x0c, 0x30, 0x60, 0xd9, 0x8c, 0x00, 0x60, 0x31, 0x8e, 0x70, 0x60, 0xd9, 0x8f, 0xf0, 0x60,
  0x31, 0x8f, 0xe0, 0x60, 0xcd, 0x8f, 0xe0, 0x60, 0x31, 0x8c, 0x60, 0x60, 0xcd, 0x8c, 0x00, 0x60,
  0x7f, 0xcc, 0x30, 0x60, 0xc7, 0x8c, 0x00, 0x60, 0x60, 0xcc, 0x38, 0x60, 0xc7, 0x8c, 0x00, 0x60,
  0x60, 0xcc, 0x18, 0x60, 0xc3, 0x8c, 0x00, 0x60, 0xc0, 0x6c, 0x1c, 0x60, 0xc3, 0x8f, 0xf0, 0x60
};
// 'DMX_CHANNEL_SEL_BAR', 71x9px
const unsigned char BITMAP_DMX_CHANNEL_SEL_BAR[] PROGMEM = {
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x7f,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xf8
};
// 'DMX_PAGE', 35x12px
const unsigned char BITMAP_DMX_PAGE[] PROGMEM = {
  0xfe, 0x06, 0x07, 0x30, 0x60, 0xff, 0x87, 0x07, 0x18, 0x60, 0xc1, 0x87, 0x0f, 0x18, 0xc0, 0xc0,
  0xc7, 0x8f, 0x0d, 0x80, 0xc0, 0xc7, 0x9b, 0x07, 0x80, 0xc0, 0xc6, 0x9b, 0x07, 0x00, 0xc0, 0xe6,
  0xd3, 0x07, 0x00, 0xc0, 0xc6, 0xf3, 0x0f, 0x80, 0xc0, 0xc6, 0x73, 0x0d, 0x80, 0xc1, 0xc6, 0x63,
  0x18, 0xc0, 0xef, 0x86, 0x03, 0x30, 0x60, 0xfe, 0x06, 0x03, 0x30, 0x60
};
// 'HSV_PAGE', 117x12px
const unsigned char BITMAP_HSV_PAGE[] PROGMEM = {
  0xc0, 0xcc, 0x08, 0xff, 0x00, 0x01, 0xf0, 0x18, 0xff, 0xc0, 0x01, 0x80, 0xc7, 0x06, 0x00, 0xc0,
  0xcc, 0x0c, 0xff, 0x00, 0x03, 0xf8, 0x38, 0xff, 0xc0, 0x01, 0x80, 0xc7, 0x06, 0x00, 0xc0, 0xcc,
  0x0c, 0xc0, 0x00, 0x06, 0x00, 0x3c, 0x0c, 0x00, 0x00, 0xc1, 0x8f, 0x06, 0x00, 0xc0, 0xcc, 0x0c,
  0xc0, 0x00, 0x06, 0x00, 0x3c, 0x0c, 0x00, 0x00, 0xc1, 0x8d, 0x86, 0x00, 0xc0, 0xcc, 0x0c, 0xc0,
  0x00, 0x07, 0x00, 0x66, 0x0c, 0x00, 0x00, 0x63, 0x0d, 0x86, 0x00, 0xff, 0xcc, 0x0c, 0xff, 0x00,
  0x03, 0xe0, 0x66, 0x0c, 0x00, 0x00, 0x63, 0x18, 0x86, 0x00, 0xff, 0xcc, 0x0c, 0xfe, 0x00, 0x01,
  0xf8, 0xc6, 0x0c, 0x00, 0x00, 0x63, 0x18, 0xc6, 0x00, 0xc0, 0xcc, 0x0c, 0xc0, 0x00, 0x00, 0x18,
  0xc3, 0x0c, 0x00, 0x00, 0x36, 0x18, 0xc6, 0x00, 0xc0, 0xcc, 0x18, 0xc0, 0x00, 0x00, 0x18, 0xff,
  0x0c, 0x00, 0x00, 0x36, 0x3f, 0xe6, 0x00, 0xc0, 0xc6, 0x18, 0xc0, 0x00, 0x00, 0x19, 0x81, 0x0c,
  0x00, 0x00, 0x3c, 0x30, 0x66, 0x00, 0xc0, 0xc7, 0x38, 0xc0, 0x00, 0x06, 0x19, 0x81, 0x8c, 0x00,
  0x00, 0x1c, 0x60, 0x66, 0x00, 0xc0, 0xc3, 0xf0, 0xff, 0x00, 0x07, 0xf1, 0x81, 0x8c, 0x00, 0x00,
  0x1c, 0x60, 0x37, 0xf8
};
// 'RGB_PAGE', 121x12px
const unsigned char BITMAP_RGB_PAGE[] PROGMEM = {
  0xfc, 0x0f, 0xe3, 0xf0, 0x00, 0x03, 0xe1, 0xf8, 0x30, 0x60, 0x1f, 0xc3, 0x03, 0x02, 0x3f, 0x80,
  0xfe, 0x0f, 0xe3, 0xfc, 0x00, 0x0f, 0xf1, 0xfc, 0x38, 0x60, 0x1f, 0xe3, 0x03, 0x03, 0x3f, 0x80,
  0xc3, 0x08, 0x03, 0x0e, 0x00, 0x18, 0x11, 0x8c, 0x3c, 0x60, 0x18, 0x63, 0x03, 0x03, 0x30, 0x00,
  0xc3, 0x08, 0x03, 0x06, 0x00, 0x30, 0x01, 0x86, 0x3c, 0x60, 0x18, 0x23, 0x03, 0x03, 0x30, 0x00,
  0xc3, 0x08, 0x03, 0x07, 0x00, 0x30, 0x01, 0x86, 0x36, 0x60, 0x18, 0x63, 0x03, 0x03, 0x30, 0x00,
  0xe7, 0x0f, 0xe3, 0x03, 0x00, 0x30, 0x01, 0x9c, 0x36, 0x60, 0x1f, 0xc3, 0x03, 0x03, 0x3f, 0x80,
  0xfe, 0x0f, 0xe3, 0x03, 0x00, 0x30, 0xf1, 0xf8, 0x33, 0x60, 0x1f, 0xe3, 0x03, 0x03, 0x3f, 0x80,
  0xc6, 0x08, 0x03, 0x03, 0x00, 0x30, 0x31, 0x9c, 0x33, 0x60, 0x18, 0x33, 0x03, 0x03, 0x30, 0x00,
  0xc3, 0x08, 0x03, 0x06, 0x00, 0x30, 0x31, 0x8c, 0x31, 0xe0, 0x18, 0x33, 0x03, 0x02, 0x30, 0x00,
  0xc1, 0x88, 0x03, 0x0e, 0x00, 0x38, 0x31, 0x86, 0x31, 0xe0, 0x18, 0x33, 0x01, 0x86, 0x30, 0x00,
  0xc1, 0x8c, 0x03, 0x3c, 0x00, 0x1c, 0x71, 0x86, 0x30, 0xe0, 0x1c, 0x73, 0x81, 0xce, 0x30, 0x00,
  0xc0, 0xcf, 0xe3, 0xf0, 0x00, 0x0f, 0xe1, 0x83, 0x30, 0xe0, 0x1f, 0xe3, 0xfc, 0xfc, 0x3f, 0x80
};
// 'SEGMENTS_PAGE ', 87x28px
const unsigned char BITMAP_SEGMENTS_PAGE[] PROGMEM = {
  0x3e, 0x1f, 0xc0, 0xf8, 0x70, 0x71, 0xfc, 0x70, 0xdf, 0xf8, 0xfc, 0x7f, 0x1f, 0xc3, 0xfc, 0x70,
  0x71, 0xfc, 0x70, 0xdf, 0xf9, 0xfc, 0xc0, 0x10, 0x06, 0x04, 0x78, 0x71, 0x80, 0x78, 0xc1, 0x83,
  0x00, 0xc0, 0x10, 0x06, 0x00, 0x78, 0xf1, 0x80, 0x78, 0xc1, 0x83, 0x00, 0xe0, 0x10, 0x0c, 0x00,
  0x68, 0xf1, 0x80, 0x6c, 0xc1, 0x83, 0x80, 0x7c, 0x1f, 0xcc, 0x00, 0x6d, 0xb1, 0xfc, 0x6c, 0xc1,
  0x81, 0xf0, 0x3f, 0x1f, 0xcc, 0x3e, 0x6d, 0xb1, 0xfc, 0x66, 0xc1, 0x80, 0xfc, 0x03, 0x10, 0x0c,
  0x0e, 0x67, 0x31, 0x80, 0x66, 0xc1, 0x80, 0x0c, 0x03, 0x10, 0x0c, 0x06, 0x67, 0x31, 0x80, 0x63,
  0xc1, 0x80, 0x06, 0x03, 0x10, 0x06, 0x06, 0x63, 0x31, 0x80, 0x63, 0xc1, 0x80, 0x06, 0xc3, 0x18,
  0x07, 0x0e, 0x60, 0x31, 0x80, 0x61, 0xc1, 0x83, 0x0c, 0xfe, 0x1f, 0xc1, 0xfc, 0x60, 0x31, 0xfe,
  0x61, 0xc1, 0x83, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x70, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x60, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x60,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x67, 0xff, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x66, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63,
  0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x67, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x61, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xe0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};
// 'selection_bar_sub', 36x15px
const unsigned char BITMAP_SELECTION_BAR_SUB[] PROGMEM = {
	0xc0, 0x00, 0x00, 0x00, 0x30, 0x80, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x10, 0x80, 
	0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 
	0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 
	0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 
	0x10, 0x80, 0x00, 0x00, 0x00, 0x10, 0xc0, 0x00, 0x00, 0x00, 0x30
};

// 'UNI_CHANNEL_SEL_BAR', 57x9px
const unsigned char BITMAP_UNI_CHANNEL_SEL_BAR[] PROGMEM = {
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00
};

// 'SAVED_SCREEN', 91x29px
const unsigned char BITMAP_SAVED_SCREEN[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x07, 0x18, 0x0d, 0xfe, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xfe, 0x07, 0x18, 0x19, 0xfe, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0f, 0x0c,
  0x19, 0x80, 0x60, 0xc0, 0xff, 0xff, 0xd0, 0x00, 0x01, 0x80, 0x0d, 0x8c, 0x19, 0x80, 0x60, 0x60,
  0xff, 0xff, 0xe8, 0x00, 0x00, 0xc0, 0x0d, 0x8c, 0x31, 0x80, 0x60, 0x60, 0xfc, 0x00, 0x74, 0x00,
  0x00, 0xfc, 0x18, 0x86, 0x31, 0xfe, 0x60, 0x60, 0xfc, 0x06, 0x7a, 0x00, 0x00, 0x3e, 0x18, 0xc6,
  0x21, 0xfc, 0x60, 0x60, 0xfc, 0x06, 0x7d, 0x00, 0x00, 0x07, 0x18, 0xc2, 0x61, 0x80, 0x60, 0x60,
  0xfc, 0x06, 0x7e, 0x80, 0x00, 0x03, 0x3f, 0xe3, 0x61, 0x80, 0x60, 0x60, 0xfc, 0x06, 0x7e, 0x80,
  0x00, 0x03, 0x30, 0x63, 0xc1, 0x80, 0x60, 0xe0, 0xfc, 0x06, 0x7e, 0x80, 0x01, 0x86, 0x60, 0x61,
  0xc1, 0x80, 0x67, 0xc0, 0xfc, 0x06, 0x7e, 0x80, 0x00, 0xfc, 0x60, 0x31, 0xc1, 0xfe, 0x7f, 0x00,
  0xfc, 0x00, 0x7e, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x80, 0x00, 0x00, 0x00, 0xf0,
  0x30, 0x60, 0x00, 0x00, 0xf0, 0x00, 0x1e, 0x80, 0x00, 0x00, 0x01, 0xfc, 0x31, 0xc0, 0x00, 0x00,
  0xf0, 0x00, 0x1e, 0x80, 0x00, 0x00, 0x03, 0x06, 0x33, 0x80, 0x00, 0x00, 0xf3, 0xff, 0x9e, 0x80,
  0x00, 0x00, 0x06, 0x06, 0x37, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x1e, 0x80, 0x00, 0x00, 0x06, 0x03,
  0x3e, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x1e, 0x80, 0x00, 0x00, 0x06, 0x03, 0x3c, 0x00, 0x00, 0x00,
  0xf3, 0xff, 0x9e, 0x80, 0x00, 0x00, 0x06, 0x03, 0x3c, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x1e, 0x80,
  0x00, 0x02, 0x06, 0x03, 0x36, 0x00, 0x40, 0x00, 0xf0, 0x00, 0x1e, 0x80, 0x00, 0x03, 0x06, 0x07,
  0x33, 0x00, 0xc0, 0x00, 0xf0, 0x00, 0x1e, 0x80, 0x00, 0x03, 0x07, 0x06, 0x31, 0x80, 0xc0, 0x00,
  0xff, 0xff, 0xfe, 0x80, 0x00, 0x03, 0x03, 0x8c, 0x30, 0xc0, 0xc0, 0x00, 0xff, 0xff, 0xfe, 0x80,
  0x00, 0x03, 0x01, 0xf8, 0x30, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x80, 0x00,
  0x00, 0x01, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0x80, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00
};

// 'COLON', 2x10px
const unsigned char BITMAP_COLON[] PROGMEM = {
  0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0
};

enum {
  NMBR_ARTNET_REC_PAGE,
  NMBR_DMX_CHANNEL_SEL_BAR,
  NMBR_DMX_PAGE,
  NMBR_HSV_PAGE,
  NMBR_RGB_PAGE,
  NMBR_SEGMENTS_PAGE,
  NMBR_SELECTION_BAR_SUB,
  NMBR_UNI_CHANNEL_SEL_BAR,
  NMBR_SAVED_SCREEN,
  NMBR_COLON
};

#define BITMAP_SUB_MENU_LEN 10

int W_H_MATRIX_SUB_MENU[BITMAP_SUB_MENU_LEN][2] = {
  { 63, 12 },
  { 71, 9 },
  { 35, 12 },
  { 117, 12 },
  { 121, 12 },
  { 87, 28 },
  { 36, 15 },
  { 57, 9 },
  { 91, 29 },
  { 2, 10 }
};

int X_Y_MATRIX_SUB_MENU[BITMAP_SUB_MENU_LEN][2] = {
  { 32, 1 },
  { 56, 22 },
  { 46, 1 },
  { 5, 1 },
  { 5, 1 },
  { 20, 1 },
  { 3, 14 },
  { 1, 22 },
  { 18, 1 },
  { 77, 7 }
};

const unsigned char *BITMAP_SUB_MENU_ARRAY[BITMAP_SUB_MENU_LEN] = {
  BITMAP_ARTNET_REC_PAGE,
  BITMAP_DMX_CHANNEL_SEL_BAR,
  BITMAP_DMX_PAGE,
  BITMAP_HSV_PAGE,
  BITMAP_RGB_PAGE,
  BITMAP_SEGMENTS_PAGE,
  BITMAP_SELECTION_BAR_SUB,
  BITMAP_UNI_CHANNEL_SEL_BAR,
  BITMAP_SAVED_SCREEN,
  BITMAP_COLON
};

enum {
  LAN_SYMBOL,
  WIFI_SYMBOL_1,
  WIFI_SYMBOL_2,
  WIFI_SYMBOL_3
};

#define BITMAP_ICONS_LEN 4

int W_H_MATRIX_ICONS[BITMAP_ICONS_LEN][2] = {
  { 15, 12 },
  { 6, 4 },
  { 10, 6 },
  { 14, 8 }
};

int X_Y_MATRIX_ICONS[BITMAP_ICONS_LEN][2] = {
  { 105, 1 },
  { 12, 7 },
  { 10, 5 },
  { 8, 3 }
};

// 'LAN_SYMBOL', 14x8px
const unsigned char BITMAP_LAN_SYMBOL[] PROGMEM = {
  0xff, 0xfe, 0xaa, 0xaa, 0xaa, 0xaa, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0xe0, 0x0e,
  0xe0, 0x0e, 0xfc, 0x7e, 0xfc, 0x7e, 0x7f, 0xfc
};
// 'WIFI_SYMBOL_1', 14x8px
const unsigned char BITMAP_WIFI_SYMBOL_1[] PROGMEM = {
  0x78, 0x84, 0x30, 0x30
};
// 'WIFI_SYMBOL_2', 14x8px
const unsigned char BITMAP_WIFI_SYMBOL_2[] PROGMEM = {
  0x3f, 0x00, 0x40, 0x80, 0x9e, 0x40, 0x21, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'WIFI_SYMBOL_3', 14x8px
const unsigned char BITMAP_WIFI_SYMBOL_3[] PROGMEM = {
  0x1f, 0xe0, 0x20, 0x10, 0x4f, 0xc8, 0x90, 0x24, 0x27, 0x90, 0x08, 0x40, 0x03, 0x00, 0x03, 0x00
};

const unsigned char *BITMAP_ICONS_ARRAY[BITMAP_ICONS_LEN] = {
  BITMAP_LAN_SYMBOL,
  BITMAP_WIFI_SYMBOL_1,
  BITMAP_WIFI_SYMBOL_2,
  BITMAP_WIFI_SYMBOL_3
};

enum {
  NMBR_SEGMENTS_OPTION,
  NMBR_FIRMWARE_OPTION
};

#define BITMAP_SETTINGS_LEN 2

int W_H_MATRIX_SETTINGS[BITMAP_ICONS_LEN][2] = {
  { 74, 14 },
  { 67, 12 },
};

int X_Y_MATRIX_SETTINGS[BITMAP_ICONS_LEN][2] = {
  { 0, 5 },
  { 4, 4 },
};

// 'SEGMENTS_OPTION', 74x14px
const unsigned char BITMAP_SEGMENTS_OPTION[] PROGMEM = {
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0xe2, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0x00, 0x00, 0xc0, 0x0c, 0x04, 0x00, 0x86, 0x03, 0x00, 0x83, 0x02, 0x00, 0xc0, 0x1f,
  0x0f, 0xcf, 0xff, 0x0f, 0x8f, 0xe7, 0xcf, 0x80, 0xf0, 0x31, 0x98, 0xce, 0x71, 0x98, 0xce, 0x63,
  0x18, 0x00, 0x7e, 0x61, 0x90, 0xcc, 0x31, 0x98, 0x4c, 0x23, 0x18, 0x00, 0x0e, 0x7f, 0xb0, 0xcc,
  0x21, 0x9f, 0xcc, 0x33, 0x0f, 0x00, 0x03, 0x60, 0x30, 0xcc, 0x21, 0x98, 0x0c, 0x33, 0x03, 0x80,
  0x03, 0x60, 0x18, 0xcc, 0x21, 0x98, 0x0c, 0x33, 0x00, 0xc0, 0xc7, 0x30, 0x9f, 0xcc, 0x21, 0x9c,
  0x4c, 0x33, 0x10, 0xc0, 0xfe, 0x1f, 0x8f, 0xcc, 0x21, 0x8f, 0xcc, 0x31, 0xdf, 0x80, 0x00, 0x00,
  0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'FIRMWARE_OPTION', 67x12px
const unsigned char BITMAP_FIRMWARE_OPTION[] PROGMEM = {
  0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x86, 0x10, 0x00,
  0x01, 0x80, 0x23, 0x00, 0xc0, 0x8f, 0xbf, 0x78, 0xce, 0x67, 0xe3, 0xe7, 0xc0, 0xfc, 0x8c, 0x31,
  0xcc, 0xce, 0x60, 0x63, 0x0c, 0x60, 0xfc, 0x8c, 0x31, 0x8c, 0xce, 0x40, 0x63, 0x18, 0x60, 0xc0,
  0x8c, 0x31, 0x8c, 0x5a, 0xc7, 0xe3, 0x1f, 0xe0, 0xc0, 0x8c, 0x31, 0x8c, 0x7b, 0xcc, 0x23, 0x18,
  0x00, 0xc0, 0x8c, 0x31, 0x8c, 0x73, 0xcc, 0x23, 0x18, 0x00, 0xc0, 0x8c, 0x31, 0x8c, 0x71, 0x8c,
  0x63, 0x0c, 0x20, 0xc0, 0x8c, 0x31, 0x8c, 0x31, 0x87, 0xe3, 0x07, 0xe0
};

const unsigned char *BITMAP_SETTINGS_ARRAY[BITMAP_SETTINGS_LEN] = {
  BITMAP_SEGMENTS_OPTION,
  BITMAP_FIRMWARE_OPTION
};
#endif