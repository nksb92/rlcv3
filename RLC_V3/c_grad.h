/**
 * @file c_grad.h
 * @brief Header file for the gradient color control class.
 */

#if !defined(C_GRAD_H)
#define C_GRAD_H

#include <Arduino.h>

/**
 * @brief Enum defining menu items for Gradient mode.
 */
enum {
  GRAD_START_HUE, /**< Start color hue setting. */
  GRAD_START_SAT, /**< Start color saturation setting. */
  GRAD_START_VAL, /**< Start color value/brightness setting. */
  GRAD_END_HUE,   /**< End color hue setting. */
  GRAD_END_SAT,   /**< End color saturation setting. */
  GRAD_END_VAL,   /**< End color value/brightness setting. */
  GRAD_DIMMER,    /**< Overall dimmer setting. */
  GRAD_LAST       /**< Sentinel for boundaries. */
};

/**
 * @brief Enum defining deepness/selection level in Gradient menu.
 */
enum {
  GRAD_ITEM_SELECTION,  /**< Selecting which gradient parameter to change. */
  GRAD_VALUE_SELECTION /**< Adjusting the value of the selected parameter. */
};

/**
 * @class C_GRAD
 * @brief Manages linear gradients between two HSV colors.
 */
class C_GRAD {
  uint8_t start_hue; /**< Hue value of the start color (0-255). */
  uint8_t start_sat; /**< Saturation value of the start color (0-MAX). */
  uint8_t start_val; /**< Value/brightness of the start color (0-MAX). */
  uint8_t end_hue;   /**< Hue value of the end color (0-255). */
  uint8_t end_sat;   /**< Saturation value of the end color (0-MAX). */
  uint8_t end_val;   /**< Value/brightness of the end color (0-MAX). */
  uint8_t dimmer;    /**< Overall dimmer scale factor. */

  uint8_t current_menu_item = GRAD_START_HUE; /**< Currently highlighted menu item. */
  uint8_t current_deepness = GRAD_ITEM_SELECTION; /**< Current menu navigation depth. */

 public:
  /**
   * @brief Constructor for C_GRAD.
   * @param[in] _sh Start hue (0-255).
   * @param[in] _ss Start saturation (0-255).
   * @param[in] _sv Start value (0-255).
   * @param[in] _eh End hue (0-255).
   * @param[in] _es End saturation (0-255).
   * @param[in] _ev End value (0-255).
   */
  C_GRAD(uint8_t _sh, uint8_t _ss, uint8_t _sv, uint8_t _eh, uint8_t _es, uint8_t _ev);
  
  /**
   * @brief Destructor for C_GRAD.
   */
  ~C_GRAD();

  /**
   * @brief Navigates the highlight index of the menu items.
   * @param[in] value Relative change direction (+1 or -1).
   */
  void add_setting(int value);

  /**
   * @brief Toggles between item selection and value selection.
   */
  void deeper();

  /**
   * @brief Gets current menu navigation depth.
   * @return Navigation depth (GRAD_ITEM_SELECTION or GRAD_VALUE_SELECTION).
   */
  uint8_t get_deepness();

  /**
   * @brief Gets currently selected menu item index.
   * @return Active item index.
   */
  uint8_t get_item();

  /**
   * @brief Adds a relative amount to the currently active setting's value.
   * @param[in] amount The adjustment amount.
   */
  void add_value(int amount);

  /** @brief Gets start hue value. @return Hue (0-255). */
  uint8_t get_start_hue();
  /** @brief Gets start saturation value. @return Saturation (0-MAX). */
  uint8_t get_start_sat();
  /** @brief Gets start value/brightness. @return Value (0-MAX). */
  uint8_t get_start_val();
  /** @brief Gets end hue value. @return Hue (0-255). */
  uint8_t get_end_hue();
  /** @brief Gets end saturation value. @return Saturation (0-MAX). */
  uint8_t get_end_sat();
  /** @brief Gets end value/brightness. @return Value (0-MAX). */
  uint8_t get_end_val();

  /** @brief Sets start hue value. @param[in] value New hue. */
  void set_start_hue(uint8_t value);
  /** @brief Sets start saturation value. @param[in] value New saturation. */
  void set_start_sat(uint8_t value);
  /** @brief Sets start value/brightness. @param[in] value New value. */
  void set_start_val(uint8_t value);
  /** @brief Sets end hue value. @param[in] value New hue. */
  void set_end_hue(uint8_t value);
  /** @brief Sets end saturation value. @param[in] value New saturation. */
  void set_end_sat(uint8_t value);
  /** @brief Sets end value/brightness. @param[in] value New value. */
  void set_end_val(uint8_t value);

  /** @brief Gets overall gradient dimmer. @return Dimmer value (0-MAX). */
  uint8_t get_dimmer();
  /** @brief Sets overall gradient dimmer. @param[in] value New dimmer value. */
  void set_dimmer(uint8_t value);
};

#endif  // C_GRAD_H
