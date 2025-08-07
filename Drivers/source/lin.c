/*============================== (c) 2025 ===================================
** File Name   :  lin.c
** Author      :  Hammad
** Created on  :  Aug 08, 2025
*---------------------------------------------------------------------------*
** Description : Implements LIN (Local Interconnect Network) driver functions.
**               Provides initialization, frame transmission, checksum
**               calculation, and interrupt handling for LIN communication
**               over UART.
=============================================================================*/

/*=============================================================================
**                                 Includes
=============================================================================*/
#include "lin.h"
#include "uart.h"
#include "nvic.h"
#include "std_types.h"

/*=============================================================================
**                             External Variables
=============================================================================*/
extern Uart_RegisterType * UartChannels[];  // UART channel register pointers
extern uint8 Data_Receiver[];               // Global LIN data receive buffer

/*=============================================================================
**                             Local Variables
=============================================================================*/
static uint8 Check_Sum = 0U;          // Stores last calculated checksum
static uint8 Data_Receive = 0U;       // Data receive index counter
static uint8 Transmission_Flag = 0U;  // Indicates ongoing LIN frame transmission

/*=============================================================================
**                      Private Function Prototypes
=============================================================================*/
static uint8 Calculate_CheckSum (const Lin_PduType* PduInfoPtr);
static void Lin_SendBreak (Lin_ChannelType lin);

/*=============================================================================
**                             Global Variables
=============================================================================*/
Lin_VarType Lin_Frame; // Stores current LIN frame data for transmission

/*=============================================================================
**                             Public Functions
=============================================================================*/

/******************************************************************************
** Function Name  : Lin_Init
** Description    : Initializes LIN communication on the given UART channel
**                  and enables LIN mode in the hardware control register.
** Input          : lin  (Lin_ChannelType)  - LIN channel ID
**                  baud (Lin_BaudrateType) - Desired baud rate
** Output         : None
** Return         : None
******************************************************************************/
void Lin_Init (const Lin_ChannelType lin, const Lin_BaudrateType baud)
{
    Usart_Init (USART3_EN, lin, baud, USART3_IRQn);
    UartChannels[lin]->CR2 |= LINEN; // Enable LIN mode
}

/******************************************************************************
** Function Name  : Lin_SendFrame
** Description    : Prepares and sends a LIN frame over the specified channel.
**                  Handles both MASTER_RESPONSE and SLAVE_RESPONSE modes.
**                  Adds SYNC, PID, data bytes, and checksum as required.
** Input          : channel    (uint8)         - LIN channel number
**                  PduInfoPtr (Lin_PduType*)  - Pointer to LIN PDU structure
** Output         : None
** Return         : Std_ReturnType (E_OK or E_NOT_OK)
******************************************************************************/
Std_ReturnType Lin_SendFrame (uint8 channel, const Lin_PduType *PduInfoPtr)
{
    Std_ReturnType ret = E_OK;
    if ((channel < INVALID_CHANNEL) && (PduInfoPtr != (void *)NULL))
    {
        Lin_Frame.TxCount = 0U;
        Lin_Frame.Size = 0U;

        /* Master Response Frame */
        if (PduInfoPtr->Drc == LIN_MASTER_RESPONSE)
        {
            Lin_Frame.Storage[Lin_Frame.Size++] = SYNC;
            Lin_Frame.Storage[Lin_Frame.Size++] = PduInfoPtr->pid;

            for (uint8 DataLength = 0; DataLength < PduInfoPtr->Dl; DataLength++)
            {
                Lin_Frame.Storage[Lin_Frame.Size++] = PduInfoPtr->SduPtr[DataLength];
            }

            Check_Sum = Calculate_CheckSum(PduInfoPtr);
            Lin_Frame.Storage[Lin_Frame.Size++] = Check_Sum;
        }

        /* Slave Response Frame */
        if (PduInfoPtr->Drc == LIN_SLAVE_RESPONSE)
        {
            for (uint8 DataLength = 0; DataLength < PduInfoPtr->Dl; DataLength++)
            {
                Lin_Frame.Storage[Lin_Frame.Size++] = PduInfoPtr->SduPtr[DataLength];
            }

            Check_Sum = Calculate_CheckSum(PduInfoPtr);
            Lin_Frame.Storage[Lin_Frame.Size++] = Check_Sum;
        }

        /* Send Break Field */
        Lin_SendBreak(channel);

        Transmission_Flag = HIGH;
    }
    else
    {
        ret = E_NOT_OK;
    }

    return ret;
}

/******************************************************************************
** Function Name  : USART3_IRQHandler
** Description    : Interrupt handler for USART3 (LIN channel).
**                  - On TX complete: sends next byte if transmission ongoing.
**                  - On RX: stores received byte into Data_Receiver buffer.
** Input          : None (hardware ISR)
** Output         : None
** Return         : None
******************************************************************************/
void USART3_IRQHandler(void)
{
    /* Transmission Complete Interrupt */
    if (UartChannels[UART_3]->SR & STATUS_TX_COMPLETE)
    {
        if (Transmission_Flag == HIGH)
        {
            if (Lin_Frame.TxCount < Lin_Frame.Size)
            {
                Usart_SendByte(UART_3, Lin_Frame.Storage[Lin_Frame.TxCount]);
                Lin_Frame.TxCount++;
            }
        }

        /* Clear TX complete flag */
        UartChannels[UART_3]->SR &= ~(STATUS_TX_COMPLETE);
    }

    /* Receive Interrupt */
    if (UartChannels[UART_3]->SR & STATUS_RX)
    {
        Data_Receiver[Data_Receive++] = Usart_ReceiveByte(UART_3);
    }
}

/*=============================================================================
**                             Private Functions
=============================================================================*/

/******************************************************************************
** Function Name  : Lin_SendBreak
** Description    : Sends a LIN break field on the given channel.
** Input          : lin (Lin_ChannelType) - LIN channel ID
** Output         : None
** Return         : None
******************************************************************************/
static void Lin_SendBreak (Lin_ChannelType lin)
{
    UartChannels[lin]->CR1 |= SBK;
}

/******************************************************************************
** Function Name  : Calculate_CheckSum
** Description    : Calculates checksum for a LIN frame using either
**                  classic checksum or enhanced checksum method.
** Input          : PduInfoPtr (const Lin_PduType*) - Pointer to PDU structure
** Output         : None
** Return         : uint8 (calculated checksum)
******************************************************************************/
static uint8 Calculate_CheckSum (const Lin_PduType* PduInfoPtr)
{
    uint16 sum = 0U;
    uint16 check_sum = 0U;

    /* Sum all data bytes */
    for (uint8 datalength = 0; datalength < PduInfoPtr->Dl; datalength++)
    {
        sum = sum + PduInfoPtr->SduPtr[datalength];

        if (sum >= 0x100U)
        {
            sum = sum - 0xFFU;
        }
    }

    /* Classic checksum */
    if (PduInfoPtr->Cs == LIN_CLASSIC_CS)
    {
        return sum;
    }
    else
    {
        /* Enhanced checksum includes PID */
        check_sum = sum + PduInfoPtr->pid;

        if (check_sum >= 0x100U)
        {
            check_sum = check_sum - 0xFFU;
        }

        check_sum = ~(check_sum);

        return check_sum;
    }
}
