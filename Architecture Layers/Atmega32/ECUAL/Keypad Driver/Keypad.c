/*****************************************************************************
* Module: Keypad Module
* File Name: Keypad.c
* Description: Source file for Keypad Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Keypad.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuKeypad_Status_t Keypad_Status = KEYPAD_STATUS_ERROR_OK;

const uint8_t au8_keysLayout[Number_Rows][Number_Columns]
=
{{'7','8','9','/'},
{'4','5','6','*'},
{'1','2','3','-'},
{'C','0','=','.'}};

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

enuKeypad_Status_t Keypad_init(void)
{

	Dio_init();
	return KEYPAD_STATUS_ERROR_OK;

}

enuKeypad_Status_t KeypadScan(uint8_t* u8_pressedKey)
{
	*u8_pressedKey = NO_KEY_PRESSED;
	
	uint8_t u8_row = Initial_Value;
	uint8_t u8_activeColumn = NO_KEY_PRESSED;
	uint8_t u8_columnsCounter = Initial_Value;
	uint8_t u8_columnValue = NO_KEY_PRESSED;
	uint8_t u8_breakFlag = Initial_Value;
		
	//uint8_t u8_currenlyPressedColumn = Initial_Value;
	
	//loop on rows
	for (u8_row=Initial_Value;u8_row<Number_Rows;u8_row++)
	{
		//set ROWs initially to no output state
		
		Dio_writePin(ROW_1_DIO_ID, STD_HIGH);
		Dio_writePin(ROW_2_DIO_ID, STD_HIGH);
		Dio_writePin(ROW_3_DIO_ID, STD_HIGH);
		Dio_writePin(ROW_4_DIO_ID, STD_HIGH);
		//set one of the rows to logic one each time
		switch(u8_row)
		{
			case(ROW_1):
			{
				Dio_writePin(ROW_1_DIO_ID, STD_LOW);
				Dio_writePin(ROW_2_DIO_ID, STD_HIGH);
				Dio_writePin(ROW_3_DIO_ID, STD_HIGH);
				Dio_writePin(ROW_4_DIO_ID, STD_HIGH);
				break;				
			}
			case(ROW_2):
			{
				Dio_writePin(ROW_1_DIO_ID, STD_HIGH);
				Dio_writePin(ROW_2_DIO_ID, STD_LOW);
				Dio_writePin(ROW_3_DIO_ID, STD_HIGH);
				Dio_writePin(ROW_4_DIO_ID, STD_HIGH);
				break;
			}
			case(ROW_3):
			{
				Dio_writePin(ROW_1_DIO_ID, STD_HIGH);
				Dio_writePin(ROW_2_DIO_ID, STD_HIGH);
				Dio_writePin(ROW_3_DIO_ID, STD_LOW);
				Dio_writePin(ROW_4_DIO_ID, STD_HIGH);
				break;
			}
			case(ROW_4):
			{
				Dio_writePin(ROW_1_DIO_ID, STD_HIGH);
				Dio_writePin(ROW_2_DIO_ID, STD_HIGH);
				Dio_writePin(ROW_3_DIO_ID, STD_HIGH);
				Dio_writePin(ROW_4_DIO_ID, STD_LOW);
				break;
			}
			default: break;									
		}
		//check input for each column
		for(u8_columnsCounter = Initial_Value; u8_columnsCounter < Number_Columns; u8_columnsCounter++)
		{
			switch(u8_columnsCounter)
			{
				case(COLUMN_1):
				{
					Dio_readPin(COLUMN_1_DIO_ID, &u8_columnValue);
					if(u8_columnValue == STD_LOW) 
					{
						u8_activeColumn = COLUMN_1;
						u8_breakFlag = 1;
					}
					
					break;
				}
				case(COLUMN_2):
				{
					Dio_readPin(COLUMN_2_DIO_ID, &u8_columnValue);
					if(u8_columnValue == STD_LOW) 
					{
						u8_activeColumn = COLUMN_2;
						u8_breakFlag = 1;
					}
					break;
				}
				case(COLUMN_3):
				{
					Dio_readPin(COLUMN_3_DIO_ID, &u8_columnValue);
					if(u8_columnValue == STD_LOW) 
					{
						u8_activeColumn = COLUMN_3;
						u8_breakFlag = 1;
					}
					break;
				}
				case(COLUMN_4):
				{
					Dio_readPin(COLUMN_4_DIO_ID, &u8_columnValue);
					if(u8_columnValue == STD_LOW) 
					{
						u8_activeColumn = COLUMN_4;
						u8_breakFlag = 1;
					}
					break;
				}
				default: break;
			}
			if(u8_breakFlag == 1) break;			
		}

		
		//if the input in the valid range
		if (u8_activeColumn != NO_KEY_PRESSED)
		{
			/*wait for some delay or check for all o/p pins are 1s button no longer pressed */
			Delay_ms(220);
			//map the input to the global array
			*u8_pressedKey = au8_keysLayout[u8_row][u8_activeColumn];
			break;	
		}
	}
	
	
	return KEYPAD_STATUS_ERROR_OK;
}

