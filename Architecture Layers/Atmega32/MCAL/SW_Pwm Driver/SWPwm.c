/*****************************************************************************
* Module: SW_PWM Module
* File Name: SWPwm.c
* Description: Source file for SW_PWM Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/



/*- INCLUDES
----------------------------------------------*/
#include "SWPwm.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
strPwm_sharedData_t usedParameters;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuSWPwm_Status_t SW_PWM_Status = SWPWM_STATUS_ERROR_OK;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuSWPwm_Status_t
* Description: Initializes the gpt and dio driver to use the sw pwm
******************************************************************************************/
enuSWPwm_Status_t SWPwm_Init(void)
{
	Dio_init();
	GptInit();
	return SWPWM_STATUS_ERROR_OK;
}
/*****************************************************************************************
* Parameters (in): Channel Id , frequency and duty cycle
* Parameters (out): Error Status
* Return value: enuSWPwm_Status_t
* Description: starts the PWM signal according to the given parameters 
******************************************************************************************/
enuSWPwm_Status_t SWPwm_Start(uint8_t u8_ChannelID, uint32_t u32_Freq, uint8_t u8_DutyCycle)
{
	if(SW_PWM_Status != SWPWM_STATUS_ALREADY_RUNNING)
	{	
		SW_PWM_Status = SWPWM_STATUS_ALREADY_RUNNING;	

		
		float32_t f32_TotalPeriod = (float32_t)1/u32_Freq;
		float32_t f32_OneTick = (float32_t)(strGpt_Channels[u8_ChannelID].u8_Prescaler)/F_CPU;
		uint32_t u32_TimerTicks = f32_TotalPeriod/f32_OneTick;
		uint32_t u32_OnTimeTicks = u32_TimerTicks * ((float32_t)u8_DutyCycle/100);
		uint32_t u32_OffTimeTicks = u32_TimerTicks - u32_OnTimeTicks;
		
		usedParameters.u8_ChannelID = u8_ChannelID;
		usedParameters.u32_OnTimeTicks = u32_OnTimeTicks;
		usedParameters.u32_OffTimeTicks = u32_OffTimeTicks;
		
		Dio_writePin(strPwm_channels[usedParameters.u8_ChannelID].u8_DioId, STD_LOW); //make sure it's starting from a low level
		GptStart_aSync(strPwm_channels[u8_ChannelID].u8_TimerChannelId, u32_OffTimeTicks, PWM_Generate);
		
		usedParameters.u8_TurnTicks = Initial_Value;
		
	}
	else
	{
		return SWPWM_STATUS_ALREADY_RUNNING;
	}
	return SWPWM_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuSWPwm_Status_t
* Description: stops the pwm signal of the given ID
******************************************************************************************/
enuSWPwm_Status_t SWPwm_Stop(uint8_t u8_ChannelID)
{
	SW_PWM_Status = SWPWM_STATUS_NOT_RUNNING;
	Dio_writePin(strPwm_channels[usedParameters.u8_ChannelID].u8_DioId, STD_LOW); //make sure it's starting from a low level
	GptStop(strPwm_channels[u8_ChannelID].u8_TimerChannelId);
	usedParameters.u8_TurnTicks = Initial_Value;
	return SWPWM_STATUS_ERROR_OK;
}
/*- APIs IMPLEMENTATION
-----------------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: callback function to be called when overflow ISR triggered
******************************************************************************************/
void PWM_Generate(void)
{
	Dio_togglePin(strPwm_channels[usedParameters.u8_ChannelID].u8_DioId);
	
	if(SW_PWM_Status == SWPWM_STATUS_ALREADY_RUNNING)
	{
		if(usedParameters.u8_TurnTicks == Initial_Value)
		{
			usedParameters.u8_TurnTicks++;
			GptStart_aSync(strPwm_channels[usedParameters.u8_ChannelID].u8_TimerChannelId, usedParameters.u32_OnTimeTicks, PWM_Generate);
			
		}
		else
		{
			--usedParameters.u8_TurnTicks;
			GptStart_aSync(strPwm_channels[usedParameters.u8_ChannelID].u8_TimerChannelId, usedParameters.u32_OffTimeTicks, PWM_Generate);
			
		}
	}
	
}

