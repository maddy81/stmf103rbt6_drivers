/******************************************************************************
* FILENAME :timer.h
* DESCRIPTION : Header file of timer.c conatains clock function prototypes, macros
                enums
* AUTHOR : Hammad
******************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

/********** includes *****************/

#include "gpio.h"
#include "nvic.h"
#include "clock.h"
#include "std_types.h"

/********** Macros *************************************************************/

#define RCC_CR            (*(volatile uint32 *)(RCC_BASE_ADDRESS  +  0x00U))
#define RCC_CFGR          (*(volatile uint32 *)(RCC_BASE_ADDRESS  +  0x04U))
#define PLL_MUL_4         (2U << 18U)
#define PLL_MUL_8         (6U << 18U)
#define PLLON             (1U << 24U)   
#define PLL_RDY           (1U << 25U)
#define SYS_CLOCK_SWITCH  (2U << 0U)  
#define SYS_CLOCK_STATUS  (2U << 2U)

/********** ENUMS *******************************************************/

typedef enum
{
	TIM_1 = 0,
	TIM_2,
	TIM_3,
	TIM_4,
	TIM_5
} timer_type;

typedef enum
{
    FREQ_8 = 8000U,
    FREQ_16 = 16000U,
    FREQ_32 = 32000U
} clock_freq_type;

/********** STRUCTURES *******************************************************/

typedef struct timer_tag
{
    volatile uint32 CR1;
    volatile uint32 CR2;
    volatile uint32 SMCR;
    volatile uint32 DIER;
    volatile uint32 SR;
    volatile uint32 EGR;
    volatile uint32 CCMR1_OUTPUTCOMPAREMODE;
    volatile uint32 CCMR1_INPUTCOMPAREMODE;
    volatile uint32 CCER;
    volatile uint32 CNT;
    volatile uint32 PSC;
    volatile uint32 ARR;
    volatile uint32 RESERVED;
    volatile uint32 CCR1;
    volatile uint32 CCR2;
    volatile uint32 CCR3;
    volatile uint32 CCR4;
    volatile uint32 RESERVED_1;
    volatile uint32 DCR;
    volatile uint32 DMAR;
} timer_registers;

/********** External APIs ****************************************************/

extern void Timer_Init (
            peripheral_clock_type peripherals,
            timer_type timer,
            clock_freq_type pre_scaler
);
extern void Timer_Delay(timer_type timmer, uint16 millisec);

#endif /* End of _TIMER_H_ */
