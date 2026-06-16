/**
 * @file settings_menu.h
 * @brief Header file for settings sub-menu structure and interaction.
 */

#if !defined(SETTINGS_MENU_H)
#define SETTINGS_MENU_H

#include <Arduino.h>

/**
 * @brief Enum defining setting items in settings menu page.
 */
enum {
  SEGMENTS,          /**< Zone segmentation count setting. */
  DIMMER_OPTION,     /**< Dimmer protocol style option. */
  WHITE_OPTION,      /**< White LED channel layout option. */
  VALUE_MODE_OPTION, /**< Numeric representation mode option. */
  RESET_OPTION,      /**< Factory reset option. */
  FIRMWARE,          /**< View firmware version item. */
  LAST_SETTING       /**< Sentinel for boundaries. */
};

/**
 * @brief Enum defining selection depth within the settings menu.
 */
enum {
  ITEM_SELECTION,    /**< Highlighting which setting parameter to adjust. */
  VALUE_SELECTION    /**< Editing the value of the highlighted setting. */
};

/**
 * @class settings_menu
 * @brief Manages navigation and adjustment level within the system configuration screen.
 */
class settings_menu {
 private:
  uint8_t current_menu_item = SEGMENTS;       /**< Currently selected setting parameter. */
  uint8_t current_deepness = ITEM_SELECTION;   /**< Selection depth (highlighting vs editing). */
  uint8_t reset_confirm = 0;                  /**< Factory reset safety confirmation state (0 = NO, 1 = YES). */

 public:
  /**
   * @brief Constructor for settings_menu.
   */
  settings_menu();

  /**
   * @brief Destructor for settings_menu.
   */
  ~settings_menu();

  /**
   * @brief Relatively adjusts the highlighted setting parameter index.
   * @param[in] value Relative change amount.
   */
  void add_setting(int value);

  /**
   * @brief Toggles between item selection and value adjustment.
   */
  void deeper();

  /**
   * @brief Gets current selection depth.
   * @return Current depth.
   */
  uint8_t get_deepness();

  /**
   * @brief Gets currently selected setting parameter index.
   * @return Selected index.
   */
  uint8_t get_item();

  /**
   * @brief Gets the factory reset confirmation state.
   * @return Confirmation state (0 = NO, 1 = YES).
   */
  uint8_t get_reset_confirm();

  /**
   * @brief Toggles or modifies the reset confirmation state.
   * @param[in] value Relative change index.
   */
  void add_reset_confirm(int value);

  /**
   * @brief Resets the factory reset confirmation state back to NO.
   */
  void clear_reset_confirm();
};

#endif  // SETTINGS_MENU_H
