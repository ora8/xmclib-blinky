#pragma once

#include <stdint.h>

#include "infineon/xmc4700_struct.h"

enum gpio_mode : uint8_t
{
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    OUTPUT,
    OUTPUT_OPENDRAIN
};

enum gpio_level : uint8_t
{
    LOW,
    HIGH
};

class gpio
{
public:
    gpio(uint8_t port, uint8_t pin, gpio_mode mode) :
        gpio{port, pin, mode, LOW}
    {
    }
    gpio(uint8_t port, uint8_t pin, gpio_mode mode, gpio_level level) :
        _port{port},  _pin{pin}, _mode{mode}, _level{level}
    {
        _xmc_mode = get_xmc_mode(mode);
        _xmc_port = get_xmc_port(port);
    }
    uint8_t get_port() const
    {
        return _port;
    }    
    uint8_t get_pin() const
    {
        return _pin;
    }
    gpio_mode get_mode() const
    {
        return _mode;
    }
    gpio_level get_lev() const
    {
        return _level;
    }
    void begin();
    void set_high();
    void set_low();
    void toggle();
private:
    static constexpr uint32_t PORT_IOCR_PC_Msk{0xf8UL};
    static constexpr uint32_t PORT_IOCR_PC_Size{8U};
    uint8_t _port;
    uint8_t _pin;
    gpio_mode _mode;
    gpio_level _level;
    XMC_GPIO_PORT *_xmc_port;
    XMC_GPIO_MODE _xmc_mode;
    XMC_GPIO_MODE get_xmc_mode(const gpio_mode mode);
    XMC_GPIO_PORT * get_xmc_port(const uint8_t port);
    void set_mode();
};

extern gpio gpio_1_0;
extern gpio gpio_2_0;
