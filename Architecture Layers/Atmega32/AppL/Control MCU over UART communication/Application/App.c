/*****************************************************************************
* Module: App Module
* File Name: App.c
* Description: Source file for App Module
* Author: Mohamed Magdy
* Date: 20-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "App.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuApp_Status_t
* Description: initializes the system modules
************************************************************************************/
enuApp_Status_t App_Init(void)
{
	Led_init();
	Uart_init();
	return APP_STATUS_ERROR_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuApp_Status_t
* Description: main task of the system, handles all application cases
************************************************************************************/
enuApp_Status_t App_Update(void)
{
	uint8_t u8_RxData = Initial_Value;
	uint16_t u16_Sum = Initial_Value;
	uint8_t au8_RxCommand[MAX_COMMAND_CHARS];
	uint8_t u8_LoopCounter = Initial_Value;
	
	while(TRUE)
	{
		Uart_syncReceive_oneFrame(&u8_RxData);
		Uart_syncTransmit_oneFrame(u8_RxData);

		au8_RxCommand[u8_LoopCounter] = u8_RxData;
		u16_Sum += 	u8_RxData;
		++u8_LoopCounter;
		
		if(u16_Sum == START || u16_Sum == WAIT || u16_Sum == STOP || u16_Sum == AT)
		{
			u8_LoopCounter = Initial_Value;
			break;
		}
		if (u8_LoopCounter == MAX_COMMAND_CHARS-1)
		{
			u8_LoopCounter = Initial_Value;
		}
			
	}
	
	Uart_syncTransmit_oneFrame('\r');
	switch(u16_Sum)
	{
		case(START):
		{
			LedOn(GREEN_LED);
			LedOff(YELLOW_LED);
			LedOff(RED_LED);
			break;
		}
		case(WAIT):
		{
			LedOff(GREEN_LED);
			LedOn(YELLOW_LED);
			LedOff(RED_LED);
			break;
		}
		case(STOP):
		{
			LedOff(GREEN_LED);
			LedOff(YELLOW_LED);
			LedOn(RED_LED);
			break;
		}
		case(AT):
		{
			Uart_syncTransmit_array("OK", 2);
			Uart_syncTransmit_oneFrame('\r');
			break;
		}
		default: return APP_STATUS_ERROR_NOK;						
	}
	
	
	return APP_STATUS_ERROR_OK;
}
