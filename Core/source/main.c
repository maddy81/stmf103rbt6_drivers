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
#include "timer.h"
//#include "uart.h"
#include "gpio.h"
//#include "lin.h"
#include "nvic.h"
#include "blink_led.h"
//#include "adc.h"
#include "uart.h"

volatile char received_char = 0;
volatile uint8 data_ready = 0;

int main(void) {

    Timer_Init (TIM3_EN, TIM_3, FREQ_8);
	
	Gpio_Init (PORT_A, PIN_5, GPIOA, SPEED_10_GENERAL_PURPOSE_OUTPUT_PUSHPULL);
    
	Gpio_Init(PORT_C, PIN_13, GPIOC, INPUT_PULLUP_PULLDOWN);
    Gpio_Configure_Interrupt(PIN_13, INT_FALLING_EDGE, PORT_C);
    gpio_enable_interrupt(PIN_13, EXTI15_10_IRQn);

	Usart_Init(USART2_EN, UART_2, BAUDRATE_9600, USART2_IRQn);
	while(1)
	{
		
		//Blink_Led_Button_Press();
  Uart_RegisterType *uart = UartChannels[UART_2];
        if (uart->SR & (1 << 5)) {  // RXNE bit is set
            char received = uart->DR;  // Read received data

            // Echo the character back
            while (!(uart->SR & (1 << 7)));  // Wait until TXE (bit 7) is set
            uart->DR = received;

            // Optional: Toggle PA5 as visual feedback
            Pin_Toggle(PORT_A, PIN_5);
        }
    }
		
	
	
   
    return 0;
}

void USART2_IRQHandler(void)
{
    Uart_RegisterType *uart = UartChannels[UART_2];

    if (uart->SR & STATUS_RX)
    {
        received_char = uart->DR;  // Read received byte
        data_ready = 1;
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & (1 << 13)) {
        gpio_clear_interrupt(13);
        // Your logic: e.g., toggle LED on PA5
		Pin_Toggle(PORT_A,PIN_13);
    }
}