/**
 * @file RLC_V3_PANEL.ino
 * @brief Firmware for the ATtiny402-based panel slave segment controller.
 * 
 * Listens on I2C for RGB color values and outputs WS2812/WS2815 NeoPixel signals.
 * Since RAM is very limited, it is optimized to output a single uniform color across
 * all pixels in the segment.
 */

#include "tinyNeoPixelModded.h"
#include <Wire.h>

// Note: Change buffer size to 16 Byte in megaTinyCore Wire library config if needed
// to prevent ATtiny402 from running out of RAM.

//    Pinout AtTiny402
//          ____
// 1 VDD  -|    |-  8 GND
// 2 PA6  -|    |-  7 PA3
// 3 PA7  -|    |-  6 PA0 (UPDI)
// 4 PA1  -|____|-  5 PA2

#define DATA_OUT PIN_PA7        /**< NeoPixel data output pin. */
#define LED_PIN PIN_PA6
#define SDA_PIN PIN_PA1         /**< I2C SDA pin. */
#define SCL_PIN PIN_PA2         /**< I2C SCL pin. */
#define NUM_PIXEL 75            /**< Length of the LED segment. */

// Select Slave Address
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

/**
 * @struct rgb_data
 * @brief Simple storage structure for receiving 8-bit RGB color packets.
 */
struct rgb_data {
  uint8_t red;   /**< Red intensity. */
  uint8_t green; /**< Green intensity. */
  uint8_t blue;  /**< Blue intensity. */
};

tinyNeoPixelModded leds = tinyNeoPixelModded(1, PIN_PA7);
rgb_data data;

/**
 * @brief I2C receive event callback.
 * Reads 3 bytes of RGB data, updates the local color state, and triggers NeoPixel show.
 * @param[in] len The number of bytes received.
 */
void onReceive(int len) {
  data.red = Wire.read();
  data.green = Wire.read();
  data.blue = Wire.read();
  leds.setPixelColor(0, data.red, data.green, data.blue);
  leds.show(NUM_PIXEL);
}

/**
 * @brief Initializes I2C slave mode, sets callbacks, and readies NeoPixel output.
 */
void setup() {
  // sanity delay
  delay(2000);
  
  // begin with standard pins: PA1 and PA2
  Wire.onReceive(onReceive);
  Wire.begin((uint8_t)ADDRESS);

  leds.begin();
}

/**
 * @brief Idle loop. All processing is event-driven via I2C callbacks.
 */
void loop() {
}