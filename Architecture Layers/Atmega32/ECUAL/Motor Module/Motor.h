
/*****************************************************************************
* Module: Motor Module
* File Name: Motor.h
* Description: Header file for Motor Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/
#ifndef MOTOR_H_
#define MOTOR_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Motor_Cfg.h"
#include "../../MCAL/Dio Driver/Dio.h"
#include "../../MCAL/SW_Pwm Driver/SWPwm.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
 * Data Type for Motor return status
 */
typedef enum
{
	MOTOR_STATUS_ERROR_NOK,
	MOTOR_STATUS_ERROR_OK,
	MOTOR_STATUS_ERROR_INVALID
}enuMotor_Status_t;

/*
 * Data Type for Motor Configurations
 */
typedef struct
{
	uint8_t u8_controlPin_1;
	uint8_t u8_controlPin_2;
	uint8_t u8_PwmPin;
	uint32_t u32_Freq;

}strMotor_Config_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the motor module */
enuMotor_Status_t Motor_init(void);

/* Function to move the motor forward with given speed in % */
enuMotor_Status_t Motor_moveForward(uint8_t u8_motorID, uint8_t u8_speed);

/* Function to move the motor backward with given speed in % */
enuMotor_Status_t Motor_moveBackward(uint8_t u8_motorID, uint8_t u8_speed);

/* Function to stop motor */
enuMotor_Status_t Motor_stop(uint8_t u8_motorID);

/* configuration variable */
extern strMotor_Config_t strMotor_Config[MOTORS_USED];

#endif /* MOTOR_H_ */