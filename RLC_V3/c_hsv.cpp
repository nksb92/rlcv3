#include "c_hsv.h"

C_HSV::C_HSV(uint8_t _hue, uint8_t _sat_p, uint8_t _val_p)
{
    hue = _hue;
    sat_p = _sat_p;
    val_p = _val_p;
}

/**
 * Adds an amount to the current hue value.
 * @param amount: The amount to add.
 */
void C_HSV::add_hue(int amount)
{
    hue += amount;
}

/**
 * Adds an amount to the current saturation value.
 * If the result is greater than 100 or less than 0, it is clamped to the maximum or minimum value, respectively.
 * @param amount: The amount to add.
 */
void C_HSV::add_sat(int amount)
{
    if (sat_p + amount > 100)
        sat_p = 100;
    else if (sat_p + amount <= 0)
        sat_p = 0;
    else
        sat_p += amount;
}

/**
 * Adds an amount to the current value/brightness value.
 * If the result is greater than 100 or less than 0, it is clamped to the maximum or minimum value, respectively.
 * @param amount: The amount to add.
 */
void C_HSV::add_val(int amount)
{
    if (val_p + amount > 100)
        val_p = 100;
    else if (val_p + amount <= 0)
        val_p = 0;
    else
        val_p += amount;
}

/**
 * Returns the current hue value.
 * @return The hue value between 0 and 255 (in 360/255 steps).
 */
uint8_t C_HSV::get_hue()
{
    return hue;
}

/**
 * Returns the current saturation value.
 * @return The saturation value between 0 and 100 (as a percentage).
 */
uint8_t C_HSV::get_sat_p()
{
    return sat_p;
}

/**
 * Returns the current value/brightness value.
 * @return The value/brightness value between 0 and 100 (as a percentage).
 */
uint8_t C_HSV::get_val_p()
{
    return val_p;
}

/**
 * Sets the value/brightness value to the given value, clamping it to the maximum or minimum value if necessary.
 * @param value: The value to set the value/brightness to.
 */
void C_HSV::set_val_p(uint8_t value)
{
    val_p = 0;
    add_val(value);
}

/**
 * Sets the value/brightness value to the given value, clamping it to the maximum or minimum value if necessary.
 * @param value: The value to set the value/brightness to.
 */
void C_HSV::set_sat_p(uint8_t value)
{
    sat_p = 0;
    add_sat(value);
}

/**
 * Sets the hue to the given value in 360/255 steps.
 * @param value: The hue value to set.
 */
void C_HSV::set_hue_byte(uint8_t value)
{
    hue = value;
}

/**
 * Returns the current mode.
 * @return The current mode.
 */
uint8_t C_HSV::get_current()
{
    return current;
}

/**
 * Sets the current mode to the given mode. If the given mode is greater than or equal to the total number of modes,
 * sets the mode to the last available mode.
 * @param _current: The mode to set the current mode to.
 */
void C_HSV::set_current(uint8_t _current)
{
    if (_current >= HSV_LAST)
    {
        current = HSV_LAST - 1;
    }
    else
    {
        current = _current;
    }
}

/**
 * Sets the current mode to HUE.
 */
void C_HSV::set_hue()
{
    current = HUE;
}

/**
 * Sets the current mode to SAT.
 */
void C_HSV::set_sat()
{
    current = SAT;
}

/**
 * Sets the current mode to VAL.
 */
void C_HSV::set_val()
{
    current = VAL;
}

/**
 * Sets the current mode to the next mode in the enum.
 * If the current mode is the last one, sets it to HUE.
 */
void C_HSV::next()
{
    current++;
    if (current >= HSV_LAST)
    {
        set_hue();
    }
}