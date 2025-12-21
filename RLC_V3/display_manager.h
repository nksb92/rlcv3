#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "display.h"

// Display update functions
void display_show_menu();
void display_show_submenu();

// Standby control
void display_enter_standby();
void display_leave_standby();
bool get_standby_status();

// saved screen control
void display_enter_saved_screen();
void display_leave_saved_screen();
bool get_saved_screen_state();

#endif  // DISPLAY_MANAGER_H
