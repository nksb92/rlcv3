#include "c_rgb.h"

C_RGB::C_RGB(uint8_t red, uint8_t green, uint8_t blue)
{
    rgb_color.r = red;
    rgb_color.g = green;
    rgb_color.b = blue;
}

void C_RGB::set_current(uint8_t value)
{
    current = value;
}

void C_RGB::next()
{
    current++;
    if (current >= RGB_LAST)
    {
        current = RED;
    }
}

uint8_t C_RGB::get_current()
{
    return current;
}

void C_RGB::set_red(uint8_t value)
{
    rgb_color.r = value;
}

void C_RGB::add_red(int value)
{
    rgb_color.r += value;
}

uint8_t C_RGB::get_red()
{
    return rgb_color.r;
}

void C_RGB::set_green(uint8_t value)
{
    rgb_color.g = value;
}

void C_RGB::add_green(int value)
{
    rgb_color.g += value;
}

uint8_t C_RGB::get_green()
{
    return rgb_color.g;
}

void C_RGB::set_blue(uint8_t value)
{
    rgb_color.b = value;
}

void C_RGB::add_blue(int value)
{
    rgb_color.b += value;
}

uint8_t C_RGB::get_blue()
{
    return rgb_color.b;
}

void C_RGB::set_rgb(CRGB rgb_value)
{
    rgb_color = rgb_value;
}

CRGB C_RGB::get_rgb()
{
    return rgb_color;
}