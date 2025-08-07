/******************************************************************************
* FILENAME : uart.c
* DESCRIPTION : Uart driver functions are being implemented in this file.
* AUTHOR : Hammad
******************************************************************************/

/********** Includes *********************************************************/

#include "uart.h"
#include "clock.h"
#include "nvic.h"
#include "gpio.h"
//#include "lin.h"

static void Usart_GpioInit (peripheral_clock_type peripherals);

/**********  Pointer Array of addresses **************************************/

Uart_RegisterType * UartChannels [3U] =
{
	((Uart_RegisterType *) (0x40013800U)),
	((Uart_RegisterType *) (0x40004400U)),
	((Uart_RegisterType *) (0x40004800U)),
};

/**
 * @brief Usart_Init : sets clock, enables TX and Rx of uart and their interrupts 
 * @param peripherals
 * @param reg
 * @return void
 */
void Usart_Init (peripheral_clock_type peripherals, Uart_Type uart, BaudrateType baud, IRQn_Type irq)
{
	Uart_RegisterType * uartChannel = UartChannels[uart];

	Rcc_Enabler(peripherals);
	Usart_GpioInit(peripherals);

	uartChannel->BRR = baud;

	uartChannel->CR1 = (TX_COMPLETE_INTERRUPT_ENABLE | TX_ENABLE | RX_ENABLE | USART_ENABLE | RX_INTERRUPT_ENABLE);

	//Enable_Irq();
	//NVIC_EnableIRQ(irq);
}


/**
 * @brief Uart_GpioInit : Enable gpio pins according to uart
 * @param peripherals
 * @return static void
 */
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

/**
 * @brief Uart_SendByte : For Sending data byte by byte
 * @param uart, data
 * @return uint8
 */
uint8 Usart_SendByte (Uart_Type uart,  char data)
{
	return UartChannels[uart]->DR = data;
}

/**
 * @brief Uart_Receive_Data : Receive data through Uart
 * @param uart
 * @return uint8
 */
uint8 Usart_ReceiveByte (Uart_Type uart)
{
	return UartChannels[uart]->DR;
}



