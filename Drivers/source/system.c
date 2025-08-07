/*============================== (c) 2025 ===================================
** File Name   :  system.c
** Author      :  Hammad
** Created on  :  Aug 08, 2025
*---------------------------------------------------------------------------*
** Description : Implements system-level functions, including vector table
**               configuration.
=============================================================================*/

/*=============================================================================
**                                 Includes
=============================================================================*/
#include "system.h"

/*=============================================================================
**                             Public Functions
=============================================================================*/

/******************************************************************************
** Function Name  : System
** Description    : Configures the Vector Table Offset Register (VTOR) to
**                  point to the defined vector table base address and offset.
** Input          : None
** Output         : None
** Return         : None
******************************************************************************/
void System (void)
{
    VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET;
}
