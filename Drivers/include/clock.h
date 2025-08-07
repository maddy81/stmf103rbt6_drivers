/******************************************************************************
* FILENAME : clock.h
* DESCRIPTION : Header file of clock.c conatains clock function prototypes, macros
                enums
* AUTHOR : Hammad
******************************************************************************/

#ifndef _CLOCK_H_
#define _CLOCK_H_

/********** Includes *********************************************************/

#include "std_types.h"

/********** Macros ***********************************************************/

#define RCC_BASE_ADDRESS        (0X40021000U)
#define RCC_APB2ENR_ENABLER     (*(volatile uint32 *)(RCC_BASE_ADDRESS  +  0x18U))
#define RCC_APB1ENR_ENABLER     (*(volatile uint32 *)(RCC_BASE_ADDRESS  +  0x1CU))
#define RCC_CR                  (*(volatile uint32 *)(RCC_BASE_ADDRESS  +  0x00U))
#define RCC_CFGR                (*(volatile uint32 *)(RCC_BASE_ADDRESS  +  0x04U))
#define RCC_CFGR2               (*(volatile uint32 *)(RCC_BASE_ADDRESS  +  0x2CU))
#define APB2_END                (0X10U)
#define HIGH                    (0x1U)
#define LOW                     (0x0U)

/********** ENUMS ************************************************************/

typedef enum
{
    AFIO = 0,
    RESERVED_1,
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    RESERVED_SEVEN,
    RESERVED_EIGHT,
    ADC1,
    ADC2,
    TIM1_EN,
    SPI1_EN,
    RESERVED_THIRTEEN,
    USART1_EN,
    RESERVED_15,
    TIM2_EN,
    TIM3_EN,
    TIM4_EN,
    TIM5_EN,
    TIM6_EN,
    TIM7_EN,
    RESERVED_6,
    RESERVED_7,
    RESERVED_8,
    RESERVED_9,
    RESERVED_10,
    WWD_GEN,
    RESERVED_12,
    RESERVED_13,
    SPI_2_EN,
    SPI_3_EN,
    RESERVED_16,
    USART2_EN,
    USART3_EN,
    UART4_EN,
    UART5_EN,
    I2C1_EN,
    I2C2_EN,
    RESERVED_23,
    RESERVED_24,
    CAN1_EN,
    CAN2_EN,
    BKP_EN,
    PWR_EN,
    DAC_EN
} peripheral_clock_type;

/********** External APIs ****************************************************/

extern void Rcc_Enabler(peripheral_clock_type peripherals);

#endif  /* End of _CLOCK_H_ */
