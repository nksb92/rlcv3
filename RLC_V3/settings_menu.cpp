#include "settings_menu.h"

settings_menu::settings_menu()
{
    current_menu_item = SEGMENTS;
}

settings_menu::~settings_menu()
{
}

void settings_menu::add_setting(int value)
{
    if (value != 0)
    {
        if (value < 0)
        {
            if (current_menu_item - 1 >= 0)
            {
                current_menu_item--;
            }
            else
            {
                current_menu_item = LAST_SETTING - 1;
            }
        }
        else
        {
            if (current_menu_item + 1 < LAST_SETTING)
            {
                current_menu_item++;
            }
            else
            {
                current_menu_item = SEGMENTS;
            }
        }
    }
}

void settings_menu::handle_submenu()
{
    switch (current_menu_item)
    {
    case SEGMENTS:
        /* code */
        break;
    case FIRMWARE:
        /* code */
        break;

    default:
        break;
    }
}
