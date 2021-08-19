/*****************************************************************************
* Module: Uart Module
* File Name: Uart.c
* Description: Source file for UART Module
* Author: Mohamed Magdy
* Date: 19-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Uart.h"
/*- BLOBAL STATIC VARIABLES
-------------------------------*/
static pfUart_CallBack_t UartRxCallback;
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuUart_Status_t Uart_Status = UART_STATUS_ERROR_OK;
enuUart_initStatus_t Uart_Init = UART_NOT_INITIALIZED;
uint16_t gu16_baudRateRegisterValue = Initial_Value;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: initialize Uart module according to the cfg file
******************************************************************************************/
enuUart_Status_t Uart_init(void)
{
	if(Uart_Init == UART_INITIALIZED) return UART_STATUS_ERROR_NOK;
	
	Uart_Init = UART_INITIALIZED;
	/*******************************************************************/
	switch(strUart_Config.u8_uartRate)
	{
		case(SINGLE_RATE):
		{
			CLEAR_BIT(UCSRA_R, U2X_B);
			
			gu16_baudRateRegisterValue = (uint16_t)((UART_FREQ/(16*(strUart_Config.u32_baudRate))) - 1);
			break;
		}
		case(DOUBLE_RATE):
		{
			SET_BIT(UCSRA_R, U2X_B);
			gu16_baudRateRegisterValue = (uint16_t)((UART_FREQ/(8*(strUart_Config.u32_baudRate))) - 1);
			break;
		}
		default: return UART_STATUS_ERROR_NOK;
	}
	
	/*******************************************************************/
	/* setting the baud rate register */
	CLEAR_BIT(UCSRC_R, URSEL_B);
	UBRRH_R = (uint8_t)(gu16_baudRateRegisterValue>>8);  //send the high 4 bits of the UBRR
	UBRRL_R = (uint8_t)(gu16_baudRateRegisterValue) ;    //send the low  8 bits of the UBRR
	
	/*******************************************************************/
	switch(strUart_Config.u8_stopBits)
	{
		case(ONE_STOP_BIT):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			CLEAR_BIT(UCSRC_R, USBS_B);
			break;
		}
		case(TWO_STOP_BIT):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			SET_BIT(UCSRC_R, USBS_B);
			break;
		}
		default: return UART_STATUS_ERROR_NOK;
	}
	/*******************************************************************/
	switch(strUart_Config.u8_dataSize)
	{
		case(DATA_5BITS):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			CLEAR_BIT(UCSRB_R, UCSZ2_B);
			CLEAR_BIT(UCSRC_R, UCSZ1_B);
			CLEAR_BIT(UCSRC_R, UCSZ0_B);
			
			break;
		}
		case(DATA_6BITS):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			CLEAR_BIT(UCSRB_R, UCSZ2_B);
			CLEAR_BIT(UCSRC_R, UCSZ1_B);
			SET_BIT(UCSRC_R, UCSZ0_B);
			
			break;
		}
		case(DATA_7BITS):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			CLEAR_BIT(UCSRB_R, UCSZ2_B);
			SET_BIT(UCSRC_R, UCSZ1_B);
			CLEAR_BIT(UCSRC_R, UCSZ0_B);
			break;
		}
		case(DATA_8BITS):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			CLEAR_BIT(UCSRB_R, UCSZ2_B);
			SET_BIT(UCSRC_R, UCSZ1_B);
			SET_BIT(UCSRC_R, UCSZ0_B);
			break;
		}
		case(DATA_9BITS):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			SET_BIT(UCSRB_R, UCSZ2_B);
			SET_BIT(UCSRC_R, UCSZ1_B);
			SET_BIT(UCSRC_R, UCSZ0_B);
			break;
		}
		default: return UART_STATUS_ERROR_NOK;
	}
	/*******************************************************************/
	switch(strUart_Config.u8_parity)
	{
		case(NO_PARITY):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			CLEAR_BIT(UCSRC_R, UPM0_B);
			CLEAR_BIT(UCSRC_R, UPM1_B);
			break;
		}
		case(ODD_PARITY):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			SET_BIT(UCSRC_R, UPM0_B);
			SET_BIT(UCSRC_R, UPM1_B);
			break;
		}
		case(EVEN_PARTIY):
		{
			SET_BIT(UCSRC_R, URSEL_B);
			CLEAR_BIT(UCSRC_R, UPM0_B);
			SET_BIT(UCSRC_R, UPM1_B);
			break;
		}
		default: return UART_STATUS_ERROR_NOK;
	}

	
	/*******************************************************************/
	/* enable transmission and reception */
	
	SET_BIT(UCSRB_R, TXEN_B);
	SET_BIT(UCSRB_R, RXEN_B);
	
	return UART_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): Data to be transmitted
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: uart transmits one frame through TX pin
******************************************************************************************/
enuUart_Status_t Uart_syncTransmit_oneFrame(uint8_t u8_TxData)
{
	while(BIT_IS_CLEAR(UCSRA_R, UDRE_B));

	UDR_R = u8_TxData;
	return UART_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): pointer to data which will be received 
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: uart receives one frame through RX pin
******************************************************************************************/
enuUart_Status_t Uart_syncReceive_oneFrame(uint8_t* u8_RxData)
{
	while(BIT_IS_CLEAR(UCSRA_R, RXC_B));

	*u8_RxData = UDR_R;
	return UART_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): pointer to array which will be transmitted
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: uart transmits an array of data through TX
******************************************************************************************/
enuUart_Status_t Uart_syncTransmit_array(uint8_t* u8_TxArray, uint16_t u16_arraySize)
{
		uint8_t  u8_loopCounter = Initial_Value ;
		for (u8_loopCounter = Initial_Value; u8_loopCounter < u16_arraySize ; u8_loopCounter++)
		{
			Uart_syncTransmit_oneFrame(u8_TxArray[u8_loopCounter]);
		}
		return UART_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): pointer to string which will be transmitted
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: uart transmits a string through TX
******************************************************************************************/
enuUart_Status_t Uart_syncTransmit_string(uint8_t* u8_TxString)
{
	uint8_t  u8_loopCounter = Initial_Value ;
	while(u8_TxString[u8_loopCounter] != END_OF_STRING)
	{
		Uart_syncTransmit_oneFrame(u8_TxString[u8_loopCounter]);
		u8_loopCounter++;
	}
	return UART_STATUS_ERROR_OK;
}


/*****************************************************************************************
* Parameters (in): pointer to string which will be received in
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: uart receives  a string through TX
******************************************************************************************/
enuUart_Status_t Uart_syncReceive_string_vTerminal(uint8_t* u8_RxString)
{
	uint8_t  u8_loopCounter = Initial_Value ;
	while (TRUE)
	{
		Uart_syncReceive_oneFrame(&u8_RxString[u8_loopCounter]);
		Uart_syncTransmit_oneFrame(u8_RxString[u8_loopCounter]);
		if(u8_RxString[u8_loopCounter] == NEW_LINE)
		{
			u8_RxString[u8_loopCounter] = END_OF_STRING;
			break;
		}
	}
	return UART_STATUS_ERROR_OK;
}


/*****************************************************************************************
* Parameters (in): pointer to callback function
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: uart receives data using interrupts
******************************************************************************************/
enuUart_Status_t Uart_asyncReceive(pfUart_CallBack_t FunToBeCalledInISR)
{
	EnableGlobalInterrupts();
	setUartRxCallback(FunToBeCalledInISR);
	
	/* enable receiving interrupt */
	SET_BIT(UCSRB_R, RXCIE_B);	
	return UART_STATUS_ERROR_OK;
}


/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: stops uart receive interrupt
******************************************************************************************/
enuUart_Status_t Uart_asyncReceive_Stop()
{
	/* disable receiving interrupt */
	CLEAR_BIT(UCSRB_R, RXCIE_B);
	
	return UART_STATUS_ERROR_OK;
	
}
/* Interrupts */

/*****************************************************************************************
* Parameters (in): pointer to function to be called from ISR
* Parameters (out): None
* Return value: None
* Description: sets the function to be called by overflow timer ISR
******************************************************************************************/
void setUartRxCallback(pfUart_CallBack_t FunToBeCalledInISR)
{
	UartRxCallback = FunToBeCalledInISR;
	
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: interrupt service routine for uart RX
******************************************************************************************/
ISR(USART_RXC)
{

	UartRxCallback();
	
}