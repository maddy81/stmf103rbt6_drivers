/*============================== (c) 2025 ===================================
** File Name   :  nvic.c
** Author      :  Hammad
** Created on  :  Aug 08, 2025
*---------------------------------------------------------------------------*
** Description : Implements NVIC driver functions for enabling specific
**               interrupts and managing global CPU interrupt control.
=============================================================================*/

/*=============================================================================
**                                 Includes
=============================================================================*/
#include "nvic.h"

/*=============================================================================
**                             Public Functions
=============================================================================*/

/******************************************************************************
** Function Name  : NVIC_EnableIRQ
** Description    : Enables the specified IRQ number in the NVIC interrupt
**                  enable registers (ISER0, ISER1, ISER2).
** Input          : IRQn (IRQn_Type) :
**                  - Interrupt Request Number to enable.
** Output         : None
** Return         : None
******************************************************************************/
void NVIC_EnableIRQ (IRQn_Type IRQn)
{
    if (IRQn <= 31 && IRQn >= 0)
    {
        NVIC->ISER0 = (HIGH << IRQn);
    }
    else if (IRQn <= 63 && IRQn >= 32)
    {
        NVIC->ISER1 = (HIGH << (IRQn - ISER0_END));
    }
    else
    {
        NVIC->ISER2 |= (HIGH << (IRQn - ISER1_END));
    } 
}

/******************************************************************************
** Function Name  : Enable_Irq
** Description    : Globally enables CPU interrupts.
** Input          : None
** Output         : None
** Return         : None
******************************************************************************/
void Enable_Irq (void)
{ 
    /* Assembly instruction to enable CPU interrupts */
    __asm volatile ("cpsie i" : : : "memory");
}

/******************************************************************************
** Function Name  : Disable_Irq
** Description    : Globally disables CPU interrupts.
** Input          : None
** Output         : None
** Return         : None
******************************************************************************/
void Disable_Irq (void)
{
    /* Assembly instruction to disable CPU interrupts */
    __asm volatile ("cpsid i" : : : "memory"); 
}
