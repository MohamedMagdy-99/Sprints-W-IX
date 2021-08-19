/*****************************************************************************
* Module: Adc Module
* File Name: Adc.c
* Description: Source file for Adc Module
* Author: Mohamed Magdy
* Date: 25-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Adc.h"


/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static pfAdc_CallBack_t AdcCallback;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuAdc_Status_t Adc_Status = ADC_STATUS_ERROR_OK;
enuAdc_initStatus_t Adc_Init = ADC_NOT_INITIALIZED;


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
enuAdc_Status_t Adc_init(void)
{
	if(Adc_Init == ADC_INITIALIZED) return ADC_STATUS_ERROR_NOK;
	Adc_Init = ADC_INITIALIZED;
	
	Dio_init();
	/*******************************************************************/
	
	/* enable ADC module */
	SET_BIT(ADCSRA_R, ADEN_B);
	
	/* setting conversion speed to Fosc/12 */
	SET_BIT(ADCSRA_R, ADPS0_B);
	SET_BIT(ADCSRA_R, ADPS1_B);
	SET_BIT(ADCSRA_R, ADPS2_B);
	
	/* check for Auto trigger mode */
	switch(AutoTriggerState)
	{
		case(DisableAutoTrigger):
		{
			CLEAR_BIT(ADCSRA_R, ADATE_B);
			break;
		}
		default: break;
	}
	
	/* set ADC conversion result to right adjusted */
	CLEAR_BIT(ADCSRA_R, ADLAR_B);
	
	return ADC_STATUS_ERROR_OK;
}

enuAdc_Status_t Adc_start(uint8_t u8_channelId, uint16_t* pu16_milliVolts)
{
	/* enable adc in case it was stopped */
	SET_BIT(ADCSRA_R, ADEN_B);

		switch(strAdc_Channles[u8_channelId].u8_channelId)
		{
			case(ADC0_ID):
			{
				/* set channel Id */
				ADMUX_R |= ADC0_ID;
				
				/* set desired Vref */
				switch(strAdc_Channles[u8_channelId].u8_channelVref)
				{
					case(External_Vref):
					{
						CLEAR_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(AdcVcc_Vref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);						
						break;
					}
					case(InternalVref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						SET_BIT(ADMUX_R, REFS1_B);
						break;
					}
					default: break;										
				}
					break;
			}
			case(ADC1_ID):
			{
				/* set channel Id */
				ADMUX_R |= ADC1_ID;
				
				/* set desired Vref */
				switch(strAdc_Channles[u8_channelId].u8_channelVref)
				{
					case(External_Vref):
					{
						CLEAR_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(AdcVcc_Vref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(InternalVref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						SET_BIT(ADMUX_R, REFS1_B);
						break;
					}
					default: break;
				}
				break;
			}
			case(ADC2_ID):
			{
				/* set channel Id */
				ADMUX_R |= ADC2_ID;
				
				/* set desired Vref */
				switch(strAdc_Channles[u8_channelId].u8_channelVref)
				{
					case(External_Vref):
					{
						CLEAR_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(AdcVcc_Vref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(InternalVref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						SET_BIT(ADMUX_R, REFS1_B);
						break;
					}
					default: break;
				}
				break;
			}
			case(ADC3_ID):
			{
				/* set channel Id */
				ADMUX_R |= ADC3_ID;
				
				/* set desired Vref */
				switch(strAdc_Channles[u8_channelId].u8_channelVref)
				{
					case(External_Vref):
					{
						CLEAR_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(AdcVcc_Vref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(InternalVref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						SET_BIT(ADMUX_R, REFS1_B);
						break;
					}
					default: break;
				}
				break;
			}
			case(ADC4_ID):
			{
				/* set channel Id */
				ADMUX_R |= ADC4_ID;
				
				/* set desired Vref */
				switch(strAdc_Channles[u8_channelId].u8_channelVref)
				{
					case(External_Vref):
					{
						CLEAR_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(AdcVcc_Vref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(InternalVref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						SET_BIT(ADMUX_R, REFS1_B);
						break;
					}
					default: break;
				}
				break;
			}
			case(ADC5_ID):
			{
				/* set channel Id */
				ADMUX_R |= ADC5_ID;
				
				/* set desired Vref */
				switch(strAdc_Channles[u8_channelId].u8_channelVref)
				{
					case(External_Vref):
					{
						CLEAR_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(AdcVcc_Vref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(InternalVref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						SET_BIT(ADMUX_R, REFS1_B);
						break;
					}
					default: break;
				}
				break;
			}
			case(ADC6_ID):
			{
				/* set channel Id */
				ADMUX_R |= ADC6_ID;
				
				/* set desired Vref */
				switch(strAdc_Channles[u8_channelId].u8_channelVref)
				{
					case(External_Vref):
					{
						CLEAR_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(AdcVcc_Vref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(InternalVref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						SET_BIT(ADMUX_R, REFS1_B);
						break;
					}
					default: break;
				}
				break;
			}
			case(ADC7_ID):
			{
				/* set channel Id */
				ADMUX_R |= ADC7_ID;
			
				/* set desired Vref */
				switch(strAdc_Channles[u8_channelId].u8_channelVref)
				{
					case(External_Vref):
					{
						CLEAR_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(AdcVcc_Vref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						CLEAR_BIT(ADMUX_R, REFS1_B);
						break;
					}
					case(InternalVref):
					{
						SET_BIT(ADMUX_R, REFS0_B);
						SET_BIT(ADMUX_R, REFS1_B);
						break;
					}
					default: break;
				}
				break;
			}
			default: break;																					
		}
	
		/* start conversion signal */
		SET_BIT(ADCSRA_R, ADSC_B);
		
		/* wait for end of conversion flag */
		while(BIT_IS_CLEAR(ADCSRA_R, ADIF_B));
		
		/* read the result from register */
		uint16_t u16_tempAdcValue = Initial_Value;
		
		
		u16_tempAdcValue = ADCL_R;
		
		u16_tempAdcValue |= (ADCH_R<<8);
		
		

		/* convert Adc value to millivolts */
		*pu16_milliVolts = ((u16_tempAdcValue* Vref)/ResolutionLevels)*1000;
	
		
		
		/* clear interrupt flag */
		SET_BIT(ADCSRA_R, ADIF_B);
		
		
		return ADC_STATUS_ERROR_OK;
}


enuAdc_Status_t Adc_readFromISR(uint16_t* pu16_milliVolts)
{
		/* read the result from register */
		uint16_t u16_tempAdcValue = Initial_Value;
		
		u16_tempAdcValue = ADCL_R;
		
		u16_tempAdcValue |= (ADCH_R<<8);
		
		/* convert Adc value to milivolts */
		*pu16_milliVolts = ((u16_tempAdcValue* Vref)/ResolutionLevels)*1000;
		
		return ADC_STATUS_ERROR_OK;
}


enuAdc_Status_t Adc_stop(void)
{
	/* disable ADC module */
	CLEAR_BIT(ADCSRA_R, ADEN_B);
	
	return ADC_STATUS_ERROR_OK;
}


enuAdc_Status_t Adc_startWithInterrupt(uint8_t u8_channelId, pfAdc_CallBack_t FunToBeCalledInISR)
{
	/* enable global and adc interrupts */
	EnableGlobalInterrupts();
	SET_BIT(ADCSRA_R, ADIE_B);
	/* set the call back function to be executed in ISR */
	Adc_setCallBack(FunToBeCalledInISR);
	
	
	
	return ADC_STATUS_ERROR_OK;
}


/* Interrupts */

/*****************************************************************************************
* Parameters (in): pointer to function to be called from ISR
* Parameters (out): None
* Return value: None
* Description: sets the function to be called by Adc ISR
******************************************************************************************/
void Adc_setCallBack(pfAdc_CallBack_t FunToBeCalledInISR)
{
	AdcCallback = FunToBeCalledInISR;
	
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: interrupt service routine for Adc conversion complete
******************************************************************************************/
ISR(ADC)
{
	AdcCallback();
	/* disable adc interrupts */
	CLEAR_BIT(ADCSRA_R, ADIE_B);
}
