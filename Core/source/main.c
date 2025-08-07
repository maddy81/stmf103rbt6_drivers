/*============================== (c) 2025 ===================================
** File Name   :  main.c
** Author      :  Hammad.
** Created on  :  Aug 02, 2025
*---------------------------------------------------------------------------*
** Description : Main application entry point for STM32. Initializes
**               peripherals (Timer, GPIO, UART) and configures interrupts
**               for USART2 and external GPIO events. Contains the main loop
**               and ISR handlers for UART RX and EXTI lines.
=============================================================================*/

/*=============================================================================
**                                 Includes
=============================================================================*/
#include "timer.h"
#include "gpio.h"
#include "lin.h"
#include "nvic.h"
#include "blink_led.h"
#include "uart.h"

/*=============================================================================
**                             Global Variables
=============================================================================*/
uint8 Data_Receiver[12U];              // Buffer for incoming data (size 12)
/*=============================================================================
**                             Public Functions
=============================================================================*/

/******************************************************************************
** Function Name  : main
** Description    : Program entry point. Initializes required peripherals:
**                  - Timer3 for time base
**                  - GPIO for LED and button
**                  - External interrupt on PC13
**                  - UART2 for serial communication
**                  Enters infinite loop where application logic can be added.
** Input          : None
** Output         : None
** Return         : int (never returns in embedded context)
******************************************************************************/
int main(void) {

    Timer_Init (TIM3_EN, TIM_3, FREQ_8);   // Initialize Timer3 at 8 Hz
    
    Gpio_Init (PORT_A, PIN_5, GPIOA, SPEED_10_GENERAL_PURPOSE_OUTPUT_PUSHPULL); // LED output
    
    Gpio_Init(PORT_C, PIN_13, GPIOC, INPUT_PULLUP_PULLDOWN); // Button input
    Gpio_Configure_Interrupt(PIN_13, INT_FALLING_EDGE, PORT_C); // Falling edge trigger
    gpio_enable_interrupt(PIN_13, EXTI15_10_IRQn); // Enable EXTI interrupt for PC13

    Usart_Init(USART2_EN, UART_2, BAUDRATE_9600, USART2_IRQn); // UART2 init (9600 baud)

    
    
    while(1)
    {
       
    }
    
    return 0;
}

/******************************************************************************
** Function Name  : USART2_IRQHandler
** Description    : UART2 interrupt service routine. Handles RXNE event by:
**                  - Reading incoming data
**                  - Echoing it back to sender
**                  - Toggling LED on PA5
** Input          : None (hardware ISR)
** Output         : None
** Return         : None
******************************************************************************/
void USART2_IRQHandler(void)
{
    // Check if RXNE (Receive not empty) interrupt is pending
    if (UartChannels[UART_2]->SR & (1 << 5))  // RXNE
    {
        char received = UartChannels[UART_2]->DR;  // Read received byte

        // Echo back
        while (!(UartChannels[UART_2]->SR & (1 << 7)));  // Wait until TXE
        UartChannels[UART_2]->DR = received;

        // Toggle LED on PA5
        Pin_Toggle(PORT_A, PIN_5);
    }
}

/******************************************************************************
** Function Name  : EXTI15_10_IRQHandler
** Description    : External interrupt service routine for lines 10 to 15.
**                  Specifically handles EXTI line 13 (button on PC13).
**                  - Clears interrupt pending bit
**                  - Toggles PA13 as part of user-defined logic
** Input          : None (hardware ISR)
** Output         : None
** Return         : None
******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & (1 << 13)) {
        gpio_clear_interrupt(13);         // Clear EXTI pending flag
        // Example: Toggle LED or output pin
        Pin_Toggle(PORT_A, PIN_13);
    }
}
