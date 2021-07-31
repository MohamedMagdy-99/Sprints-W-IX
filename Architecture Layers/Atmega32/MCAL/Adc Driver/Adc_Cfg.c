/*****************************************************************************
* Module: Adc Module
* File Name: Adc_Cfg.c
* Description: Source file for Adc Module
* Author: Mohamed Magdy
* Date: 25-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Adc.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* configuration of pins to be used */
strAdc_Config_t strAdc_Channles[ADC_USED_CHANNELS_NUM]=
{
	/*Channle Id*/   /* Vref Source*/    
	{  ADC0_ID    ,   AdcVcc_Vref    }


	
};