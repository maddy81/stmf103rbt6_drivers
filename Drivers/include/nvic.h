/******************************************************************************
* FILENAME :nvic.h
* DESCRIPTION : Header file of nvic.c conatains nvic function prototypes, macros
                structures, enums
* AUTHOR : Hammad
******************************************************************************/

#ifndef _NVIC_H
#define _NVIC_H

/********** Includes *********************************************************/

#include "std_types.h"

/********** Macros *************************************************************/

#define NVIC_BASE   (0xE000E100UL)
#define ISER0_END   (0X20U)
#define ISER1_END   (0x40U)
#define NVIC        ((NVIC_Type *) NVIC_BASE)
#define HIGH        (0x1U)
#define LOW         (0x0U)

/********** ENUMS *******************************************************/

typedef enum
{
  NonMaskableInt_IRQn         = -14,    
  HardFault_IRQn              = -13,    
  MemoryManagement_IRQn       = -12,    
  BusFault_IRQn               = -11,    
  UsageFault_IRQn             = -10,    
  SVCall_IRQn                 = -5,     
  DebugMonitor_IRQn           = -4,     
  PendSV_IRQn                 = -2,     
  SysTick_IRQn                = -1,       
  WWDG_IRQn                   = 0,      
  PVD_IRQn                    = 1,      
  TAMPER_IRQn                 = 2,      
  RTC_IRQn                    = 3,      
  FLASH_IRQn                  = 4,      
  RCC_IRQn                    = 5,      
  EXTI0_IRQn                  = 6,      
  EXTI1_IRQn                  = 7,      
  EXTI2_IRQn                  = 8,      
  EXTI3_IRQn                  = 9,      
  EXTI4_IRQn                  = 10,     
  DMA1_Channel1_IRQn          = 11,     
  DMA1_Channel2_IRQn          = 12,     
  DMA1_Channel3_IRQn          = 13,     
  DMA1_Channel4_IRQn          = 14,     
  DMA1_Channel5_IRQn          = 15,     
  DMA1_Channel6_IRQn          = 16,     
  DMA1_Channel7_IRQn          = 17,     
  ADC1_2_IRQn                 = 18,     
  USB_HP_CAN1_TX_IRQn         = 19,     
  USB_LP_CAN1_RX0_IRQn        = 20,     
  CAN1_RX1_IRQn               = 21,     
  CAN1_SCE_IRQn               = 22,     
  EXTI9_5_IRQn                = 23,     
  TIM1_BRK_IRQn               = 24,     
  TIM1_UP_IRQn                = 25,     
  TIM1_TRG_COM_IRQn           = 26,     
  TIM1_CC_IRQn                = 27,     
  TIM2_IRQn                   = 28,     
  TIM3_IRQn                   = 29,     
  TIM4_IRQn                   = 30,     
  I2C1_EV_IRQn                = 31,     
  I2C1_ER_IRQn                = 32,     
  I2C2_EV_IRQn                = 33,     
  I2C2_ER_IRQn                = 34,     
  SPI1_IRQn                   = 35,     
  SPI2_IRQn                   = 36,     
  USART1_IRQn                 = 37,     
  USART2_IRQn                 = 38,     
  USART3_IRQn                 = 39,     
  EXTI15_10_IRQn              = 40,     
  RTC_Alarm_IRQn              = 41,     
  USBWakeUp_IRQn              = 42,
  TIM8_BRK_IRQn               = 43,
  TIM8_UP_IRQn                = 44,
  TIM8_TRG_COM_IRQn           = 45,
  TIM8_CC_IRQn                = 46,
  ADC3_IRQn                   = 47,
  FSMC_IRQn                   = 48,
  SDIO_IRQn                   = 49,
  TIM5_IRQn                   = 50, 
  SPI3_IRQn                   = 51,
  USART4_IRQn                 = 52,
  USART5_IRQn                 = 53, 
  TIM6_IRQn                   = 54,
  TIM7_IRQn                   = 55,
  DMA_CHANNEL1_IRQn           = 56,
  DMA_CHANNEL2_IRQn           = 57,
  DMA_CHANNEL3_IRQn           = 58,
  DMA_CHANNEL4_IRQn           = 59
} IRQn_Type;

/********** STRUCTURES *******************************************************/

typedef struct nvic_tag
{
  volatile uint32 ISER0;
  volatile uint32 ISER1;
  volatile uint32 ISER2;
}NVIC_Type;

/********** External APIs ****************************************************/

extern void NVIC_EnableIRQ(IRQn_Type IRQn);
extern void Enable_Irq(void);
extern void Disable_Irq(void);

#endif /* End of _NVIC_H_ */
