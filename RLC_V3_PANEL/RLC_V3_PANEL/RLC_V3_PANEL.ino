#include "tinyNeoPixelModded.h"
#include <Wire.h>
// I2C for Attiny
// Changed buffer size to 16 Byte, otherwise the 402 Controller runs out of RAM
// https://github.com/SpenceKonde/megaTinyCore/tree/master/megaavr/libraries/Wire

// NeoPixel for Attiny
// Modified code to output one Color for all Pixel to save up RAM
// Only works with 16 Mhz clock speed

//    Pinout AtTiny402
//          ____
// 1 VDD  -|    |-  8 GND
// 2 PA6  -|    |-  7 PA3
// 3 PA7  -|    |-  6 PA0 (UPDI)
// 4 PA1  -|____|-  5 PA2

#define DATA_OUT PIN_PA7
#define LED_PIN PIN_PA6
#define SDA_PIN PIN_PA1
#define SCL_PIN PIN_PA2
#define NUM_PIXEL 75

// Select Slave Adress
// #define HW_INDEX_0 0
#define HW_INDEX_1 1
// #define HW_INDEX_2 2
// #define HW_INDEX_3 3
// #define HW_INDEX_4 4

#ifdef HW_INDEX_0
#define ADDRESS 0x08
#endif

#ifdef HW_INDEX_1
#define ADDRESS 0x09
#endif

#ifdef HW_INDEX_2
#define ADDRESS 0x0A
#endif

#ifdef HW_INDEX_3
#define ADDRESS 0x0B
#endif

#ifdef HW_INDEX_4
#define ADDRESS 0x0C
#endif

// struct for storing incoming data
struct rgb_data {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

// For WS2815 no dedicated Chipset in library, therefore the standart is used
tinyNeoPixelModded leds = tinyNeoPixelModded(1, PIN_PA7);
rgb_data data;

void onReceive(int len) {
  data.red = Wire.read();
  data.green = Wire.read();
  data.blue = Wire.read();
  leds.setPixelColor(0, data.red, data.green, data.blue);
  leds.show(NUM_PIXEL);
}

void setup() {
  // sanity delay
  delay(2000);
  // begin with standart pins
  // PA1 (4) and PA2 (5)
  Wire.onReceive(onReceive);
  Wire.begin((uint8_t)ADDRESS);

  leds.begin();
}

void loop() {
}