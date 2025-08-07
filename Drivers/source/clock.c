/*============================== (c) 2025 ===================================
** File Name   :  clock.c
** Author      :  Hammad
** Created on  :  Aug 08, 2025
*---------------------------------------------------------------------------*
** Description : Implements clock driver functions for enabling peripheral
**               clocks via RCC (Reset and Clock Control) registers.
=============================================================================*/

/*=============================================================================
**                                 Includes
=============================================================================*/
#include "clock.h"

/*=============================================================================
**                             Public Functions
=============================================================================*/

/******************************************************************************
** Function Name  : Rcc_Enabler
** Description    : Enables the clock for the specified peripheral using
**                  the RCC (Reset and Clock Control) registers.
**                  - If the peripheral index is within APB2 range, it updates
**                    RCC_APB2ENR_ENABLER.
**                  - Otherwise, it enables the peripheral clock via
**                    RCC_APB1ENR_ENABLER.
** Input          : peripherals (peripheral_clock_type) :
**                  Identifier for the target peripheral clock.
** Output         : None
** Return         : None
******************************************************************************/
void Rcc_Enabler (peripheral_clock_type peripherals)
{  
   if (peripherals <= RESERVED_15)
   {  
      /* Enabling peripherals at APB2 Bus */
      RCC_APB2ENR_ENABLER |= (HIGH << peripherals);
   }
   else
   {
      /* Enabling peripherals at APB1 Bus */
      RCC_APB1ENR_ENABLER |= (HIGH << (peripherals - APB2_END));
   }
}
