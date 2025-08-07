/*============================== (c) 2025 ===================================
** File Name   :  uart.c
** Author      :  Hammad
** Created on  :  Aug 08, 2025
*---------------------------------------------------------------------------*
** Description : Uart driver functions are being implemented in this file.
=============================================================================*/

/*=============================================================================
**                                 Includes
=============================================================================*/
#include "uart.h"
#include "clock.h"
#include "nvic.h"
#include "gpio.h"
//#include "lin.h"

/*=============================================================================
**                       Private Functions Prototypes
=============================================================================*/
static void Usart_GpioInit (peripheral_clock_type peripherals);

/*=============================================================================
**                      Pointer Array of addresses
=============================================================================*/
Uart_RegisterType * UartChannels [3U] =
{
	((Uart_RegisterType *) (0x40013800U)),
	((Uart_RegisterType *) (0x40004400U)),
	((Uart_RegisterType *) (0x40004800U)),
};

/****************************************************************************** 
** Function Name  : Usart_Init
** Description    : sets clock, enables TX and Rx of uart and their interrupts 
** Input          : peripherals, reg
** Output         : None
** Return         : void
******************************************************************************/
void Usart_Init (peripheral_clock_type peripherals, Uart_Type uart, BaudrateType baud, IRQn_Type irq)
{
	Uart_RegisterType * uartChannel = UartChannels[uart];

	Rcc_Enabler(peripherals);
	Usart_GpioInit(peripherals);

	uartChannel->BRR = baud;

	uartChannel->CR1 = (TX_COMPLETE_INTERRUPT_ENABLE | TX_ENABLE | RX_ENABLE | USART_ENABLE | RX_INTERRUPT_ENABLE);

	Enable_Irq();
	NVIC_EnableIRQ(irq);
}

/****************************************************************************** 
** Function Name  : Usart_GpioInit
** Description    : Enable gpio pins according to uart
** Input          : peripherals
** Output         : static void
** Return         : None
******************************************************************************/
static void Usart_GpioInit (peripheral_clock_type peripherals)
{
	if (peripherals == USART1_EN)
	{
		Gpio_Init (PORT_A, PIN_9, GPIOA, SPEED_10_ALTERNATE_FUNCTION_OUTPUT_PUSHPULL);
	    Gpio_Init (PORT_A, PIN_10, GPIOA, INPUT_PULLUP_PULLDOWN);
	}

	if (peripherals == USART2_EN)
	{
		Gpio_Init (PORT_A, PIN_2, GPIOA, SPEED_10_ALTERNATE_FUNCTION_OUTPUT_PUSHPULL);
	    Gpio_Init (PORT_A, PIN_3, GPIOA, INPUT_PULLUP_PULLDOWN);
	}

	if (peripherals == USART3_EN)
	{
		Gpio_Init (PORT_B, PIN_10, GPIOB, SPEED_10_ALTERNATE_FUNCTION_OUTPUT_PUSHPULL);
		Gpio_Init (PORT_B, PIN_11, GPIOB, INPUT_PULLUP_PULLDOWN);
	}
}

/****************************************************************************** 
** Function Name  : Usart_SendByte
** Description    : For Sending data byte by byte
** Input          : uart, data
** Output         : None
** Return         : uint8
******************************************************************************/
uint8 Usart_SendByte (Uart_Type uart,  char data)
{
	return UartChannels[uart]->DR = data;
}

/****************************************************************************** 
** Function Name  : Usart_ReceiveByte
** Description    : Receive data through Uart
** Input          : uart
** Output         : None
** Return         : uint8
******************************************************************************/
uint8 Usart_ReceiveByte (Uart_Type uart)
{
	return UartChannels[uart]->DR;
}
