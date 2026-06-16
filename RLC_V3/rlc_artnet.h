/**
 * @file rlc_artnet.h
 * @brief Header file for ArtNet over WiFi control receiver class.
 */

#ifndef RLC_ARTNET_H
#define RLC_ARTNET_H

#include <ArtnetWifi.h>
#include <WiFi.h>

#include "common.h"

#define UNIVERSE_SIZE 513            /**< Standard max DMX channels in a universe (+ 1 index alignment). */
#define LAST_DMX_ADDRESS 512         /**< Highest addressable DMX channel. */
#define FIRST_DMX_ADDRESS 1          /**< Lowest addressable DMX channel. */
#define LAST_UNIVERSE 99             /**< Limited universe ceiling (0-99). */

/**
 * @brief Enum defining WiFi connection Finite State Machine states.
 */
enum {
  MENU,             /**< Not connecting, showing menu. */
  CONNECTING,       /**< WiFi connection in progress. */
  ARTNET_CONNECTED  /**< WiFi connected, parsing ArtNet packets. */
};

/**
 * @brief Enum defining selection parameters in ArtNet menu.
 */
enum {
  UNIVERSE,         /**< Adjusting the starting universe parameter. */
  CHANNEL,          /**< Adjusting the starting DMX channel parameter. */
  IP_ADDRESS,       /**< Viewing local IP info (non-selectable parameter). */
  ARTNET_LAST       /**< Sentinel for boundaries. */
};

/**
 * @class rlc_artnet
 * @brief Manages WiFi connectivity and ArtNet-DMX packet decoding.
 */
class rlc_artnet {
 private:
  uint16_t current_universe = 0;    /**< Starting DMX universe. */
  uint16_t last_used_universe = 0;   /**< Final universe consumed by segments. */
  uint16_t channel_start = 1;        /**< Starting DMX channel within start universe. */
  uint16_t last_channel = 0;         /**< Ending DMX channel. */
  uint16_t used_channel = 4;         /**< Total channels consumed by configured segments. */
  uint16_t number_segments = 1;      /**< Number of configured LED segments. */
  uint16_t last_address = UNIVERSE_SIZE - used_channel;
  uint8_t current = UNIVERSE;        /**< Currently highlighted menu item parameter. */
  uint8_t current_fsm = MENU;        /**< Active WiFi FSM connection state. */
  volatile uint8_t number_dots = 1;  /**< Connecting loader animation dot counter. */
  uint8_t data_current_universe[UNIVERSE_SIZE] = {}; /**< Buffer containing start universe DMX data. */
  uint8_t data_next_universe[UNIVERSE_SIZE] = {};    /**< Buffer containing next universe DMX data. */

 public:
  /**
   * @brief Constructor for rlc_artnet.
   */
  rlc_artnet();

  /**
   * @brief Destructor for rlc_artnet.
   */
  ~rlc_artnet();

  /**
   * @brief Initializes ArtNet WiFi libraries and sets DMX parsing callback.
   * @param[in] fptr Callback function pointer triggered on packet reception.
   */
  void init(void (*fptr)(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data));

  /**
   * @brief Begins listening for ArtNet packets if WiFi is connected.
   */
  void begin_artnet();

  /**
   * @brief Disables ArtNet receiver and shuts down WiFi module.
   */
  void stop_artnet();

  /**
   * @brief Triggers WiFi connection to predefined SSID credentials.
   */
  void connect_wifi();

  /**
   * @brief Disconnects WiFi from active router.
   */
  void disconnect_wifi();

  /**
   * @brief Cycles selected parameters inside the ArtNet menu.
   */
  void next_selection();

  /**
   * @brief Adjusts starting universe parameter relatively.
   * @param[in] value Relative change amount.
   */
  void add_universe(int value);

  /**
   * @brief Adjusts starting channel parameter relatively.
   * @param[in] value Relative change amount.
   */
  void add_channel(int value);

  /**
   * @brief Increments loading dots count (1 to 3, then wraps to 1).
   */
  void add_dot();

  /**
   * @brief Adjusts channel start address relatively, clamping to hardware limits.
   * @param[in] value Relative change amount.
   */
  void add_channel_node(int value);

  /**
   * @brief Parses incoming TCP/UDP buffer looking for ArtNet packets.
   */
  void artnet_parse();

  /* GETTER FUNCTIONS */
  
  /** @brief Gets active WiFi connection status. @return True if connected. */
  bool get_wifi_status();
  /** @brief Gets string representation of local IP. @return IP string. */
  String get_wifi_local_ip();
  /** @brief Gets configured starting universe. @return Universe index. */
  uint16_t get_start_universe();
  /** @brief Gets final universe index consumed. @return Universe index. */
  uint16_t get_end_universe();
  /** @brief Gets configured starting channel. @return Channel address (1-512). */
  uint16_t get_start_channel();
  /** @brief Gets final channel address consumed. @return Channel address (1-512). */
  uint16_t get_end_channel();
  /** @brief Gets total channel count consumed. @return Channel count. */
  uint16_t get_used_channel();
  /** @brief Gets configured number of LED segments. @return Segment count. */
  uint16_t get_section_number();
  /** @brief Gets currently active parameter selection. @return Selected index. */
  uint8_t get_current_sel();
  /** @brief Gets active WiFi FSM state. @return State index. */
  uint8_t get_current_fsm();
  /** @brief Gets current loading dots count. @return Dot count. */
  uint8_t get_number_dots();
  /** @brief Gets pointer to current universe DMX buffer. @return Buffer pointer. */
  uint8_t* get_current_data();
  /** @brief Gets pointer to next universe DMX buffer. @return Buffer pointer. */
  uint8_t* get_next_data();

  /* SETTER FUNCTIONS */
  
  /**
   * @brief Sets segment count and updates channel usage variables.
   * @param[in] _segments Segment count.
   * @param[in] dimmer_mode Segment dimmer configuration.
   * @param[in] white_mode White channel handling mode.
   */
  void set_number_segments(uint16_t _segments, uint8_t dimmer_mode, uint8_t white_mode);

  /**
   * @brief Copies universe data into internal start buffer.
   * @param[in] data Incoming DMX data pointer.
   */
  void set_current_universe(uint8_t* data);

  /**
   * @brief Copies universe data into internal next buffer.
   * @param[in] data Incoming DMX data pointer.
   */
  void set_next_universe(uint8_t* data);

  /**
   * @brief Sets WiFi connection FSM state.
   * @param[in] val FSM state index.
   */
  void set_current_fsm(uint8_t val);

  /**
   * @brief Sets starting universe index directly.
   * @param[in] val Universe index.
   */
  void set_current_universe_nmbr(uint16_t val);

  /**
   * @brief Sets starting channel directly.
   * @param[in] channel Channel address.
   */
  void set_current_channel(uint16_t channel);

  /**
   * @brief Sets loading dot count directly.
   * @param[in] _dots Dot count.
   */
  void set_dots(uint8_t _dots);
};

#endif