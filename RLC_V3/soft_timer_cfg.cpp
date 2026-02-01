#include "soft_timer_cfg.h"

// Timer Configuration Table
const soft_timer_cfg_t soft_timer_config[] = {
    // ID                      Name               DefPeriod                 Mode                  Event                     AutoStart
    { TIMER_DISPLAY_STANDBY,  "DisplayStandby",  STD_STANDBY_TIME * 100,    TIMER_MODE_ONE_SHOT,  EVT_DISPLAY_STANDBY,      true  },
    { TIMER_FAN_COOLDOWN,     "FanCooldown",     STD_FAN_RUN_ON_TIME * 100, TIMER_MODE_ONE_SHOT,  EVT_FAN_COOLDOWN,         false },
    { TIMER_SCROLL_TEXT,      "ScrollText",      110,                       TIMER_MODE_PERIODIC,  EVT_SCROLL_TICK,          false },
    { TIMER_CONNECTING_DOTS,  "ConnectingDots",  500,                       TIMER_MODE_PERIODIC,  EVT_CONNECTING_DOTS_TICK, false },
    { TIMER_RAINBOW_ANIM,     "RainbowAnim",     100,                       TIMER_MODE_PERIODIC,  EVT_RAINBOW_TICK,         false },
    { TIMER_UPDATE_FAN,       "UpdateFanSpeed",  150,                       TIMER_MODE_PERIODIC,  EVT_UPDATE_FAN,           false },
};

const uint8_t soft_timer_config_count = sizeof(soft_timer_config) / sizeof(soft_timer_config[0]);
