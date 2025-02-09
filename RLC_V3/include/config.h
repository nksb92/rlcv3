#if !defined(CONFIG_H)
#define CONFIG_H

// ------------------------------------------------------------------------------------------------------
//
//                   ONLY UNCOMMENT ONE OF THE OPTIONS
//
// #define RGB_IC_TUBE // Sets the mode for hardware to RGB_IC: usage with led strip like WS2815, WS2812B
// #define RGB_TUBE // Sets the mode for hardware to RGB: usage with rgb led strip driven with mosfets
// #define PANEL // Sets the mode for hardware to PANEL: usage with slave deveices controlled via i2c and cooling fan
#define SPOT // Sets the mode for hardware to SPOT: usage with a single cob rgb led and cooling fan
// ------------------------------------------------------------------------------------------------------

// check if zero or more than one config is selected
#if defined(RGB_IC_TUBE) + defined(RGB_TUBE) + defined(PANEL) + defined(SPOT) != 1
#error "Zero or more than one hardware config is active. Check the hardware config settings in the 'config.h' file."
#endif

#ifdef RGB_IC_TUBE
#define LED_OUT_RGBIC
#define NUM_PIXEL 20
#endif

#ifdef RGB_TUBE
#define LED_OUT_MOSFET
#define NUM_PIXEL 1
#endif

#ifdef PANEL
#define LED_OUT_I2C
#define FAN_USAGE
#define NUM_PIXEL 5
#endif

#ifdef SPOT
#define LED_OUT_MOSFET
#define FAN_USAGE
#define NUM_PIXEL 1
#endif

#endif // CONFIG_H
