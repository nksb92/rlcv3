#include "menu_structure.h"

menu_structure::menu_structure(/* args */)
{
}

menu_structure::~menu_structure()
{
}

void menu_structure::init()
{
    // if (CURRENT_MODE == RGB) last_menu = MAIN_LAST - 1;
}

/**
 * Returns the current mode.
 */
uint8_t menu_structure::get_current()
{
    return current;
}

uint8_t menu_structure::get_deepness()
{
    return deepness;
}

/**
 * Sets the current mode to the given mode. If the given mode is greater than or equal to the total number of modes,
 * sets the mode to the last available mode.
 * @param _current: The mode to set the current mode to.
 */
void menu_structure::set_current(uint8_t _current)
{
    if (_current >= MAIN_LAST)
    {
        current = MAIN_LAST - 1;
    }
    else
    {
        current = _current;
    }
}

void menu_structure::set_deepness(uint8_t _deepness)
{
    if (_deepness >= MAX_DEEP)
    {
        deepness = MAX_DEEP - 1;
    }
    else
    {
        deepness = _deepness;
    }
}

void menu_structure::add_current(int val)
{
    int temp = current + val;
    if (temp >= last_menu)
    {
        current = HSV_PAGE;
    }
    else if (temp < 0)
    {
        current = last_menu - 1;
    }
    else
    {
        current = temp;
    }
}

void menu_structure::deeper()
{
    deepness++;
    if (deepness >= MAX_DEEP)
    {
        deepness = 0;
    }
}