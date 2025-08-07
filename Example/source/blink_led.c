/*============================== (c) 2025 ===================================
** File Name   :  main.c
** Author      :  Hammad.
** Created on  :  Aug 02, 2025
*---------------------------------------------------------------------------*
** Description : 
=============================================================================*/

/*=============================================================================
**                                 Includes
=============================================================================*/
#include "blink_led.h"
#include "gpio.h"


void Blink_Led_Button_Press()
{
    	if (Gpio_Pin_Read(PORT_C, PIN_13) == 0)  // Button is pressed (active low)
        {
            Pin_High(PORT_A, PIN_5);  // Turn on LED
        }
        else
        {
            Pin_Low(PORT_A, PIN_5);   // Turn off LED
        }
}