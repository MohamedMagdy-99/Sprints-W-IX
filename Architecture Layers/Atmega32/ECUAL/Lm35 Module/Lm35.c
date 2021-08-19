/*****************************************************************************
* Module: Lm35 Module
* File Name: Lm35.c
* Description: Source file for Lm35 Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Lm35.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

enuLm35_Status_t Lm35_init(void)
{
	Adc_init();
	
	return LM35_STATUS_ERROR_OK;
}

enuLm35_Status_t Lm35_getTemp(uint8_t u8_channelId, uint8_t* u8_temperature)
{
	uint16_t u16_milliVolts = Initial_Value;
	Adc_start(u8_channelId, &u16_milliVolts);
	
	*u8_temperature = u16_milliVolts/SensorResolution_Millivolts;
	
	
	return LM35_STATUS_ERROR_OK;
}