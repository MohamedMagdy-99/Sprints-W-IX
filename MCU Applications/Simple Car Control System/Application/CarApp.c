/*****************************************************************************
* Module: Car Module
* File Name: CarApp.c
* Description: Source file for Car Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "CarApp.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
uint8_t u8_buttonState[BUTTONS_USED];
uint8_t u8_button_G_PressCounts = Initial_Value;

sint8_t s8_currentPressed_Index = NO_BUTTON_PRESSED;
sint8_t s8_previousPressed_Index = NO_BUTTON_PRESSED;

enuCar_Status_t Car_Status = CAR_STATUS_INITIAL;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuCar_Status_t
* Description: initializes the car module by initializing the modules used in it
************************************************************************************/
enuCar_Status_t Car_Init(void)
{
   Button_init();
   Motor_init();
   
   Car_Status = CAR_STATUS_INITIAL;
   
   return CAR_STATUS_ERROR_OK;	
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuCar_Status_t
* Description: main task of the control system, handles all application cases
************************************************************************************/
enuCar_Status_t Car_Update(void)
{
	
	uint8_t u8_ButtonLoop = Initial_Value;
	
	/* button checks */
	for(u8_ButtonLoop = Initial_Value; u8_ButtonLoop < BUTTONS_USED; u8_ButtonLoop++)
	{
		Button_updateState(strButton_Config[u8_ButtonLoop].u8_ButtonId);
		Button_getState(strButton_Config[u8_ButtonLoop].u8_ButtonId, &u8_buttonState[u8_ButtonLoop]);
		
		
		if(u8_buttonState[u8_ButtonLoop] == BUTTON_STATE_PRESSED)
		{
			
			s8_previousPressed_Index = s8_currentPressed_Index;
			s8_currentPressed_Index = strButton_Config[u8_ButtonLoop].u8_ButtonId;
			
		
			break;
		}
		if(u8_ButtonLoop == BUTTONS_USED - 1)
		{	
			s8_currentPressed_Index =  NO_BUTTON_PRESSED;
			s8_previousPressed_Index = NO_BUTTON_PRESSED;
		}
	}
	
	switch(s8_currentPressed_Index)
	{
		case(BUTTON_G_ID):
		{
			
			if(s8_previousPressed_Index == BUTTON_G_ID) break;
			
			if(u8_button_G_PressCounts == 4) u8_button_G_PressCounts = Initial_Value;
			++u8_button_G_PressCounts;
			switch(u8_button_G_PressCounts)
			{
				case(SPEED_30_FORWARD):
				{
					Car_Status = CAR_STATUS_SPEED_30_FW;

					break;
				}
				case(SPEED_60_FORWARD):
				{
					Car_Status = CAR_STATUS_SPEED_60_FW;
					
					break;
				}
				case(SPEED_90_FORWARD):
				{
					Car_Status = CAR_STATUS_SPEED_90_FW;
					
					break;
				}
				case(SPEED_30_BACKWARD):
				{
					Car_Status = CAR_STATUS_SPEED_30_BW;
					
					break;
				}																
			}
			
			break;
		}
		case(BUTTON_M_ID):
		{
			/* check if system is not in initial state */
			if(Car_Status == CAR_STATUS_INITIAL) break;
			
			if(s8_previousPressed_Index == BUTTON_M_ID) break;
			
			/* check Car_Status and then assign direction and speed */
			switch(Car_Status)
			{
				case(CAR_STATUS_SPEED_30_FW):
				{
					/* set the 2 motors speed 30 and direction forward */
					Motor_moveForward(MOTOR_R, SPEED_30);
					Motor_moveForward(MOTOR_L, SPEED_30);
					break;
				}
				case(CAR_STATUS_SPEED_60_FW):
				{
					/* set the 2 motors speed 60 and direction forward */
					Motor_moveForward(MOTOR_R, SPEED_60);
					Motor_moveForward(MOTOR_L, SPEED_60);
					break;
				}
				case(CAR_STATUS_SPEED_90_FW):
				{
					/* set the 2 motors speed 90 and direction forward */
					Motor_moveForward(MOTOR_R, SPEED_90);
					Motor_moveForward(MOTOR_L, SPEED_90);
					break;
				}
				case(CAR_STATUS_SPEED_30_BW):
				{
					/* set the 2 motors speed 30 and direction backward */
					Motor_moveBackward(MOTOR_R, SPEED_30);
					Motor_moveBackward(MOTOR_L, SPEED_30);
					break;
				}
				default: break;												
				
			}
			
			break;
		}
		case(BUTTON_R_ID):
		{
			
			if(s8_previousPressed_Index == BUTTON_R_ID) break;
			
			/* activate motor with speed 30 and direction right */
			Motor_moveBackward(MOTOR_R, SPEED_30);
			Motor_moveForward(MOTOR_L, SPEED_30);
			break;
		}
		case(BUTTON_L_ID):
		{
			
			
			if(s8_previousPressed_Index == BUTTON_L_ID) break;
			/* activate motor with speed 30 and direction left */
			Motor_moveForward(MOTOR_R, SPEED_30);
			Motor_moveBackward(MOTOR_L, SPEED_30);			
			
			
			break;
		}
		case(NO_BUTTON_PRESSED):
		{
			
			/* stop motors */
			Motor_stop(MOTOR_L);
			Motor_stop(MOTOR_R);
			break;
		}
		default: break;		
	}
	return CAR_STATUS_ERROR_OK;
}
