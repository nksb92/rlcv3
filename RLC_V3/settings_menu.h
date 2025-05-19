#if !defined(SETTINGS_MENU_H)
#define SETTINGS_MENU_H

#include <Arduino.h>
// #include "common.h"

enum
{
    SEGMENTS,
    FIRMWARE,
    LAST_SETTING
};

enum
{
    ITEM_SELECTION,
    VALUE_SELECTION
};

class settings_menu
{
private:
    /* data */
    uint8_t current_menu_item = SEGMENTS;
    uint8_t current_menu_ITEM_SELECTIONelection = ITEM_SELECTION;

public:
    settings_menu(/* args */);
    ~settings_menu();

    void add_setting(int value);

    void handle_submenu();
};

#endif // SETTINGS_MENU_H
