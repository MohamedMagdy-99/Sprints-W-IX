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
	/*Control Pin 1*/  /*Control Pin 2*/      /*Pwm Pin*/		/*Motor Freq*/ 
	{  MOTOR_IN1    ,   MOTOR_IN2  ,		   MOTOR_PWM_ENA  ,     MOTOR_FREQ   }

};
