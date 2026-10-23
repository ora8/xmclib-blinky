#pragma once

#include "gpio.hpp"

class led 
{
public:
    led(uint8_t port_nr, uint8_t pin_nr) : _gpio{port_nr, pin_nr, OUTPUT}
    {
    }
    void begin()
    {
        _gpio.begin();
    }
    void on()
    {
        _gpio.set_high();
    }
    void off()
    {
        _gpio.set_low();
    }
    void toggle()
    {
        _gpio.toggle();
    }
private:
    gpio _gpio;
};
