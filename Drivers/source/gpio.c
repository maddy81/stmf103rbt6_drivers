/*============================== (c) 2025 ===================================
** File Name   :  gpio.c
** Author      :  Hammad
** Created on  :  Aug 08, 2025
*---------------------------------------------------------------------------*
** Description : Implements GPIO driver functions for STM32. Provides
**               configuration, read/write, toggling, and external interrupt
**               setup for general-purpose I/O pins.
=============================================================================*/

/*=============================================================================
**                                 Includes
=============================================================================*/
#include "gpio.h"
#include "clock.h"

/*=============================================================================
**                             Local Variables
=============================================================================*/
/* Array of GPIO base addresses for ports A-E */
static gpio_type * port_address[5U] =
{
   ((gpio_type*) (0x40010800U)), // GPIOA
   ((gpio_type*) (0x40010C00U)), // GPIOB
   ((gpio_type*) (0x40011000U)), // GPIOC
   ((gpio_type*) (0x40011400U)), // GPIOD
   ((gpio_type*) (0x40011800U))  // GPIOE
};

/*=============================================================================
**                             Public Functions
=============================================================================*/

/******************************************************************************
** Function Name  : Gpio_Init
** Description    : Configures a GPIO pin in any available mode. Enables
**                  the corresponding peripheral clock and sets the control
**                  registers for pins 0–7 (CRL) or 8–15 (CRH).
** Input          : selected_port (port_type)      - GPIO port index
**                  pin_num      (gpio_pin_num)    - Pin number (0–15)
**                  peripherals  (peripheral_clock_type) - Peripheral clock ID
**                  mode         (mode_type)       - Pin mode configuration
** Output         : None
** Return         : None
******************************************************************************/
void Gpio_Init (port_type selected_port, gpio_pin_num pin_num, peripheral_clock_type peripherals, mode_type mode)
{
   Rcc_Enabler(peripherals);

   if (pin_num > PIN_SEVEN)
   {
      /* Configuration of pins above pin 7 (CRH register) */
      port_address[selected_port]->CRH &= ~(0xFU << (4 * (pin_num - 8)));
      port_address[selected_port]->CRH |=  (mode << (4 * (pin_num - 8)));
   }
   else
   {
      /* Configuration of pins 0–7 (CRL register) */
      port_address[selected_port]->CRL &= ~(0xFU << (4 * pin_num));
      port_address[selected_port]->CRL |=  (mode << (4 * pin_num));
   }
}

/******************************************************************************
** Function Name  : Pin_High
** Description    : Sets the specified GPIO pin to logic HIGH.
** Input          : selected_port (port_type)   - GPIO port index
**                  pin_num      (gpio_pin_num) - Pin number (0–15)
** Output         : None
** Return         : None
******************************************************************************/
void Pin_High (port_type selected_port, gpio_pin_num pin_num)
{
   port_address[selected_port]->ODR |= (HIGH << pin_num);
}

/******************************************************************************
** Function Name  : Pin_Low
** Description    : Sets the specified GPIO pin to logic LOW.
** Input          : selected_port (port_type)   - GPIO port index
**                  pin_num      (gpio_pin_num) - Pin number (0–15)
** Output         : None
** Return         : None
******************************************************************************/
void Pin_Low (port_type selected_port, gpio_pin_num pin_num)
{
   port_address[selected_port]->ODR &= ~(HIGH << pin_num);
}

/******************************************************************************
** Function Name  : Pin_Toggle
** Description    : Toggles the specified GPIO pin's output state.
** Input          : selected_port (port_type)   - GPIO port index
**                  pin_num      (gpio_pin_num) - Pin number (0–15)
** Output         : None
** Return         : None
******************************************************************************/
void Pin_Toggle (port_type selected_port, gpio_pin_num pin_num)
{
   port_address[selected_port]->ODR ^= PIN_TOGGLE;
}

/******************************************************************************
** Function Name  : Gpio_Pin_Read
** Description    : Reads the logical state of a GPIO pin.
** Input          : port   (port_type)      - GPIO port index
**                  pin    (gpio_pin_num)   - Pin number (0–15)
** Output         : None
** Return         : uint8 (1 if pin is HIGH, 0 if LOW)
******************************************************************************/
uint8 Gpio_Pin_Read(port_type port, gpio_pin_num pin)
{
    return (port_address[port]->IDR & (1U << pin)) ? 1 : 0;
}

/******************************************************************************
** Function Name  : Gpio_Configure_Interrupt
** Description    : Configures external interrupt for a given GPIO pin.
**                  Sets edge trigger type, maps the pin to EXTI line, and
**                  unmasks the interrupt in EXTI->IMR.
** Input          : pin_no   (uint16)       - Pin number (0–15)
**                  edge_sel (int_edge_sel_t) - Interrupt edge selection
**                  port     (port_type)    - GPIO port index
** Output         : None
** Return         : None
******************************************************************************/
void Gpio_Configure_Interrupt(uint16 pin_no, int_edge_sel_t edge_sel, port_type port)
{
    /* Configure edge trigger type */
    if (edge_sel == INT_RISING_EDGE)
        EXTI->RTSR |= (1U << pin_no);
    else if (edge_sel == INT_FALLING_EDGE)
        EXTI->FTSR |= (1U << pin_no);
    else if (edge_sel == INT_RISING_FALLING_EDGE)
    {
        EXTI->RTSR |= (1U << pin_no);
        EXTI->FTSR |= (1U << pin_no);
    }

    /* Enable AFIO clock */
    Rcc_Enabler(AFIO_EN);

    /* Map EXTI line to the correct GPIO port */
    uint8 exti_index = pin_no / 4;
    uint8 exti_pos = (pin_no % 4) * 4;

    AFIO->EXTICR[exti_index] &= ~(0xF << exti_pos);  // Clear previous mapping
    AFIO->EXTICR[exti_index] |= (port << exti_pos);  // Set new mapping

    /* Unmask interrupt */
    EXTI->IMR |= (1U << pin_no);
}

/******************************************************************************
** Function Name  : gpio_enable_interrupt
** Description    : Enables NVIC and unmasks EXTI interrupt for a given pin.
** Input          : pin_no (uint16) - Pin number (0–15)
**                  irq_no (IRQn_Type) - NVIC interrupt number
** Output         : None
** Return         : None
******************************************************************************/
void gpio_enable_interrupt(uint16 pin_no, IRQn_Type irq_no)
{
   EXTI->IMR |= 1 << pin_no;
   NVIC_EnableIRQ(irq_no);
}

/******************************************************************************
** Function Name  : gpio_clear_interrupt
** Description    : Clears pending interrupt flag for a given EXTI pin.
** Input          : pin (uint16) - Pin number (0–15)
** Output         : None
** Return         : None
******************************************************************************/
void gpio_clear_interrupt(uint16 pin)
{
   if (EXTI->PR & (1 << pin))
   {
      EXTI->PR |= 1 << pin;
   }
}
