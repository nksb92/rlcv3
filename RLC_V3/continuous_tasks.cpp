#include "continuous_tasks.h"

#include "common.h"
#include "dmx.h"
#include "event_manager.h"
#include "leds.h"
#include "std_defines.h"

#ifdef FAN_USAGE
#include "fan_control.h"
#endif

extern rgb_dmx dmx_val;
extern menu_structure main_sw;
extern rlc_artnet artnet_var;
extern segments seg;
extern bool artnet_data;

#ifdef FAN_USAGE
extern fan_control fan;
#endif

void handle_continuous_tasks() {
  uint8_t current_deepness = main_sw.get_deepness();
  uint8_t main_state = main_sw.get_current();

  if (current_deepness != SUB_MENU) {
    return;
  }

  switch (main_state) {
    case DMX_PAGE:
      dmx_val.handle_dmx();
      if (dmx_val.get_rec_status()) {
        uint16_t last_rgb_sum = set_pixel(
            dmx_val.get_start(),
            dmx_val.get_dimmer_address(),
            seg.get_num_seg(),
            dmx_val.get_universe());
#ifdef FAN_USAGE
        fan.evaluate_sum(last_rgb_sum);
#endif
        dmx_val.set_rec_status(false);
      }
      break;

    case ARTNET_PAGE:
      switch (artnet_var.get_current_fsm()) {
        case CONNECTING:
          if (artnet_var.get_wifi_status()) {
            event_manager.post(EVT_WIFI_CONNECTED);
          }
          break;

        case ARTNET_CONNECTED:
          if (!artnet_var.get_wifi_status()) {
            event_manager.post(EVT_WIFI_DISCONNECTED);
            break;
          }

          artnet_var.artnet_parse();
          if (artnet_data) {
            uint16_t last_rgb_sum = output_artnet(artnet_var);
#ifdef FAN_USAGE
            fan.evaluate_sum(last_rgb_sum);
#endif
            artnet_data = false;
          }
          break;

        default:
          break;
      }
      break;

    default:
      break;
  }
}
