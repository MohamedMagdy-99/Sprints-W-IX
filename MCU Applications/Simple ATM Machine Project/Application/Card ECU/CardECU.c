/*****************************************************************************
* Module: Card Module
* File Name: CardECU.c
* Description: Source file for Card Module
* Author: Mohamed Magdy
* Date: 27-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "CardECU.h"
#include "../MCAL/Interrupt Driver/ISR.h"
#include "../Microcontroller/Utility Module/Utility.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuCard_Mode_t enuCardMode = CARD_IDLE_MODE;
uint8_t u8_EepromFlagValue = Initial_Value;
uint8_t gau8_userPAN[PAN_SIZE];
uint8_t gau8_userPIN[PIN_SIZE_ARR];
uint8_t gau8_userMode[USER_MODE_MAX];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/


/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuCar_Status_t
* Description: initializes the car module by initializing the modules used in it
************************************************************************************/
enuCard_Status_t Card_Init(void)
{
	Dio_init();
	Uart_init();
	Uart_syncTransmit_string("Card Terminal\r**************\r");
	Spi_init();
	Eeprom_24_init();
	
	EnableExternalInterrupts_INT0(LOW_LEVEL);
	setExtINT0Callback(FunctionWhenATM_WantsCardData);
	/* check if card data is available */
	Eeprom_24_readByte(EepromFlagAddress, &u8_EepromFlagValue);
	if(u8_EepromFlagValue == EpromEmpty)
	{
		Uart_syncTransmit_string("This card has no data, you will be directed to programing mode.\r\r");
		enuCardMode = CARD_PROGRAMMING_MODE;
	}
	else
	{
		/* read the data again from eeprom to update variables */
		Eeprom_24_readPacket(PanAddress, gau8_userPAN, PAN_SIZE);
		Eeprom_24_readPacket(PinAddress, gau8_userPIN, PIN_SIZE_EE);
		enuCardMode = CARD_USER_MODE;
	}
	return CARD_STATUS_ERROR_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuCar_Status_t
* Description: main task of the control system, handles all application cases
************************************************************************************/
enuCard_Status_t Card_Update(void)
{
	
	/**************************************************************************************************/
	/*********************************** PROGRAMMING MODE *********************************************/
	/**************************************************************************************************/
	
	if(enuCardMode == CARD_PROGRAMMING_MODE || enuCardMode == CARD_IDLE_MODE)
	{
			Uart_syncTransmit_string("\rNow you are in Programming mode\r\r");
			
			/* saving the PAN */
			Uart_syncTransmit_string("Please enter your PAN: ");
			getPAN();
			if(enuCardMode == CARD_USER_MODE)
			{
				return CARD_STATUS_ERROR_OK;
			}
			/* send PAN to EEPROM */
			Eeprom_24_writePacket(PanAddress, gau8_userPAN, PAN_SIZE);
			/*********************************************************************************/
			/* saving the PIN */
			Uart_syncTransmit_string("Please enter your PIN: ");
			getPIN();
			if(enuCardMode == CARD_USER_MODE)
			{
				return CARD_STATUS_ERROR_OK;
			}
			/* send PAN to EEPROM */
			Eeprom_24_writePacket(PinAddress, gau8_userPIN, PIN_SIZE_EE);	
			
			/* saving data is done, switch to user mode and changing eeprom flag to has data */	
			Eeprom_24_writeByte(EepromFlagAddress, EepromHasData);
			enuCardMode = CARD_USER_MODE;
			
			Uart_syncTransmit_string("\rYour card has been programmed successfully!\rYou will now be directed to USER mode\r");
		}
	
	/**************************************************************************************************/
	/*********************************** USER MODE ****************************************************/
	/**************************************************************************************************/
	
	else
	{
		Uart_syncTransmit_string("\rNow you are in User Mode\r");
		/* check if user wanted to go to Programming mode */
		getMode_userModeVersion();
		return CARD_STATUS_ERROR_OK;
	}
	
	return CARD_STATUS_ERROR_OK;
}



















enuCard_Status_t getMode_userModeVersion(void)
{
	while(TRUE)
	{
		Uart_syncTransmit_string("\rWaiting for transaction processing...\r");
		Uart_syncTransmit_string("You can go to admin mode by typing ADMIN\r\r");
		
		uint8_t u8_loopCounter = Initial_Value;
		
		for(u8_loopCounter = Initial_Value; u8_loopCounter < USER_MODE_MAX; u8_loopCounter++)
		{
			Uart_syncReceive_oneFrame(&gau8_userMode[u8_loopCounter]);


			if(gau8_userMode[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
			{
				Uart_syncTransmit_oneFrame(gau8_userMode[u8_loopCounter]);
				u8_loopCounter-=2;
			}
			else if(gau8_userMode[u8_loopCounter] == NEW_LINE)
			{
				Uart_syncTransmit_oneFrame(gau8_userMode[u8_loopCounter]);
				gau8_userMode[u8_loopCounter] = END_OF_STRING;
				if(stringCmp(gau8_userMode, "ADMIN") == TRUE)
				{
					enuCardMode = CARD_PROGRAMMING_MODE;

					return CARD_STATUS_ERROR_OK;
				}
				else if(stringCmp(gau8_userMode, "USER") == TRUE)
				{
					Uart_syncTransmit_string("You are already in USER mode\r\r");
					u8_loopCounter = USER_MODE_MAX;
				}
				else
				{
					Uart_syncTransmit_string("Please enter a correct choice.\r\r");
					u8_loopCounter = USER_MODE_MAX;
				}
			}
			else if(gau8_userMode[u8_loopCounter] != BACK_SPACE)
			{
				Uart_syncTransmit_oneFrame(gau8_userMode[u8_loopCounter]);
			}
			else
			{
				u8_loopCounter--;
			}
		}
	}
	return CARD_STATUS_ERROR_OK;
}








enuCard_Status_t getPAN(void)
{
	uint8_t u8_loopCounter = Initial_Value;
	for(u8_loopCounter = Initial_Value; u8_loopCounter < PAN_SIZE; u8_loopCounter++)
	{
		Uart_syncReceive_oneFrame(&gau8_userPAN[u8_loopCounter]);
		

		if(gau8_userPAN[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
		{
			Uart_syncTransmit_oneFrame(gau8_userPAN[u8_loopCounter]);
			u8_loopCounter-=2;
		}
		else if(gau8_userPAN[u8_loopCounter] == NEW_LINE)
		{
			Uart_syncTransmit_oneFrame(gau8_userPAN[u8_loopCounter]);
			gau8_userPAN[u8_loopCounter] = END_OF_STRING;
			if(stringCmp(gau8_userPAN, "USER") == TRUE)
			{
				enuCardMode = CARD_USER_MODE;

				return CARD_STATUS_ERROR_OK;
			}
			else
			{
				enuCardMode = CARD_PROGRAMMING_MODE;
				return CARD_STATUS_ERROR_OK;
			}
		}
		else if(gau8_userPAN[u8_loopCounter] != BACK_SPACE)
		{
			Uart_syncTransmit_oneFrame(gau8_userPAN[u8_loopCounter]);
		}
		else
		{
			u8_loopCounter--;
		}		
	}
	return CARD_STATUS_ERROR_NOK;
}


enuCard_Status_t getPIN(void)
{
	uint8_t u8_loopCounter = Initial_Value;
	for(u8_loopCounter = Initial_Value; u8_loopCounter < PIN_SIZE_ARR; u8_loopCounter++)
	{
		Uart_syncReceive_oneFrame(&gau8_userPIN[u8_loopCounter]);
		
		if(gau8_userPIN[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
		{
			Uart_syncTransmit_oneFrame(gau8_userPIN[u8_loopCounter]);
			u8_loopCounter-=2;
		}
		else if(gau8_userPIN[u8_loopCounter] == NEW_LINE)
		{
			Uart_syncTransmit_oneFrame(NEW_LINE);
			gau8_userPIN[u8_loopCounter] = END_OF_STRING;
			if(stringCmp(gau8_userPIN, "USER") == TRUE)
			{
				enuCardMode = CARD_USER_MODE;
				return CARD_STATUS_ERROR_OK;
			}
			else
			{
				enuCardMode = CARD_PROGRAMMING_MODE;
				return CARD_STATUS_ERROR_OK;
			}
		}
		else if(gau8_userPIN[u8_loopCounter] != BACK_SPACE)
		{
			Uart_syncTransmit_oneFrame('*');
		}
		else
		{
			u8_loopCounter--;
		}
	}
	return CARD_STATUS_ERROR_NOK;
}

/* function to be called from external interrupt 0 ISR */
void FunctionWhenATM_WantsCardData(void)
{	
	/* check if card has data */
	if(u8_EepromFlagValue == EepromHasData)
	{
		/* transmit card data to ATM ecu */
		Spi_MasterTransmit_array(gau8_userPAN, PAN_SIZE);
		Spi_MasterTransmit_array(gau8_userPIN, PIN_SIZE_EE);		
	}
	else
	{
		Uart_syncTransmit_string("Card is not programmed yet!\r");
	}
	
}
