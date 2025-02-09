#if !defined(MENU_STRUCTURE_H)
#define MENU_STRUCTURE_H

#include <Arduino.h>
/**
 * An enum to define the possible main modes.
 */
enum
{
    HSV_PAGE,
    RGB_PAGE,
    DMX_PAGE,
    ARTNET_REC,
    SEGMENT_CNTRL,
    MAIN_LAST
};

enum
{
    MAIN_MENU,
    SUB_MENU,
    MAX_DEEP
};

class menu_structure
{
private:
    uint8_t current = HSV_PAGE;
    uint8_t deepness = MAIN_MENU;
    uint8_t last_menu = MAIN_LAST;

public:
    menu_structure(/* args */);
    ~menu_structure();

    void init();

    /**
     * Returns the current mode.
     */
    uint8_t get_current();

    uint8_t get_deepness();

    /**
     * Sets the current mode to the given mode. If the given mode is greater than or equal to the total number of modes,
     * sets the mode to the last available mode.
     * @param _current: The mode to set the current mode to.
     */
    void set_current(uint8_t _current);

    void set_deepness(uint8_t _deepness);

    void add_current(int val);

    void deeper();
};

#endif // MENU_STRUCTURE_H
