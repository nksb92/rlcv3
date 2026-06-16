/**
 * @file display_manager.h
 * @brief Header file for display state and navigation manager.
 */

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "display.h"

/**
 * @brief Renders the main menu if the navigation depth is in MAIN_MENU.
 */
void display_show_menu();

/**
 * @brief Renders the active sub-menu page based on current settings and mode.
 */
void display_show_submenu();

/**
 * @brief Puts the OLED display into standby (blanked screen) to conserve power.
 */
void display_enter_standby();

/**
 * @brief Wakes up the OLED display from standby and restores the last active screen content.
 */
void display_leave_standby();

/**
 * @brief Gets whether the display is currently in standby mode.
 * @return True if in standby, false otherwise.
 */
bool get_standby_status();

/**
 * @brief Displays the temporary "Saved" verification screen.
 */
void display_enter_saved_screen();

/**
 * @brief Exits the "Saved" screen and restores the active menu screen.
 */
void display_leave_saved_screen();

/**
 * @brief Gets whether the display is currently showing the "Saved" screen.
 * @return True if showing saved screen, false otherwise.
 */
bool get_saved_screen_state();

#endif  // DISPLAY_MANAGER_H
