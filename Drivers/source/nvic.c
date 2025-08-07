/******************************************************************************
* FILENAME :nvic.c
* DESCRIPTION : Nvic driver functions are being implemented in this file.
* AUTHOR : Hammad
******************************************************************************/

/*********** includes ********************************************************/

#include "nvic.h"


/**
 * @brief NVIC_EnableIRQ : Turns on the specified Bit defined in the argument
                           in NVIC Interrupt enable Register
 * @param IRQn
 * @return void
 */
void NVIC_EnableIRQ (IRQn_Type IRQn)
{
  if (IRQn <= 31 && IRQn >= 0)
	{
		NVIC->ISER0 = ( HIGH << IRQn );
	}
	else if (IRQn <= 63 && IRQn >= 32)
	{
		NVIC->ISER1 = (HIGH << ( IRQn - ISER0_END ));
	}
  else
	{
		NVIC -> ISER2 |= (HIGH << ( IRQn - ISER1_END ));
	} 
}

/**
 * @brief Enable_Irq : Enables the global interrupts of CPU
 * @param void
 * @return void
 */
void Enable_Irq (void)
{ 
  /* Assembley Language code for enabling CPU Interrupts */
  __asm volatile ("cpsie i" : : : "memory");
}

/**
 * @brief Disable_Irq : Disable the global interrupts of CPU
 * @param void
 * @return void
 */
void Disable_Irq (void)
{
  /* Assembley Language code for disabling CPU Interrupts */
  __asm volatile ("cpsid i" : : : "memory"); 
}
