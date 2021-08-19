/*****************************************************************************
* Module: SW_PWM Module
* File Name: SWPwm_Cfg.c
* Description: Source file for SW_PWM Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/


/*- INCLUDES
----------------------------------------------*/
#include "SWPwm.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
strPwm_Config_t strPwm_channels[USED_PWM_CHANNELS]=
{
		/*Dio Id*/							/*Gpt Channel Id*/  
	{  PWM_CHANNEL_1_DIO_PIN_ID    ,        PWM_CHANNEL_1_TIMER_ID          }

};