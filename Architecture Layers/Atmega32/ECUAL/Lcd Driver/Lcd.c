/*****************************************************************************
* Module: Lcd Module
* File Name: Lcd.c
* Description: Source file for Lcd Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Lcd.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuLcd_Status_t Lcd_Status = LCD_STATUS_ERROR_OK;
enuLcd_initStatus_t Lcd_Init = LCD_NOT_INITIALIZED;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

enuLcd_Status_t Lcd_toggleEnable(void)
{
	Dio_writePin(EN_DIO_ID, STD_HIGH);		//set enable ON	
	Delay_ms(1);		
	Dio_writePin(EN_DIO_ID, STD_LOW);		//set enable OFF
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendData_4bitMode(uint8_t u8_data)
{
	Lcd_sendHigherNibble(u8_data);							//send higher nibble
	Lcd_toggleEnable();		//toggle enable
	
	Delay_ms(1);
	
	Lcd_sendLowerNibble(u8_data);							//send lower nibble
	Lcd_toggleEnable();		//toggle enable
	
	Delay_ms(2);
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendCommand(uint8_t u8_command)
{

	Dio_writePin(RS_DIO_ID, STD_LOW);			//activate command mode
	
	Lcd_sendData_4bitMode(u8_command);
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendCharacter(uint8_t u8_char)
{

	Dio_writePin(RS_DIO_ID, STD_HIGH);		//activate DATA mode

	Lcd_sendData_4bitMode(u8_char);
	
	return LCD_STATUS_ERROR_OK;
}



enuLcd_Status_t Lcd_sendString(uint8_t* au8_string)
{
	uint8_t u8_loopCounter = Initial_Value;
	for (u8_loopCounter=Initial_Value;au8_string[u8_loopCounter]!='\0';u8_loopCounter++)
	{
		Lcd_sendCharacter(au8_string[u8_loopCounter]);
	}
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_cursorPosition(uint8_t u8_xAxis, uint8_t u8_yAxis)
{
	uint8_t au8_positions[4] = {0, 64, Lcd_Columns, Lcd_Columns+64};
		
	Lcd_sendCommand(0x80+au8_positions[u8_xAxis-1]+(u8_yAxis-1));
	
	return LCD_STATUS_ERROR_OK;
}



enuLcd_Status_t Lcd_init(void)
{
	if(Lcd_Init == LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
	
	Lcd_Init = LCD_INITIALIZED;
	
	Dio_init();
	
	Delay_ms(20);
	//Activate 4 bit mode
	Lcd_sendCommand(0x33);
	Lcd_sendCommand(0x32);
	
	//Function Set (2 lines & 5x8 font)
	Lcd_sendCommand(0x28);
	
	//Display OFF
	Lcd_sendCommand(0x08);
	
	//Clear Display
	Lcd_sendCommand(0x01);
	
	//Entry Mode Set
	Lcd_sendCommand(0x06);
	
	//Display ON
	Lcd_sendCommand(0x0C);
	
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_sendVariableInt(uint16_t u16_number, uint8_t u8_base) 
{	
	uint8_t pu8_String[6];

	integerToString(u16_number, pu8_String, u8_base);

	Lcd_sendString(pu8_String);
	
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_sendLowerNibble(uint8_t u8_data)
{
	if((u8_data & 0x01) != 0)
	{
		Dio_writePin(D4_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D4_DIO_ID, STD_LOW);
	}

	if((u8_data & 0x02) != 0)
	{
		Dio_writePin(D5_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D5_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x04) != 0)
	{
		Dio_writePin(D6_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D6_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x08) != 0)
	{
		Dio_writePin(D7_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D7_DIO_ID, STD_LOW);
	}
	
	return LCD_STATUS_ERROR_OK;			
}

enuLcd_Status_t Lcd_sendHigherNibble(uint8_t u8_data)
{
	if((u8_data & 0x10) != 0)
	{
		Dio_writePin(D4_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D4_DIO_ID, STD_LOW);
	}

	if((u8_data & 0x20) != 0)
	{
		Dio_writePin(D5_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D5_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x40) != 0)
	{
		Dio_writePin(D6_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D6_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x80) != 0)
	{
		Dio_writePin(D7_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D7_DIO_ID, STD_LOW);
	}
	
	return LCD_STATUS_ERROR_OK;
}