/******************************************************************************
* FILENAME :clock.c
* DESCRIPTION : clock driver functions are being implemented in this file.
* AUTHOR : Hammad
******************************************************************************/

/*********** includes *******************************************************/

#include "clock.h"

/**
 * @brief Rcc_Enabler :Enables clock for any peripherals
 * @param peripherals
 * @return void
 */
void Rcc_Enabler (peripheral_clock_type peripherals)
{  
   if (peripherals <= RESERVED_15)
   {  
      /* Enabling peripherals at APB2 Bus */
      RCC_APB2ENR_ENABLER |= ( HIGH << peripherals );
   }
   else
   {
      /* Enabling peripherals at APB2 Bus */
      RCC_APB1ENR_ENABLER |= (HIGH << ( peripherals - APB2_END ));
   }
}



