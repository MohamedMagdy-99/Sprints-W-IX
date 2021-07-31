/*****************************************************************************
* Module: Motor Module
* File Name: Motor.c
* Description: Source file for Motor Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Motor.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuBttn_Status_t
* Description: initialized the modules used by the motor module
************************************************************************************/
enuMotor_Status_t Motor_init(void)
{
	Dio_init();
	SWPwm_Init();
	return MOTOR_STATUS_ERROR_OK;
}
/************************************************************************************
* Parameters (in): motor ID and speed
* Parameters (out): Error Status
* Return value: enuMotor_Status_t
* Description: activates the motor to move forward in a given speed
************************************************************************************/
enuMotor_Status_t Motor_moveForward(uint8_t u8_motorID, uint8_t u8_speed)
{
	Dio_writePin(strMotor_Config[u8_motorID].u8_controlPin_1, STD_LOW);
	Dio_writePin(strMotor_Config[u8_motorID].u8_controlPin_2, STD_HIGH);
	
	SWPwm_Start(strMotor_Config[u8_motorID].u8_PwmPin, strMotor_Config[u8_motorID].u32_Freq, u8_speed);
	
	return MOTOR_STATUS_ERROR_OK;
}

/************************************************************************************
* Parameters (in): motor ID and speed
* Parameters (out): Error Status
* Return value: enuMotor_Status_t
* Description: activates the motor to move backward in a given speed
************************************************************************************/
enuMotor_Status_t Motor_moveBackward(uint8_t u8_motorID, uint8_t u8_speed)
{
	Dio_writePin(strMotor_Config[u8_motorID].u8_controlPin_1, STD_HIGH);
	Dio_writePin(strMotor_Config[u8_motorID].u8_controlPin_2, STD_LOW);
	
	SWPwm_Start(strMotor_Config[u8_motorID].u8_PwmPin, strMotor_Config[u8_motorID].u32_Freq, u8_speed);
	
	return MOTOR_STATUS_ERROR_OK;	
}

/************************************************************************************
* Parameters (in): motor ID and speed
* Parameters (out): Error Status
* Return value: enuMotor_Status_t
* Description: stop a given motor
************************************************************************************/
enuMotor_Status_t Motor_stop(uint8_t u8_motorID)
{
	
	SWPwm_Stop(strMotor_Config[u8_motorID].u8_PwmPin);
	
	Dio_writePin(strMotor_Config[u8_motorID].u8_controlPin_1, STD_LOW);
	Dio_writePin(strMotor_Config[u8_motorID].u8_controlPin_2, STD_LOW);
	
	return MOTOR_STATUS_ERROR_OK;	
}
