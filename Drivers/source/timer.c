/*============================== (c) 2025 ===================================
** File Name   :  timer.c
** Author      :  Hammad
** Created on  :  Aug 08, 2025
*---------------------------------------------------------------------------*
** Description : Implements Timer driver functions for initialization, delay
**               generation, and bus frequency configuration.
=============================================================================*/

/*=============================================================================
**                                 Includes
=============================================================================*/
#include "timer.h"
#include "nvic.h"
#include "gpio.h"
#include "clock.h"

/*=============================================================================
**                             Private Data
=============================================================================*/

/* Pointer array to timer register base addresses */
static timer_registers * timer_address[5U] = 
{
    ((timer_registers*)(0x40012C00U)), /* TIM1 */
    ((timer_registers*)(0x40000000U)), /* TIM2 */
    ((timer_registers*)(0x40000400U)), /* TIM3 */
    ((timer_registers*)(0x40000800U)), /* TIM4 */
    ((timer_registers*)(0x40000C00U))  /* TIM5 */
};

/*=============================================================================
**                             Private Functions
=============================================================================*/
static void Timer_BusFreq(clock_freq_type pre_scaler);

/*=============================================================================
**                             Public Functions
=============================================================================*/

/******************************************************************************
** Function Name  : Timer_Init
** Description    : Enables clock for the given timer and sets the prescaler.
** Input          : peripherals (peripheral_clock_type) - Peripheral clock to enable
**                  timer       (timer_type)            - Timer index
**                  pre_scaler  (clock_freq_type)        - Clock frequency prescaler
** Output         : None
** Return         : None
******************************************************************************/
void Timer_Init(peripheral_clock_type peripherals, timer_type timer, clock_freq_type pre_scaler)
{
    /* Enable clock for timers */
    Rcc_Enabler(peripherals);

    /* Set prescaler value */
    timer_address[timer]->PSC = pre_scaler - 1;
}

/******************************************************************************
** Function Name  : Timer_Delay
** Description    : Generates a blocking delay using the specified timer.
** Input          : timer     (timer_type) - Timer index
**                  millisec  (uint16)     - Delay in milliseconds
** Output         : None
** Return         : None
******************************************************************************/
void Timer_Delay(timer_type timer, uint16 millisec)
{  
    /* Set Auto-Reload Register */
    timer_address[timer]->ARR = millisec;

    /* Enable the counter */
    timer_address[timer]->CR1 = HIGH;

    /* Reset counter to zero */
    timer_address[timer]->CNT = 0;

    /* Wait until counter reaches ARR value */
    while (!(timer_address[timer]->CNT == millisec - 1));

    /* Reset counter to zero */
    timer_address[timer]->CNT &= 0;
}

/*=============================================================================
**                             Private Functions
=============================================================================*/

/******************************************************************************
** Function Name  : Timer_BusFreq
** Description    : Configures the timer bus frequency to 16MHz or 32MHz.
** Input          : pre_scaler (clock_freq_type) - Desired frequency
** Output         : None
** Return         : None
******************************************************************************/
static void Timer_BusFreq(clock_freq_type pre_scaler)
{
    if (pre_scaler == FREQ_16)
    { 
        /* Select PLL as clock source and wait for it to be ready */
        RCC_CFGR |= SYS_CLOCK_SWITCH;
        while (!(RCC_CFGR & SYS_CLOCK_STATUS));

        /* Enable PLL and wait until ready */
        RCC_CR |= PLLON;
        while (!(RCC_CR & PLL_RDY));

        /* Set PLL for 16MHz */
        RCC_CFGR |= PLL_MUL_4;
    }

    if (pre_scaler == FREQ_32)
    {  
        /* Select PLL as clock source and wait for it to be ready */
        RCC_CFGR |= SYS_CLOCK_SWITCH;
        while (!(RCC_CFGR & SYS_CLOCK_STATUS));

        /* Enable PLL and wait until ready */
        RCC_CR |= PLLON;
        while (!(RCC_CR & PLL_RDY));

        /* Set PLL for 32MHz */
        RCC_CFGR |= PLL_MUL_8;
    }
}
