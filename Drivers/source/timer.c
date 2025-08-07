/******************************************************************************
* FILENAME :timer.c
* DESCRIPTION :Timer driver functions are being implemented in this file.
* AUTHOR : Hammad
******************************************************************************/

/*********** includes *******************************************************/

#include "timer.h"
#include "nvic.h"
#include "gpio.h"
#include "clock.h"

/**********  Pointer Array of addresses **************************************/

static timer_registers * timer_address [5U] = 
{
   ((timer_registers*) (0x40012C00U)),
   ((timer_registers*) (0x40000000U)),
   ((timer_registers*) (0x40000400U)),
   ((timer_registers*) (0x40000800U)),
   ((timer_registers*) (0x40000C00U))
};

static void Timer_BusFreq (clock_freq_type pre_scaler);

/**
 * @brief Timer_Init : This fuction enables the clock for timer and set the pre-scaler
 * @param peripherals, timer, prs
 * @return void
 */
void Timer_Init (peripheral_clock_type peripherals, timer_type timer, clock_freq_type pre_scaler)
{
   /* Enable clock for timers */
   Rcc_Enabler(peripherals);
   
   /* Setting the Pre-Scaler */
   timer_address[timer]->PSC = pre_scaler - 1;
   
}

/**
 * @brief 
 * 
 * @param timer 
 * @param millisec 
 */
void Timer_Delay (timer_type timer, uint16 millisec)
{  
   /* Setting value in auto reload register */
	timer_address[timer]->ARR = millisec;
   
   /* Enabling the Counter */
   timer_address[timer]->CR1 = HIGH;

   /* Start the counter from zero */
	timer_address[timer]->CNT = 0;

   /* Delay implementation putting a wait until counter reaches the ARR value */
	while (!(timer_address[timer]->CNT == millisec - 1));

   /* Setting the counter again to zero */
	timer_address[timer]->CNT &= 0;
}

/**
 * @brief Bus_Freq : To set the timer bus frequency to 16 and 32MHz 
 * @param pre_scaler 
 * @return void
 */
static void Timer_BusFreq (clock_freq_type pre_scaler)
{
	if (pre_scaler == FREQ_16)
   { 
      /* Selecting Pll as clock and wait for it to become ready */
	   RCC_CFGR |= SYS_CLOCK_SWITCH;
	   while(!(RCC_CFGR & SYS_CLOCK_STATUS ));

      /* Enabling the Pll and wait for it to become ready (requires 6 cycles)*/
	   RCC_CR |= PLLON;
	   while(!(RCC_CR & PLL_RDY));

      /* Setting the Pll for 16MHz */
	   RCC_CFGR |= PLL_MUL_4;
   }

	if (pre_scaler == FREQ_32)
   {  
      /* Selecting Pll as clock and wait for it to become ready */
	   RCC_CFGR |= SYS_CLOCK_SWITCH;
	   while(!(RCC_CFGR & SYS_CLOCK_STATUS ));

      /* Enabling the Pll and wait for it to become ready (requires 6 cycles)*/
	   RCC_CR |= PLLON;
	   while(!(RCC_CR & PLL_RDY));
      
      /* Setting the Pll for 32MHz */
      RCC_CFGR |= PLL_MUL_8;
   }
}














