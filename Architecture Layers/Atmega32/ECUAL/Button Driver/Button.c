/*****************************************************************************
* Module: Button Module
* File Name: Button.c
* Description: Source file for Button Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Button.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_button_state[BUTTONS_USED];
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuBttn_Status_t errButton_Status[BUTTONS_USED];
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuBttn_Status_t
* Description: initialized the modules used by the button module
************************************************************************************/
enuBttn_Status_t Button_init(void)
{
	Dio_init();
	return BTTN_STATUS_ERROR_OK;
}
/************************************************************************************
* Parameters (in): Button ID and pointer to variable to hold the state
* Parameters (out): Error Status
* Return value: enuBttn_Status_t
* Description: gets the state of a given button pressed or released
************************************************************************************/
enuBttn_Status_t Button_getState(uint8_t u8_bttnID, uint8_t * pu8_state)
{
	*pu8_state = gu8_button_state[u8_bttnID];
	return BTTN_STATUS_ERROR_OK;
}

/************************************************************************************
* Parameters (in): Button ID 
* Parameters (out): Error Status
* Return value: enuBttn_Status_t
* Description: updates the current state of a given button
************************************************************************************/
enuBttn_Status_t Button_updateState(uint8_t u8_bttnID)
{
   	 
	 uint16_t u16_Delay = Initial_Value;
	 uint8_t buttonState_temp = Initial_Value; 
		
	 Dio_readPin(u8_bttnID, &buttonState_temp);
	 
	 if(buttonState_temp == BUTTON_STATE_PRESSED)
	 {
		 
		 //delay for debounce check
		 for(u16_Delay = Initial_Value; u16_Delay < 3000; u16_Delay++);
		 
		  Dio_readPin(u8_bttnID, &buttonState_temp);
		  
		 if(buttonState_temp == BUTTON_STATE_PRESSED)
		 {
			 gu8_button_state[u8_bttnID] = BUTTON_STATE_PRESSED;
		 }
	 }
	 else if(buttonState_temp == BUTTON_STATE_RELEASED)
	 {
		 //delay for debounce check
		 for(u16_Delay = Initial_Value; u16_Delay < 3000; u16_Delay++);
		 
		 Dio_readPin(u8_bttnID, &buttonState_temp);
		  
		 if(buttonState_temp == BUTTON_STATE_RELEASED)
		 {
			 gu8_button_state[u8_bttnID] = BUTTON_STATE_RELEASED;
		 } 
		 
	 }
	 else
	 {
		 return BTTN_STATUS_ERROR_NOK;
	 }
	 
	 return BTTN_STATUS_ERROR_OK;
}




