/**
 * @file segments.h
 * @brief Header file for LED segment layout and configuration options.
 */

#ifndef SEGMENTS_H
#define SEGMENTS_H

#include "common.h"

/**
 * @enum DimmerMode
 * @brief Segment dimmer protocol styles.
 */
enum DimmerMode {
  DIMMER_RGB,    /**< Dimmer channel precedes RGB channels. */
  RGB_DIMMER,    /**< Dimmer channel follows RGB channels. */
  RGB_ONLY       /**< No dedicated dimmer channel. */
};

/**
 * @enum WhiteMode
 * @brief Segment white channel options.
 */
enum WhiteMode {
  WHITE_DISABLE, /**< No white channels. */
  WHITE_ONE_CH,  /**< Single white channel (e.g. RGBW). */
  WHITE_TWO_CH   /**< Two white channels (e.g. RGBCCT - WW/CW). */
};

/**
 * @enum ValueMode
 * @brief UI parameter resolution modes.
 */
enum ValueMode {
  VALUE_PERCENTAGE,  /**< Values shown as 0-100 percentage. */
  VALUE_FULL_RANGE   /**< Values shown as full 0-255 range. */
};

/**
 * @class segments
 * @brief Manages the zoning, dimmer settings, and parameter bounds of the LED system.
 */
class segments {
 private:
  uint16_t number_segments = 0;           /**< Active number of physical zones. */
  uint8_t current_segment = 0;            /**< Index of current selection in possible segments list. */
  uint16_t last_segment = 0;              /**< Total count of valid subdivisions. */
  uint16_t possible_segments[NUM_PIXEL];  /**< Array holding factor-based divisions of total pixels. */

  uint8_t dimmer_mode = RGB_DIMMER;       /**< Active dimmer channel mode index. */
  uint8_t white_mode = WHITE_DISABLE;     /**< Active white channel handling mode index. */
  uint8_t value_mode = VALUE_PERCENTAGE;  /**< Active UI resolution mode. */

  /**
   * @brief Computes factors of NUM_PIXEL to identify valid segment partitions.
   */
  void calc_segments();

 public:
  /**
   * @brief Constructor for segments.
   */
  segments();

  /**
   * @brief Discovers valid pixel groupings and sets defaults.
   */
  void init_segments();

  /**
   * @brief Gets current active segment count.
   * @return Active segment count.
   */
  uint16_t get_num_seg();

  /**
   * @brief Gets current highlighted index in segments options.
   * @return Selected option index.
   */
  uint8_t get_current_seg();

  /**
   * @brief Directly highlights index in segments options, clamping if needed.
   * @param[in] _current The index to set.
   */
  void set_current_segment(uint8_t _current);

  /**
   * @brief Applies chosen segment count based on selection index.
   * @param[in] pos Index of chosen divider in options array.
   */
  void set_segments(uint8_t pos);

  /**
   * @brief Adjusts the active segment subdivision level relatively.
   * @param[in] value Relative change amount.
   */
  void add_seg(int value);

  /**
   * @brief Gets current dimmer protocol style.
   * @return The active DimmerMode.
   */
  uint8_t get_dimmer_mode();

  /**
   * @brief Sets dimmer protocol style directly.
   * @param[in] mode The dimmer mode index.
   */
  void set_dimmer_mode(uint8_t mode);

  /**
   * @brief Relatively adjusts the dimmer protocol selection.
   * @param[in] value Relative change direction (+1 or -1).
   */
  void add_dimmer_mode(int value);

  /**
   * @brief Gets current white channel handling mode.
   * @return The active WhiteMode.
   */
  uint8_t get_white_mode();

  /**
   * @brief Sets white channel handling mode directly.
   * @param[in] mode The white mode index.
   */
  void set_white_mode(uint8_t mode);

  /**
   * @brief Relatively adjusts the white channel handling mode.
   * @param[in] value Relative change direction (+1 or -1).
   */
  void add_white_mode(int value);

  /**
   * @brief Gets current UI numeric resolution mode.
   * @return The active ValueMode.
   */
  uint8_t get_value_mode();

  /**
   * @brief Sets UI numeric resolution mode directly.
   * @param[in] mode The value mode index.
   */
  void set_value_mode(uint8_t mode);

  /**
   * @brief Relatively adjusts the UI numeric resolution mode.
   * @param[in] value Relative change direction (+1 or -1).
   */
  void add_value_mode(int value);
};

#endif