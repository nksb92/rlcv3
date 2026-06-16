/**
 * @file menu_structure.h
 * @brief Header file for main menu hierarchy and state management.
 */

#if !defined(MENU_STRUCTURE_H)
#define MENU_STRUCTURE_H

#include <Arduino.h>
#include "config.h"

/**
 * @brief Enum defining all page types in the system menu.
 */
enum {
  HSV_PAGE,        /**< Hue-Saturation-Value page. */
  RGB_PAGE,        /**< Red-Green-Blue page. */
  CCT_PAGE,        /**< Correlated Color Temperature page. */
  DMX_PAGE,        /**< DMX receiver config page. */
  ARTNET_PAGE,     /**< ArtNet receiver status/config page. */
#if NUM_PIXEL > 1
  GRAD_PAGE,       /**< Gradient generation page. */
#endif
  SETTINGS_PAGE,   /**< System configuration settings page. */
  MENU_LAST_PAGE   /**< Sentinel for boundaries. */
};

/**
 * @brief Enum defining navigation depth levels.
 */
enum {
  MAIN_MENU,       /**< High-level page swipe navigation. */
  SUB_MENU,        /**< Parameter/item selection within a page. */
  MAX_DEEP         /**< Sentinel for navigation depth. */
};

/**
 * @class menu_structure
 * @brief Handles main display page transitions and selection depth tracking.
 */
class menu_structure {
 private:
  uint8_t current = HSV_PAGE;      /**< Current active page type. */
  uint8_t deepness = MAIN_MENU;    /**< Current menu navigation depth. */
  uint8_t last_menu = MENU_LAST_PAGE; /**< Total number of pages. */

 public:
  /**
   * @brief Constructor for menu_structure.
   */
  menu_structure();
  
  /**
   * @brief Destructor for menu_structure.
   */
  ~menu_structure();

  /**
   * @brief Initializes menu properties.
   */
  void init();

  /**
   * @brief Gets current active page.
   * @return Active page type.
   */
  uint8_t get_current();

  /**
   * @brief Gets current menu navigation depth.
   * @return Menu depth.
   */
  uint8_t get_deepness();

  /**
   * @brief Sets the active page directly, clamping if out of range.
   * @param[in] _current The page index to set.
   */
  void set_current(uint8_t _current);

  /**
   * @brief Sets the menu navigation depth directly, clamping if out of range.
   * @param[in] _deepness The depth to set.
   */
  void set_deepness(uint8_t _deepness);

  /**
   * @brief Adjusts current page index relatively, preventing roll-past.
   * @param[in] val Relative change direction (+1 or -1).
   */
  void add_current(int val);

  /**
   * @brief Cycles the menu depth to the next level (or wraps back to MAIN_MENU).
   */
  void deeper();
};

#endif  // MENU_STRUCTURE_H
