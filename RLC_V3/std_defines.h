#if !defined(STD_DEFINES_H)
#define STD_DEFINES_H

#if defined(PERCENTAGE)
#define STD_SAT 100
#define STD_VAL 100
#endif

#if defined(FULL_RANGE)
#define STD_SAT 255
#define STD_VAL 255
#endif

#define STD_HUE 0

#define STD_RED 128
#define STD_GREEN 0
#define STD_BLUE 128

#define STD_CURRENT 0
#define STD_DEEPNESS 0
#define STD_SEGMENTS 1

#define STD_START_ADDRESS 1
#define STD_UNIVERSE 0

#define STD_FAN_RUN_ON_TIME 200
#define STD_STANDBY_TIME 300
#define STD_FAN_UPDATE_TIME 100

#define FAN_CHANNEL 4
#define PWM_RESOLUTION 8
#define PWM_FAN_FREQ 25000

#define SLAVE_ADR_STRT 0x08

#define DATA_OUT D8

#endif  // STD_DEFINES_H