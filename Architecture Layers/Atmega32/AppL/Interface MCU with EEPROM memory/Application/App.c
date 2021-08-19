/*****************************************************************************
* Module: App Module
* File Name: App.c
* Description: Source file for App Module
* Author: Mohamed Magdy
* Date: 23-July-2021
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
	Uart_init();
	Eeprom_24_init();

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
	uint8_t au8_uartRX_data[6];
	uint8_t u8_loopCounter = Initial_Value;
	uint16_t u16_Sum = Initial_Value;
	uint8_t u8_tempAddress[4];
	uint8_t u8_tempData[2];
	uint8_t u8_address_data_Counter = Initial_Value;
	
	uint16_t u16_Location = Initial_Value;
	uint8_t u8_Data = Initial_Value;
	
	while(TRUE)
	{
		while(TRUE)
		{
			Uart_syncReceive_oneFrame(&au8_uartRX_data[u8_loopCounter]);
			Uart_syncTransmit_oneFrame(au8_uartRX_data[u8_loopCounter]);
		
			if(au8_uartRX_data[u8_loopCounter] == '\r')
			{
				u8_loopCounter = Initial_Value;
				break;
			}
			u16_Sum += 	au8_uartRX_data[u8_loopCounter];
		}
		
		switch(u16_Sum)
		{
			case(WRITE):
			{
				u16_Sum = Initial_Value;
				Uart_syncTransmit_string("Enter an 11 bit address (3 bytes) in hex followed by Enter: ");
				for(u8_address_data_Counter=Initial_Value; u8_address_data_Counter < 4; u8_address_data_Counter++)
				{
					Uart_syncReceive_oneFrame(&u8_tempAddress[u8_address_data_Counter]);
					Uart_syncTransmit_oneFrame(u8_tempAddress[u8_address_data_Counter]);					
				}
				Uart_syncTransmit_string("OK\r");
				
				Uart_syncTransmit_string("Enter a byte data (char) followed by Enter: ");
				for(u8_address_data_Counter=Initial_Value; u8_address_data_Counter < 2; u8_address_data_Counter++)
				{
					Uart_syncReceive_oneFrame(&u8_tempData[u8_address_data_Counter]);
					Uart_syncTransmit_oneFrame(u8_tempData[u8_address_data_Counter]);
				}
				/* store data in its variable */
				u8_Data = u8_tempData[0];		
				/* convert address string to decimal */
				
				u16_Location = String_3ByteHexAddress_ToDecimal(u8_tempAddress);
		
				/* store data in eeprom */
				Eeprom_24_writeByte(u16_Location, u8_Data);
				Uart_syncTransmit_string("OK\r");
				
				break;
			}
			case(READ):
			{
				u16_Sum = Initial_Value;
				Uart_syncTransmit_string("Enter an 11 bit address (3 bytes) in hex followed by Enter: ");
				for(u8_address_data_Counter=Initial_Value; u8_address_data_Counter < 4; u8_address_data_Counter++)
				{
					Uart_syncReceive_oneFrame(&u8_tempAddress[u8_address_data_Counter]);
					Uart_syncTransmit_oneFrame(u8_tempAddress[u8_address_data_Counter]);
				}
				Uart_syncTransmit_string("OK\r");

				/* convert address string to decimal */
				
				u16_Location = String_3ByteHexAddress_ToDecimal(u8_tempAddress);
				/* store data in eeprom */
				Eeprom_24_readByte(u16_Location, &u8_Data);
				Uart_syncTransmit_string("The Data Stored is: ");
				Uart_syncTransmit_oneFrame(u8_Data);
				Uart_syncTransmit_string("\r");
				break;
			}
			default:
			{
				Uart_syncTransmit_string("\rInvalid Command\r\r");
				u16_Sum = Initial_Value;
				break;
			}
		}
	}
	
	return APP_STATUS_ERROR_OK;
}
