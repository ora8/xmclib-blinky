#include "gpio.hpp"

XMC_GPIO_MODE gpio::get_xmc_mode(const gpio_mode mode) {
  switch (mode) {
  case INPUT_PULLUP:
    return XMC_GPIO_MODE_INPUT_PULL_DOWN;
  case INPUT_PULLDOWN:
    return XMC_GPIO_MODE_INPUT_PULL_DOWN;
  case OUTPUT:
    return XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  case OUTPUT_OPENDRAIN:
    return XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN;
  default:
    return XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN;
  }
}

/**
  \brie/f  Gibt einen Zeiger auf das XMC_GPIO_PORT-Register für den angegebenen
  Port-Index zurück.
  \param  port: Port-Index (0 = PORT0, 1 = PORT1, 2 = PORT2, ...).
  \return Zeiger auf das XMC_GPIO_PORT-Register oder nullptr, falls der
  Port-Index ungültig ist.
*/
XMC_GPIO_PORT *gpio::get_xmc_port(const uint8_t port) {

  // Port adresses, see datahseet
  static constexpr uintptr_t XMC_GPIO_PORTS[] = {
      0x48028000UL, // PORT0
      0x48028100UL, // PORT1
      0x48028200UL, // PORT2
      0x48028300UL, // PORT3
      0x48028400UL, // PORT4
      0x48028500UL, // PORT5
      0x48028600UL, // PORT6
      0x48028700UL  // PORT7
  };

  // Check if valid index
  if (port < (sizeof(XMC_GPIO_PORTS) / sizeof(XMC_GPIO_PORTS[0]))) {
    return reinterpret_cast<XMC_GPIO_PORT *>(XMC_GPIO_PORTS[port]);
  } else {
    return nullptr; // Invalid index
  }
}

static constexpr uint32_t get_iocr_pc_mask(const uint8_t pin) {
  uint32_t pos{};
  if (pin < 4) {
    pos = 0;
  } else if (pin < 8) {
    pos = 8;
  } else if (pin < 12) {
    pos = 16;
  } else if (pin < 24) {
    pos = 24;
  }
  return 0x1FUL << pos;
}

// static constexpr uint32_t get_iocr_mode(const gpio_mode mode) {
//   switch (mode) {
//   case INPUT_PULLUP:
//     return XMC_GPIO_MODE_INPUT_PULL_UP;
//   case INPUT_PULLDOWN:
//     return XMC_GPIO_MODE_INPUT_PULL_DOWN;
//   case OUTPUT:
//     return XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
//   case OUTPUT_OPENDRAIN:
//     return XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN;
//   }
//   return 0;
// }

void gpio::begin() 
{
  set_mode();
}

void gpio::set_high() {
  auto level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
  _xmc_port->OMR = (uint32_t)level << _pin;
}

void gpio::set_low() {
  auto level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  _xmc_port->OMR = (uint32_t)level << _pin;
}

void gpio::set_mode() {
  _xmc_port->IOCR[(uint32_t)_pin >> 2U] &=
      ~(uint32_t)((uint32_t)PORT_IOCR_PC_Msk
                  << ((uint32_t)PORT_IOCR_PC_Size * ((uint32_t)_pin & 0x3U)));
  _xmc_port->IOCR[(uint32_t)_pin >> 2U] |= (uint32_t)_xmc_mode
                                           << ((uint32_t)PORT_IOCR_PC_Size *
                                               ((uint32_t)_pin & 0x3U));
}

void gpio::toggle() { _xmc_port->OMR = 0x10001U << _pin; }
