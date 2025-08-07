
/******************************************************************************
* FILENAME : uart.h
* DESCRIPTION : Header file of Uart conatains uart function prototypes, macros
                structures, enums
* AUTHOR : Hammad
******************************************************************************/

#ifndef _UART_H_
#define _UART_H_

/********** Includes *********************************************************/

#include "gpio.h"
#include "clock.h"
#include "nvic.h"
#include "std_types.h"

/********** Macros ***********************************************************/

#define TX_ENABLE                     (0x0008U)
#define RX_ENABLE                     (0X0004U)
#define RX_INTERRUPT_ENABLE           (0X0020U)
#define USART_ENABLE                  (0x2000U)
#define TX_COMPLETE_INTERRUPT_ENABLE	(1U << 6U)
#define STATUS_RX                     (1U << 5U)
#define STATUS_TX_COMPLETE            (1U << 6U)



/********** ENUMS ************************************************************/

typedef enum
{
  BAUDRATE_9600 = 0x0341U,
  BAUDRATE_115200 = 0x0045U
} BaudrateType;

typedef enum
{
	UART_1 = 0,
	UART_2,
	UART_3,
} Uart_Type;

/********** STRUCTURES *******************************************************/

typedef struct
{
  volatile uint32 SR;
  volatile uint32 DR;
  volatile uint32 BRR;
  volatile uint32 CR1;
  volatile uint32 CR2;
  volatile uint32 CR3;
  volatile uint32 GTPR;
} Uart_RegisterType;
extern Uart_RegisterType * UartChannels[3U];
/********** External APIs ****************************************************/

extern void Usart_Init (peripheral_clock_type peripherals,
                        Uart_Type uart, 
                        BaudrateType baud, 
                        IRQn_Type irq
);
extern uint8 Usart_SendByte (Uart_Type uart, char data);
extern uint8 Usart_ReceiveByte (Uart_Type uart);

#endif /* End of _UART_H_ */




