/*****************************************************************************
* Module: Motor Module
* File Name: Motor_Cfg.h
* Description: Header file for Motor Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/

#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

/* CONSTANTS */

/* user set the number of pins used in the project */

#define MOTORS_USED	    1

#define MOTOR_ATM_ID			0


#define MOTOR_PWM_ENA		    PWM_CHANNEL_1_ID
#define MOTOR_IN1				PORTB_PIN0_ID
#define MOTOR_IN2				PORTB_PIN1_ID
#define MOTOR_FREQ				100

#endif /* MOTOR_CFG_H_ */