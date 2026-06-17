/**
 * @file config.h
 * @brief Central configuration file defining hardware profiles, firmware settings, and macro choices.
 */

#if !defined(RLCV3_CONFIG_H)
#define RLCV3_CONFIG_H

// first digit:  increment if breaking change occures
// last digit:   increment before each pull request for new feature or bug fix to main branch
#define RLCV3_FIRMWARE_VERSION "2.1"

// Comment out this line to disable all debug output
// #define DEBUGGING_ENABLED

#ifdef DEBUGGING_ENABLED
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#define DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__)
#else
// If disabled, these macros are replaced with nothing
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#define DEBUG_PRINTF(...)
#endif

// ----------------------------------------------------------------------------------------------------------------------------------------
//
//                   ONLY UNCOMMENT ONE OF THE OPTIONS
//
#define RGB_IC_TUBE  // Sets the mode for hardware to RGB_IC: usage with led strip like WS2815, WS2812B
// #define RGB_TUBE // Sets the mode for hardware to RGB: usage with rgb led strip driven with mosfets
// #define PANEL // Sets the mode for hardware to PANEL: usage with slave deveices controlled via i2c and cooling fan
// #define SPOT // Sets the mode for hardware to SPOT: usage with a single cob rgb led and cooling fan
// ----------------------------------------------------------------------------------------------------------------------------------------

// check if zero or more than one config is selected
#if defined(RGB_IC_TUBE) + defined(RGB_TUBE) + defined(PANEL) + defined(SPOT) != 1
#error "Zero or more than one hardware config is active. Check the hardware config settings in the 'config.h' file."
#endif

// ----------------------------------------------------------------------------------------------------------------------------------------
//
//                   CONFIGURATION OF THE HARDWARE FROM THE SELECTION ABOVE
//
// OPTIONS:
// -> led output type, dependend on the led strip / hardware
//    -> LED_OUT_RGBIC: addressable led strip
//    -> LED_OUT_MOSFET: rgb control with mosfets/transitors via 8 bit PWM
//    -> LED_OUT_I2C: rgb + dimmer values are sent via I2C to slave devices
// -> led color type, dependend on the connected led strip / hardware
//    -> LED_COLOR_TYPE_RGB: standard rgb
//    -> LED_COLOR_TYPE_RGBW: rgb + white
//    -> LED_COLOR_TYPE_RGBCCT: rgb + warm white + cold white
// -> NUM_PIXEL: number of the pixels of the LED strip: integer value >= 1 >= 170
//    (170 ~= (512 - 1) / 3) (170 ~= (DMX_UNIVERSE - DIMMER_CHANNEL) / RGB)
//    for rgb non addressable strip NUM_PIXEL of 1 is needed
// -> fan controll:
//    -> FAN_USAGE: defined if a fan is required with the hardware
//    -> FAN_MAX_SPEED: required if FAN_USAGE is defined -> maximum 8 bit PWM value of the fan
//    -> FAN_MIN_SPEED: required if FAN_USAGE is defined -> minimum 8 bit PWM value of the fan
//    -> ZERO_PWM:  required if FAN_USAGE is defined -> true: values below FAN_MIN_SPEED turnes the fan off;
//                                                      false: values below FAN_MIN_SPEED are clamped to FAN_MIN_SPEED value
// ----------------------------------------------------------------------------------------------------------------------------------------

#define LED_COLOR_TYPE_RGB 0
#define LED_COLOR_TYPE_RGBW 1
#define LED_COLOR_TYPE_RGBCCT 2

// ----------------------------------------------------------------------------------------------------------------------------------------
#ifdef RGB_IC_TUBE
#define NO_FAN
#define LED_OUT_RGBIC
#define NUM_PIXEL 24

// LED strip configuration
#define COLOR_ORDER_WS2815 NEO_GRB
#define COLOR_ORDER_WS2811 NEO_RGB
#define COLOR_ORDER_COB_RGBIC NEO_RGB
// #define COLOR_ORDER COLOR_ORDER_WS2815
// #define COLOR_ORDER COLOR_ORDER_WS2811
#define COLOR_ORDER COLOR_ORDER_COB_RGBIC

// Note: To change the chipset type or LED class (e.g. NeoPixelBus features/methods),
// refer to the instantiation in leds.cpp.

#define LED_COLOR_TYPE LED_COLOR_TYPE_RGBCCT

// CCT Settings (used when LED_COLOR_TYPE is LED_COLOR_TYPE_RGBCCT)
#define CCT_MIN_KELVIN 3000
#define CCT_MAX_KELVIN 6500
#define CCT_STEP_SIZE  50

// RGB Emulation of White (used when LED_COLOR_TYPE is LED_COLOR_TYPE_RGB)
#define RGB_WW_R 255
#define RGB_WW_G 90
#define RGB_WW_B 10
#define RGB_CW_R 255
#define RGB_CW_G 255
#define RGB_CW_B 255
#endif

// ----------------------------------------------------------------------------------------------------------------------------------------
#ifdef RGB_TUBE
#define NO_FAN
#define LED_OUT_MOSFET
#define RED_PIN D10
#define GREEN_PIN D9
#define BLUE_PIN D8
#define NUM_PIXEL 1

#define LED_COLOR_TYPE LED_COLOR_TYPE_RGB

// CCT Settings
#define CCT_MIN_KELVIN 3000
#define CCT_MAX_KELVIN 6500
#define CCT_STEP_SIZE  50

// RGB Emulation of White
#define RGB_WW_R 255
#define RGB_WW_G 90
#define RGB_WW_B 10
#define RGB_CW_R 255
#define RGB_CW_G 255
#define RGB_CW_B 255
#endif

// ----------------------------------------------------------------------------------------------------------------------------------------
#ifdef PANEL
#define LED_OUT_I2C

#define FAN_USAGE
#define PWM_PIN D8
#define FAN_MAX_SPEED 225
#define FAN_MIN_SPEED 60
#define FAN_ZERO_RPM false

#define NUM_PIXEL 5

#define LED_COLOR_TYPE LED_COLOR_TYPE_RGB

// CCT Settings
#define CCT_MIN_KELVIN 3000
#define CCT_MAX_KELVIN 6500
#define CCT_STEP_SIZE  50

// RGB Emulation of White
#define RGB_WW_R 255
#define RGB_WW_G 90
#define RGB_WW_B 10
#define RGB_CW_R 255
#define RGB_CW_G 255
#define RGB_CW_B 255
#endif

// ----------------------------------------------------------------------------------------------------------------------------------------
#ifdef SPOT
#define LED_OUT_MOSFET
#define RED_PIN D10
#define GREEN_PIN D8
#define BLUE_PIN D9

#define FAN_USAGE
#define PWM_PIN D3
#define FAN_MAX_SPEED 255
#define FAN_MIN_SPEED 75
#define FAN_ZERO_RPM true

#define NUM_PIXEL 1

#define LED_COLOR_TYPE LED_COLOR_TYPE_RGB

// CCT Settings
#define CCT_MIN_KELVIN 3000
#define CCT_MAX_KELVIN 6500
#define CCT_STEP_SIZE  50

// RGB Emulation of White
#define RGB_WW_R 255
#define RGB_WW_G 90
#define RGB_WW_B 10
#define RGB_CW_R 255
#define RGB_CW_G 255
#define RGB_CW_B 255
#endif

// ----------------------------------------------------------------------------------------------------------------------------------------

#ifdef NO_FAN
#define PWM_PIN NOT_A_PIN
#define FAN_MAX_SPEED 0
#define FAN_MIN_SPEED 0
#define FAN_ZERO_RPM false
#endif

// check correct number of pixel
#if defined(NUM_PIXEL) == 0 || defined(NUM_PIXEL) > 170
#error "Pixel number is below 1 or above 170. Adjust NUM_PIXEL parameter."
#endif

// check if fan control config is correct
#if defined(FAN_USAGE) && (!defined(PWM_PIN) || !defined(FAN_MAX_SPEED) || !defined(FAN_MIN_SPEED) || !defined(FAN_ZERO_RPM))
#error "With FAN_USAGE active, min/max speed and zero rpm mode have to be defined."
#endif

// check if pwm led output config is correct
#if defined(LED_OUT_MOSFET) && (!defined(RED_PIN) || !defined(GREEN_PIN) || !defined(BLUE_PIN))
#error "With LED_OUT_MOSFET active, red, green and blue pins have to be defined."
#endif

// check if rgbcct config is correct
#if (LED_COLOR_TYPE == LED_COLOR_TYPE_RGBCCT) && (!defined(CCT_MIN_KELVIN) || !defined(CCT_MAX_KELVIN) || !defined(CCT_STEP_SIZE))
#error "With LED_COLOR_TYPE_RGBCCT active, CCT_MIN_KELVIN, CCT_MAX_KELVIN, and CCT_STEP_SIZE have to be defined."
#endif
#endif  // RLCV3_CONFIG_H
