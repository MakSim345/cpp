#pragma once

#include "gen.h"

/** @defgroup GPIO_pins GPIO pins
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;

/**
  * @brief General Purpose I/O
  */
typedef struct
{
  uint32_t MODER;       /*!< GPIO port mode register,               Address offset: 0x00      */
  uint32_t OTYPER;      /*!< GPIO port output type register,        Address offset: 0x04      */
  uint32_t OSPEEDR;     /*!< GPIO port output speed register,       Address offset: 0x08      */
  uint32_t PUPDR;       /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  uint32_t IDR;         /*!< GPIO port input data register,         Address offset: 0x10      */
  uint32_t ODR;         /*!< GPIO port output data register,        Address offset: 0x14      */
  uint32_t BSRR;        /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
  uint32_t LCKR;        /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  uint32_t AFR[2];      /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
  uint32_t BRR;         /*!< GPIO Bit Reset register,               Address offset: 0x28      */
} GPIO_TypeDef;


void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);