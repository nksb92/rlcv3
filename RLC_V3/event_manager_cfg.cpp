#include "event_manager_cfg.h"

// Event Configuration Table
const event_cfg_t event_config[] = {
    // ID                       Name                  Priority              Queueable
    {EVT_NONE, "None", EVT_PRIORITY_LOW, false},

    // Input events - high priority, user interaction must feel responsive
    {EVT_ENCODER_CHANGED, "EncoderChanged", EVT_PRIORITY_HIGH, true},
    {EVT_BUTTON_CLICK, "ButtonClick", EVT_PRIORITY_HIGH, false},
    {EVT_BUTTON_LONG_PRESS, "ButtonLongPress", EVT_PRIORITY_HIGH, false},
    {EVT_BUTTON_DOUBLE_PRESS, "ButtonDoublePress", EVT_PRIORITY_HIGH, false},

    // Timer events
    {EVT_DISPLAY_STANDBY, "DisplayStandby", EVT_PRIORITY_LOW, false},
    {EVT_FAN_COOLDOWN, "FanCooldown", EVT_PRIORITY_LOW, false},
    {EVT_SCROLL_TICK, "ScrollTick", EVT_PRIORITY_LOW, false},
    {EVT_CONNECTING_DOTS_TICK, "ConnectingDots", EVT_PRIORITY_LOW, false},
    {EVT_RAINBOW_TICK, "RainbowTick", EVT_PRIORITY_LOW, false},
    {EVT_UPDATE_FAN, "UpdateFan", EVT_PRIORITY_LOW, false},

    // System events
    {EVT_SAVE_TO_NVM, "SaveToNvm", EVT_PRIORITY_NORMAL, false},
    {EVT_DISPLAY_WAKE, "WakeUpDisplay", EVT_PRIORITY_NORMAL, false},
    {EVT_LEAVE_SAVED_SCREEN, "ShowSaved", EVT_PRIORITY_HIGH, false},
    {EVT_WIFI_CONNECTED, "WifiConnected", EVT_PRIORITY_NORMAL, false},
    {EVT_WIFI_DISCONNECTED, "WifiDisconnected", EVT_PRIORITY_NORMAL, false},
};

const uint8_t event_config_count = sizeof(event_config) / sizeof(event_config[0]);
