#pragma once

#include "generic.h"

//
// Copyright see Infineon
//
struct XMC_GPIO_PORT
{
  __IO uint32_t  OUT;			/**< The port output register determines the value of a GPIO pin when it is selected by
  	  	  	  	  	  	  	  	  	  	  Pn_IOCRx as output */
  __O  uint32_t  OMR;			/**< The port output modification register contains control bits that make it possible
  	  	  	  	  	  	  	  	  	 to individually set, reset, or toggle the logic state of a single port line*/
  __I  uint32_t  RESERVED0[2];
  __IO uint32_t  IOCR[4];		/**< The port input/output control registers select the digital output and input driver
											functionality and characteristics of a GPIO port pin */
  __I  uint32_t  RESERVED1;
  __I  uint32_t  IN;			/**< The logic level of a GPIO pin can be read via the read-only port input register
  	  	  	  	  	  	  	  	  	  Pn_IN */
  __I  uint32_t  RESERVED2[6];
  __IO uint32_t  PDR[2];		/**< Pad Driver Mode Registers */

  __I  uint32_t  RESERVED3[6];
  __IO uint32_t  PDISC;			/**< Pin Function Decision Control Register is to disable/enable the digital pad
  	  	  	  	  	  	  	  	  	 structure in shared analog and digital ports*/
  __I  uint32_t  RESERVED4[3];
  __IO uint32_t  PPS;			/**< Pin Power Save Register */
  __IO uint32_t  HWSEL;			/**< Pin Hardware Select Register */
};

#define PORT0_IOCR0_PC0_Pos (3UL) /*!< PORT0 IOCR0: PC0 (Bit 3)                                    */


enum XMC_GPIO_MODE : uint32_t
{
  XMC_GPIO_MODE_INPUT_TRISTATE = 0x0UL << PORT0_IOCR0_PC0_Pos, 	         /**< No internal pull device active */
  XMC_GPIO_MODE_INPUT_PULL_DOWN = 0x1UL << PORT0_IOCR0_PC0_Pos, 	     /**< Internal pull-down device active */
  XMC_GPIO_MODE_INPUT_PULL_UP = 0x2UL << PORT0_IOCR0_PC0_Pos, 	         /**< Internal pull-up device active */
  XMC_GPIO_MODE_INPUT_SAMPLING = 0x3UL << PORT0_IOCR0_PC0_Pos, 	         /**< No internal pull device active;Pn_OUTx continuously samples the input value */
  XMC_GPIO_MODE_INPUT_INVERTED_TRISTATE = 0x4UL << PORT0_IOCR0_PC0_Pos,  /**< Inverted no internal pull device active */
  XMC_GPIO_MODE_INPUT_INVERTED_PULL_DOWN = 0x5UL << PORT0_IOCR0_PC0_Pos, /**< Inverted internal pull-down device active */
  XMC_GPIO_MODE_INPUT_INVERTED_PULL_UP = 0x6UL << PORT0_IOCR0_PC0_Pos,   /**< Inverted internal pull-up device active */
  XMC_GPIO_MODE_INPUT_INVERTED_SAMPLING = 0x7UL << PORT0_IOCR0_PC0_Pos,  /**< Inverted no internal pull device active; Pn_OUTx continuously samples the input value */
  XMC_GPIO_MODE_OUTPUT_PUSH_PULL = 0x80UL, 			                     /**< Push-pull general-purpose output */
  XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN = 0xc0UL, 		                     /**< Open-drain general-purpose output */
  XMC_GPIO_MODE_OUTPUT_ALT1 = 0x1UL << PORT0_IOCR0_PC0_Pos,
  XMC_GPIO_MODE_OUTPUT_ALT2 = 0x2UL << PORT0_IOCR0_PC0_Pos,
  XMC_GPIO_MODE_OUTPUT_ALT3 = 0x3UL << PORT0_IOCR0_PC0_Pos,
  XMC_GPIO_MODE_OUTPUT_ALT4 = 0x4UL << PORT0_IOCR0_PC0_Pos,
  XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1 = XMC_GPIO_MODE_OUTPUT_PUSH_PULL | XMC_GPIO_MODE_OUTPUT_ALT1, 	/**<  Push-pull alternate output function 1 */
  XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2 = XMC_GPIO_MODE_OUTPUT_PUSH_PULL | XMC_GPIO_MODE_OUTPUT_ALT2, 	/**<  Push-pull alternate output function 2 */
  XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3 = XMC_GPIO_MODE_OUTPUT_PUSH_PULL | XMC_GPIO_MODE_OUTPUT_ALT3, 	/**<  Push-pull alternate output function 3 */
  XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4 = XMC_GPIO_MODE_OUTPUT_PUSH_PULL | XMC_GPIO_MODE_OUTPUT_ALT4, 	/**<  Push-pull alternate output function 4 */
  XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT1 = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN | XMC_GPIO_MODE_OUTPUT_ALT1, 	/**<  Open drain alternate output function 1 */
  XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2 = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN | XMC_GPIO_MODE_OUTPUT_ALT2, 	/**<  Open drain alternate output function 2 */
  XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT3 = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN | XMC_GPIO_MODE_OUTPUT_ALT3, 	/**<  Open drain alternate output function 3 */
  XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT4 = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN | XMC_GPIO_MODE_OUTPUT_ALT4, 	/**<  Open drain alternate output function 4 */
};

/**
 * Defines output level of a pin. Use type \a XMC_GPIO_OUTPUT_LEVEL_t for this enum.
 */
typedef enum XMC_GPIO_OUTPUT_LEVEL
{
  XMC_GPIO_OUTPUT_LEVEL_LOW  = 0x10000U, /**<  Reset bit */
  XMC_GPIO_OUTPUT_LEVEL_HIGH = 0x1U, 	/**< Set bit  */
} XMC_GPIO_OUTPUT_LEVEL_t;
