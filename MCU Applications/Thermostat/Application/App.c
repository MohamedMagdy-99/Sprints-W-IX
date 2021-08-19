/*****************************************************************************
* Module: App Module
* File Name: App.c
* Description: Source file for App Module
* Author: Mohamed Magdy
* Date: 25-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "App.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
uint16_t gu16_milliVolts = Initial_Value;
uint8_t gu8_temperature = Initial_Value;
uint8_t gu8_thresholdTemperature = Initial_Value;
uint8_t gu8_pressedKey = NO_KEY_PRESSED;
uint8_t gau8_tempString[3];
uint8_t gu8_tempStringIndex = Initial_Value;
uint8_t gu8_cursorOffset = Initial_Value;
uint8_t gu8_backSpaceFlag = Initial_Value;
uint8_t gu8_firstStartFlag = Initial_Value;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
enuApp_Status_t App_Init(void)
{
	Dio_init();
	Lm35_init();
	Keypad_init();
	Lcd_init();
	
	Lcd_sendString("SetTemp:");
	Lcd_cursorPosition(2,1);
	Lcd_sendString("Fan:OFF");
	
	return APP_STATUS_ERROR_OK;
}
 enuApp_Status_t App_Update(void)
 {
		gu8_backSpaceFlag = Initial_Value;
		
		Lm35_getTemp(ADC0_ID, &gu16_milliVolts, &gu8_temperature);	
		
     	KeypadScan(&gu8_pressedKey);
     	if(gu8_pressedKey != NO_KEY_PRESSED)
     	{
			 if(gu8_pressedKey == '-')
			 {
				 gu8_tempStringIndex--;
				 Lcd_cursorPosition(1,9+(gu8_cursorOffset-1));
				 Lcd_sendCharacter(' ');
				 gu8_backSpaceFlag = 1;
				 gu8_cursorOffset--;
			 }
			 Lcd_cursorPosition(1,9+gu8_cursorOffset);
			 
     		if(gu8_pressedKey == '=') 
     		{
				gu8_firstStartFlag = 1;
     			gau8_tempString[gu8_tempStringIndex] = '\0';
				 				 
				Lcd_cursorPosition(1,9);
				Lcd_sendString("  ");
				
				Lcd_cursorPosition(2,10);
				Lcd_sendString("Temp:");
				Lcd_sendString(gau8_tempString);
				
     			gu8_tempStringIndex= Initial_Value;
				gu8_cursorOffset = Initial_Value;
				 
     			/* convert string to integer and store in gu8_thresholdTemperature */
				 stringToInteger(gau8_tempString, &gu8_thresholdTemperature);	
     		}
     		else
     		{
				 if(gu8_tempStringIndex > 1 && gu8_backSpaceFlag == Initial_Value)
				 {
					Lcd_cursorPosition(1,9);
					gau8_tempString[0] = '9';
					gau8_tempString[1] = '9';
					Lcd_sendString("99");
					gu8_tempStringIndex = 2;
					
				 }
				 else if(gu8_backSpaceFlag == Initial_Value)
				 {
					gau8_tempString[gu8_tempStringIndex] = gu8_pressedKey;
					gu8_tempStringIndex++;
					Lcd_sendCharacter(gu8_pressedKey);
					gu8_cursorOffset++;
				 }

     		}
     		
     	}
     	
     	
     	if(gu8_temperature > gu8_thresholdTemperature && gu8_firstStartFlag == 1)
     	{
     		Dio_writePin(PORTD_PIN7_ID, STD_HIGH);
			Lcd_cursorPosition(2,7);
			Lcd_sendCharacter(' ');
			Lcd_cursorPosition(2,5);
			Lcd_sendString("ON");
     	}
     	else if(gu8_firstStartFlag == 1)
     	{
     		Dio_writePin(PORTD_PIN7_ID, STD_LOW);
			Lcd_cursorPosition(2,5);
			Lcd_sendString("OFF");			 
     	}
     	
 	return APP_STATUS_ERROR_OK;
 }
