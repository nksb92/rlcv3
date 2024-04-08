#include "common.h"

class fan_control
{
private:
    uint8_t current_speed = MIN_SPEED;

public:
    fan_control();
    ~fan_control();
    void init_fan();
    void set_speed(uint8_t _speed);
};


