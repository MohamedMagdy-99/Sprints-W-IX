/*****************************************************************************
* Module: Uart Module
* File Name: Uart.h
* Description: Header file for UART Module
* Author: Mohamed Magdy
* Date: 19-July-2021
******************************************************************************/

#ifndef UART_H_
#define UART_H_


/* INCLUDES */

#include "Std_Types.h"
#include "Common_Macros.h"
#include "Uart_Regs.h"
#include "Uart_Cfg.h"
#include "InterruptsHandler_Interface.h"

/* CONSTANTS */
#define END_OF_STRING '\0'
#define NEW_LINE	  '\r'
#define BACK_SPACE	  '\b'
/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void (*pfUart_CallBack_t)(void);

/*- ENUMS --------------------------------------------------*/
typedef enum
{
UART_STATUS_ERROR_NOK,
UART_STATUS_ERROR_OK

}enuUart_Status_t;

typedef enum
{
UART_INITIALIZED,
UART_NOT_INITIALIZED
}enuUart_initStatus_t;



/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t u8_parity;
	uint8_t u8_stopBits;
	uint8_t u8_dataSize;
	uint32_t u32_baudRate;
	uint8_t u8_uartRate; 
}strUart_Config_t;

/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/
enuUart_Status_t Uart_init(void);
enuUart_Status_t Uart_syncTransmit_oneFrame(uint8_t u8_TxData);
enuUart_Status_t Uart_syncReceive_oneFrame(uint8_t* u8_RxData);

enuUart_Status_t Uart_syncTransmit_array(uint8_t* u8_TxArray, uint16_t u16_arraySize);
enuUart_Status_t Uart_syncTransmit_string(uint8_t* u8_TxString);

enuUart_Status_t Uart_syncReceive_string_vTerminal(uint8_t* u8_RxString);

void setUartRxCallback(pfUart_CallBack_t FunToBeCalledInISR);

Std_ReturnType Uart_EnableNotification_BCM(uint8_t uartChannel);
Std_ReturnType Uart_DisableNotification_BCM(uint8_t uartChannel);
Std_ReturnType UartRead_BCM(uint8_t uartChannel, uint8_t* bufferValue);

/* configuration variable */
extern strUart_Config_t strUart_Config;

#endif /* UART_H_ */