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

#define MOTORS_USED	    2

#define MOTOR_R			0
#define MOTOR_L			1

#define MOTOR_R_PWM_ENA		    PWM_CHANNEL_1_ID
#define MOTOR_R_IN1				PORTC_PIN1_ID
#define MOTOR_R_IN2				PORTC_PIN2_ID
#define MOTOR_R_FREQ			100

#define MOTOR_L_PWM_ENB		    PWM_CHANNEL_1_ID
#define MOTOR_L_IN3				PORTC_PIN3_ID
#define MOTOR_L_IN4				PORTC_PIN4_ID
#define MOTOR_L_FREQ			100


#endif /* MOTOR_CFG_H_ */