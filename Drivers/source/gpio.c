/******************************************************************************
* FILENAME :gpio.c
* DESCRIPTION : Gpio driver functions are being implemented in this file.
* AUTHOR : Hammad
******************************************************************************/

/********** includes *********************************************************/

#include "gpio.h"
#include "clock.h"

/********** Array of gpio adresses ******************************************/

static gpio_type * port_address [5U] =
{
   ((gpio_type*) (0x40010800U)),
   ((gpio_type*) (0x40010C00U)),
   ((gpio_type*) (0x40011000U)),
   ((gpio_type*) (0x40011400U)),
   ((gpio_type*) (0x40011800U))
};

/**
 * @brief Gpio_Init : configuration of gpio in all the modes
 * @param selected_port, pin_num, port, mode
 * @return void
 */
void Gpio_Init (port_type selected_port, gpio_pin_num pin_num, peripheral_clock_type peripherals, mode_type mode)
{
   Rcc_Enabler(peripherals);

   if (pin_num > PIN_SEVEN)
   {
      /*configuraton of pins above pin 7*/
	   port_address[selected_port]->CRH  &= ~(0xfU << (4 *(pin_num-8)));
	   port_address[selected_port]->CRH  |=  (mode << (4 *(pin_num-8)));
   }
   else
   {
    	port_address[selected_port]->CRL  &= ~(0xfU << (4 * pin_num));
    	port_address[selected_port]->CRL  |=  (mode << (4 * pin_num));
   }
}
  
void Pin_High (port_type selected_port, gpio_pin_num pin_num)
{
	port_address[selected_port]->ODR |= (HIGH << pin_num);
}

void Pin_Low (port_type selected_port, gpio_pin_num pin_num)
{
	port_address[selected_port]->ODR &= ~(HIGH << pin_num);
}


/**
 * @brief Pin_Toggle : Making pin High/Low 
 * @param selected_port, pin_num
 * @param pin_num
 * @return void
 */
void Pin_Toggle (port_type selected_port, gpio_pin_num pin_num)
{
	port_address[selected_port]->ODR ^= PIN_TOGGLE;
}

/**
 * @brief Gpio_Pin_Read:Input from user to make pin high low
 * @param selected_port, pin_num
 * @param pin_num 
 * @return void
 */

uint8 Gpio_Pin_Read(port_type port, gpio_pin_num pin)
{
    return (port_address[port]->IDR & (1U << pin)) ? 1 : 0;
}

void Gpio_Configure_Interrupt(uint16 pin_no, int_edge_sel_t edge_sel, port_type port)
{
    // Configure edge trigger
    if (edge_sel == INT_RISING_EDGE)
        EXTI->RTSR |= (1U << pin_no);
    else if (edge_sel == INT_FALLING_EDGE)
        EXTI->FTSR |= (1U << pin_no);
    else if (edge_sel == INT_RISING_FALLING_EDGE)
    {
        EXTI->RTSR |= (1U << pin_no);
        EXTI->FTSR |= (1U << pin_no);
    }

    // Enable AFIO clock
    Rcc_Enabler(AFIO_EN);

    // Configure EXTIx to map to correct port in EXTICR
    uint8 exti_index = pin_no / 4;
    uint8 exti_pos = (pin_no % 4) * 4;

    AFIO->EXTICR[exti_index] &= ~(0xF << exti_pos);  // Clear
    AFIO->EXTICR[exti_index] |= (port << exti_pos);  // Set port

    // Unmask interrupt
    EXTI->IMR |= (1U << pin_no);
}
// void Gpio_Configure_Interrupt(uint16 pin_no, int_edge_sel_t edge_sel)
// {
//    if (edge_sel == INT_RISING_EDGE )
// 	{
// 		EXTI->RTSR |= 1 << pin_no;
// 	}	
// 	else if (edge_sel == INT_FALLING_EDGE)
// 	{
// 		EXTI->FTSR |= 1 << pin_no;
// 	}else if (edge_sel == INT_RISING_FALLING_EDGE )
// 	{
// 		EXTI->FTSR |= 1 << pin_no;
// 		EXTI->RTSR |= 1 << pin_no;
// 	}
// 	else
// 	{
// 		 ;//TODO
// 	}
// }


void gpio_enable_interrupt(uint16 pin_no, IRQn_Type irq_no)
{
   EXTI->IMR |= 1 << pin_no;
	NVIC_EnableIRQ(irq_no);
}

void gpio_clear_interrupt(uint16 pin)
{
   if(EXTI->PR & (1 << pin ))
	{
		EXTI->PR |= 1 << pin;
	}
}
