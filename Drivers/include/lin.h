/******************************************************************************
* FILENAME : lin.h
* DESCRIPTION : Header file of Lin contains Lin function prototypes, macros
                structures, enums
* AUTHOR : Hammad
******************************************************************************/

#ifndef _LIN_H_
#define _LIN_H_

/********** Includes *********************************************************/

#include "std_types.h"
#include "uart.h"

/********** Data Types *******************************************************/

typedef uint8  Lin_FramePidType;
typedef uint8  Lin_FrameDlType;
typedef uint8  Std_ReturnType;

/********** Macros ***********************************************************/

#define SYNC        (0x55U)
#define LINEN       (0x4000U)
#define SBK         (0x01U)
#define NULL        (0x00U)
#define E_OK        ((Std_ReturnType)0x00U)
#define E_NOT_OK    ((Std_ReturnType)0x01U)

/********** ENUMS ************************************************************/

typedef enum
{
    LIN_ENHANCED_CS,
    LIN_CLASSIC_CS
} Lin_FrameCsModelType;

typedef enum
{
    LIN_MASTER_RESPONSE,
    LIN_SLAVE_RESPONSE,
    LIN_SLAVE_TO_SLAVE
} Lin_FrameResponseType;


typedef enum
{
  BAUD_RATE_9600 = 0x0341U,
  BAUD_RATE_115200 = 0x0045U
} Lin_BaudrateType;

typedef enum
{
    LIN_1,
    LIN_2,
    LIN_3,
    INVALID_CHANNEL
} Lin_ChannelType;

/********** STRUCTURES *******************************************************/

typedef struct Lin_PduType
{
    Lin_FramePidType        pid;
    Lin_FrameCsModelType    Cs;
    Lin_FrameResponseType   Drc;
    Lin_FrameDlType         Dl;
    uint8*                  SduPtr;
} Lin_PduType;


typedef struct
{
	uint8 Storage[12];
	uint8 Size;
	uint8 TxCount;
} Lin_VarType;

/********** External APIs ****************************************************/

extern void Lin_Init (Lin_ChannelType lin, Lin_BaudrateType baud);
extern Std_ReturnType Lin_SendFrame (uint8 channel, const Lin_PduType *PduInfoPtr);

#endif






