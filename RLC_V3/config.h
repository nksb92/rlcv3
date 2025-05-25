#if !defined(CONFIG_H)
#define CONFIG_H

// first digit:  increment if breaking change occures
// last digit:   increment before each pull request for new feature or bug fix
#define RLCV3_FIRMWARE_VERSION "1.0"

// ----------------------------------------------------------------------------------------------------------------------------------------
//
//                   ONLY UNCOMMENT ONE OF THE OPTIONS
//
#define RGB_IC_TUBE // Sets the mode for hardware to RGB_IC: usage with led strip like WS2815, WS2812B
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
#ifdef RGB_IC_TUBE
#define NO_FAN
#define LED_OUT_RGBIC
#define NUM_PIXEL 20
#endif

#ifdef RGB_TUBE
#define NO_FAN
#define LED_OUT_MOSFET
#define RED_PIN D10
#define GREEN_PIN D9
#define BLUE_PIN D8
#define NUM_PIXEL 1
#endif

#ifdef PANEL
#define LED_OUT_I2C

#define FAN_USAGE
#define PWM_PIN D8
#define FAN_MAX_SPEED 225
#define FAN_MIN_SPEED 50
#define FAN_ZERO_RPM false

#define NUM_PIXEL 5
#endif

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
#endif

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
#endif // CONFIG_H
