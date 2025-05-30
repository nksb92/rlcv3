#if !defined(C_HSV_H)
#define C_HSV_H

#include <Arduino.h>

// #define PERCENTAGE
#define FULL_RANGE

#if (defined(PERCENTAGE) + defined(FULL_RANGE)) != 1
#error "Only one config has to be defined for HSV value and saturation limitation."
#endif

#if defined(PERCENTAGE)
#define MAX_VALUE_SAT_VAL 100
#endif

#if defined(FULL_RANGE)
#define MAX_VALUE_SAT_VAL 255
#endif

/**
 * An enum to define the possible hsv modes.
 */
enum
{
   HUE,
   SAT,
   VAL,
   HSV_LAST
};

class C_HSV
{
   uint8_t hue; // The hue value between 0 and 255 (in 360/255 steps).
   uint8_t sat; // The saturation value between 0 and MAX_VALUE_SAT_VAL (as a percentage or full range).
   uint8_t val; // The value/brightness value between 0 and MAX_VALUE_SAT_VAL (as a percentage or full range).

   uint8_t current = HUE; // The current mode, initialized to HUE.

public:
   /**
    * Constructor that takes the hue, saturation, and value as arguments.
    * @param _hue: The hue value between 0 and 255 (in 360/255 steps).
    * @param _sat: The saturation value between 0 and MAX_VALUE_SAT_VAL (as a percentage or full range).
    * @param _val: The value/brightness value between 0 and MAX_VALUE_SAT_VAL (as a percentage or full range).
    */
   C_HSV(uint8_t _hue, uint8_t _sat, uint8_t _val);

   /**
    * Adds an amount to the current hue value.
    * @param amount: The amount to add.
    */
   void add_hue(int amount);

   /**
    * Adds an amount to the current saturation value.
    * If the result is greater than 100 or less than 0, it is clamped to the maximum or minimum value, respectively.
    * @param amount: The amount to add.
    */
   void add_sat(int amount);

   /**
    * Adds an amount to the current value/brightness value.
    * If the result is greater than 100 or less than 0, it is clamped to the maximum or minimum value, respectively.
    * @param amount: The amount to add.
    */
   void add_val(int amount);

   /**
    * Returns the current hue value.
    * @return The hue value between 0 and 255 (in 360/255 steps).
    */
   uint8_t get_hue();

   /**
    * Returns the current saturation value.
    * @return The saturation value between 0 and 100 (as a percentage).
    */
   uint8_t get_sat();

   /**
    * Returns the current value/brightness value.
    * @return The value/brightness value between 0 and 100 (as a percentage).
    */
   uint8_t get_val();

   /**
    * Sets the value/brightness value to the given value, clamping it to the maximum or minimum value if necessary.
    * @param value: The value to set the value/brightness to.
    */
   void set_val(uint8_t value);

   /**
    * Sets the value/brightness value to the given value, clamping it to the maximum or minimum value if necessary.
    * @param value: The value to set the value/brightness to.
    */
   void set_sat(uint8_t value);

   /**
    * Sets the hue to the given value in 360/255 steps.
    * @param value: The hue value to set.
    */
   void set_hue_byte(uint8_t value);

   /**
    * Returns the current mode.
    * @return The current mode.
    */
   uint8_t get_current();

   /**
    * Sets the current mode to the given mode. If the given mode is greater than or equal to the total number of modes,
    * sets the mode to the last available mode.
    * @param _current: The mode to set the current mode to.
    */
   void set_current(uint8_t _current);

   /**
    * Sets the current mode to HUE.
    */
   void set_hue();

   /**
    * Sets the current mode to SAT.
    */
   void set_sat();

   /**
    * Sets the current mode to VAL.
    */
   void set_val();

   /**
    * Sets the current mode to the next mode in the enum.
    * If the current mode is the last one, sets it to HUE.
    */
   void next();
};

#endif // C_HSV_H
