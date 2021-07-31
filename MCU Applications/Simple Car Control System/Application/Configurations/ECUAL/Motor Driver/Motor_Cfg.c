/*****************************************************************************
* Module: Motor Module
* File Name: Motor_Cfg.c
* Description: Source file for Motor Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Motor.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* here you adjust the motor configurations */
strMotor_Config_t strMotor_Config[MOTORS_USED]=
{
	/*Control Pin 1*/  /*Control Pin 1*/      /*Pwm Pin*/		/*Motor Freq*/ 
	{  MOTOR_R_IN1    ,  MOTOR_R_IN2   ,   MOTOR_R_PWM_ENA  ,  MOTOR_R_FREQ   },
	{  MOTOR_L_IN3    ,  MOTOR_L_IN4  ,    MOTOR_L_PWM_ENB  ,  MOTOR_L_FREQ   }

};
/*- APIs IMPLEMENTATION
-----------------------------------*/