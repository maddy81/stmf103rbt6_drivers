/******************************************************************************
* FILENAME :gpio.h
* DESCRIPTION : Header file of gpio.c conatains gpio function prototypes, macros
                structures, enums
* AUTHOR : Hammad
******************************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

/********** Includes *********************************************************/

#include "clock.h"
#include "std_types.h"
#include "nvic.h"

/********** Macros ***********************************************************/

#define PIN_SEVEN   (0x7U)
#define PIN_TOGGLE  (0x20U)
#define EXTI_BASEADDR							(APB2PERIPH_BASEADDR + 0x0400) // EXTI peripheral base address on APB2 bus
#define APB2PERIPH_BASEADDR    					0x40010000U			// APB2 bus starting address
#define EXTI ((EXTI_RegDef_t*) EXTI_BASEADDR)  						// EXTI register structure pointer
#define AFIO_BASEADDR							(APB2PERIPH_BASEADDR)	
#define AFIO ((AFIO_RegDef_t*) AFIO_BASEADDR) 
#define AFIO_EN   0
/********** STRUCTURES *******************************************************/

typedef struct 
{
    volatile uint32 CRL;
    volatile uint32 CRH;
    volatile uint32 IDR;
    volatile uint32 ODR;
    volatile uint32 BSRR;
    volatile uint32 BRR;
    volatile uint32 LOCKR;
} gpio_type;

/********** ENUMS *******************************************************/

typedef enum
{
    PORT_A = 0,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E
} port_type;

typedef enum
{
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15
} gpio_pin_num;

typedef enum
{
    Input_Analog_Mode = 0x0,
    SPEED_10_GENERAL_PURPOSE_OUTPUT_PUSHPULL, 
    SPEED_02_GENERAL_PURPOSE_OUTPUT_PUSHPULL,
    SPEED_50_GENERAL_PURPOSE_OUTPUT_PUSHPULL, 
    INPUT_FLOATING,
    SPEED_10_GENERAL_PURPOSE_OUTPUT_OPENDRAIN,
    SPEED_02_GENERAL_PURPOSE_OUTPUT_OPENDRAIN,
    SPEED_50_GENERAL_PURPOSE_OUTPUT_OPENDRAIN,
    INPUT_PULLUP_PULLDOWN,
    SPEED_10_ALTERNATE_FUNCTION_OUTPUT_PUSHPULL,
    SPEED_02_ALTERNATE_FUNCTION_OUTPUT_PUSHPULL,
    SPEED_50_ALTERNATE_FUNCTION_OUTPUT_PUSHPULL,
    INPUT_RESERVED,
    SPEED_10_ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN,
    SPEED_02_ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN,
    SPEED_50_ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN,
} mode_type;

/**
* @brief  Interrupt Edge selection enum 
*/
typedef enum
{
	INT_RISING_EDGE,
	INT_FALLING_EDGE,
	INT_RISING_FALLING_EDGE
}int_edge_sel_t;

typedef struct
{
	volatile uint32 IMR; 				// Interrupt mask register							Address offset:0x00
	volatile uint32 EMR;				// Event mask register								Address offset:0x04
	volatile uint32 RTSR;				// Rising trigger selection register				Address offset:0x08
	volatile uint32 FTSR;				// Falling trigger selection register				Address offset:0x0c
	volatile uint32 SWIER;			// Software interrupt event register				Address offset:0x10
	volatile uint32 PR;				// Pending register									Address offset:0x14
}EXTI_RegDef_t;

/*
 * Peripheral register definition structure for AFIO
 */
typedef struct
{
	volatile uint32 EVCR;				// Event control register 							Address offset:0x00
	volatile uint32 MAPR;				// AF remap and debug I/O configuration register	Address offset:0x04
	volatile uint32 EXTICR[4];		// External interrupt configuration registers 		Address offset:0x08-0x14
	volatile uint32 MAPR2;			// AF remap and debug I/O configuration register2	Address offset:0x18
}AFIO_RegDef_t;


/********** External APIs ****************************************************/

extern void Gpio_Init (
                        port_type selected_port,
                        gpio_pin_num pin_num,
                        peripheral_clock_type peripherals,
                        mode_type mode
);
extern void Pin_High (port_type selected_port, gpio_pin_num pin_num);
extern void Pin_Low (port_type selected_port, gpio_pin_num pin_num);
extern void Pin_Toggle (port_type selected_port, gpio_pin_num pin_num);
void Gpio_Configure_Interrupt(uint16 pin_no, int_edge_sel_t edge_sel, port_type port);
void gpio_enable_interrupt(uint16 pin_no, IRQn_Type irq_no);
void gpio_clear_interrupt(uint16 pin);

uint8 Gpio_Pin_Read(port_type port, gpio_pin_num pin);

#endif /* End of _GPIO_H_ */
