/*****************************************************************************
* Module: Gpt Module
* File Name: Gpt.c
* Description: Source file for GPT Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Gpt.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static volatile uint32_t gu32_OvfCounts = Initial_Value;

static pfGpt_CallBack_t ovfCallback;

enuGpt_Status_t Gpt_Status = GPT_STATUS_ERROR_OK;
enuGpt_initStatus_t Gpt_Init = GPT_NOT_INITIALIZED;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: initialize the gpt module according to the cfg file
******************************************************************************************/
enuGpt_Status_t GptInit(void) 
{
	if(Gpt_Init == GPT_INITIALIZED) return GPT_STATUS_ERROR_NOK;
	
	Gpt_Init = GPT_INITIALIZED;
		
	uint8_t u8_LoopCounter = Initial_Value;
	for(u8_LoopCounter=0 ; u8_LoopCounter < GPT_USED_CHANNELS ; u8_LoopCounter++)
	{
		switch(strGpt_Channels[u8_LoopCounter].u8_TimerNumber)
		{
			case(TIMER_0):
			{
				switch(strGpt_Channels[u8_LoopCounter].u8_Mode)
				{
					case(NORMAL_MODE):
					{
						/* making sure timer is OFF */
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);

						/* set to Normal mode */
						CLEAR_BIT(TCCR0_R, WGM01_B);
						CLEAR_BIT(TCCR0_R, WGM00_B);

						/* Initialize the timer count register */
						TCNT0_R = 0x00;
						
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;
				}
			}
			default: return GPT_STATUS_ERROR_NOK;
		}
	}
	
	return GPT_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: starts the given gpt timer id in synchronous mode (polling)
******************************************************************************************/
enuGpt_Status_t GptStart_Sync(uint8_t ChannelId, uint32_t u32_Ticks)
{
	
	switch(strGpt_Channels[ChannelId].u8_TimerNumber)
	{
		case(TIMER_0):
		{
			if((u32_Ticks <= TIMER_0_MAX_TICKS) && (u32_Ticks != 0))
			{
				/* set ticks */
				TCNT0_R = TIMER_0_MAX_TICKS - u32_Ticks;
				
				/* set to prescaler */
				switch(strGpt_Channels[ChannelId].u8_Prescaler)
				{
					case(PRESCALER_1):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
							
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);	
							
						TCNT0_R = 0x00;		
													
						break;
					}
					case(PRESCALER_8):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
						
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;
																		
						break;
					}
					case(PRESCALER_64):
					{
						SET_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);		
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
						
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;
																
						break;
					}
					case(PRESCALER_256):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);	
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
						
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;
																	
						break;
					}
					case(PRESCALER_1024):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);	
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
						
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;
																	
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;																															
				}
			}
			else if((u32_Ticks > TIMER_0_MAX_TICKS) && (u32_Ticks != 0))
			{
				uint32_t u32_OvfCounter = Initial_Value;
				float32_t f32_TempValue = (float32_t)u32_Ticks/TIMER_0_MAX_TICKS;
				uint32_t u32_OvfCounts = f32_TempValue;
				f32_TempValue -= u32_OvfCounts;
				uint32_t u32_CountRemanider = f32_TempValue * TIMER_0_MAX_TICKS;
				
				/* set to prescaler */
				switch(strGpt_Channels[ChannelId].u8_Prescaler)
				{
					case(PRESCALER_1):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_8):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_64):
					{
						SET_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_256):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_1024):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;
				}				
					while(u32_OvfCounter < u32_OvfCounts)
					{
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						u32_OvfCounter++;
						SET_BIT(TIFR_R, TOV0_B);							
					}
					
					if(u32_CountRemanider != 0)
					{
						TCNT0_R = TIMER_0_MAX_TICKS - u32_CountRemanider;
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
					}
					
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;				
			}
			else
			{
				return GPT_STATUS_ERROR_NOK;
			}
			
			break;
		}
		default: return GPT_STATUS_ERROR_NOK;
		
	}
	return GPT_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: starts the given gpt timer id in Asynchronous mode (interrupts)
******************************************************************************************/
enuGpt_Status_t GptStart_aSync(uint8_t ChannelId, uint32_t u32_Ticks, pfGpt_CallBack_t FunToBeCalledInISR)
{
	if(Gpt_Status != GPT_STATUS_ALREADY_RUNNING)
	{		
		    Gpt_Status = GPT_STATUS_ALREADY_RUNNING;
			EnableGlobalInterrupts();
			setOvfCallback(FunToBeCalledInISR);
			switch(strGpt_Channels[ChannelId].u8_TimerNumber)
			{
				case(TIMER_0):
				{
					if((u32_Ticks <= TIMER_0_MAX_TICKS) && (u32_Ticks != 0))
					{
						/* set ticks */
						TCNT0_R = TIMER_0_MAX_TICKS - u32_Ticks;
						
						/* set to prescaler */
						switch(strGpt_Channels[ChannelId].u8_Prescaler)
						{
							case(PRESCALER_1):
							{
								SET_BIT(TCCR0_R, CS00_B);
								CLEAR_BIT(TCCR0_R, CS01_B);
								CLEAR_BIT(TCCR0_R, CS02_B);
								
								SET_BIT(TIMSK_R, TOIE0_B);
								
								break;
							}
							case(PRESCALER_8):
							{
								CLEAR_BIT(TCCR0_R, CS00_B);
								SET_BIT(TCCR0_R, CS01_B);
								CLEAR_BIT(TCCR0_R, CS02_B);
								
								SET_BIT(TIMSK_R, TOIE0_B);
								

								
								break;
							}
							case(PRESCALER_64):
							{
								SET_BIT(TCCR0_R, CS00_B);
								SET_BIT(TCCR0_R, CS01_B);
								CLEAR_BIT(TCCR0_R, CS02_B);
								
								SET_BIT(TIMSK_R, TOIE0_B);
								
								
								break;
							}
							case(PRESCALER_256):
							{
								CLEAR_BIT(TCCR0_R, CS00_B);
								CLEAR_BIT(TCCR0_R, CS01_B);
								SET_BIT(TCCR0_R, CS02_B);
								
								SET_BIT(TIMSK_R, TOIE0_B);
						
								
								break;
							}
							case(PRESCALER_1024):
							{
								SET_BIT(TCCR0_R, CS00_B);
								CLEAR_BIT(TCCR0_R, CS01_B);
								SET_BIT(TCCR0_R, CS02_B);
								
								SET_BIT(TIMSK_R, TOIE0_B);
								
								
								break;
							}
							default: return GPT_STATUS_ERROR_NOK;
						}
					}
					else if((u32_Ticks > TIMER_0_MAX_TICKS) && (u32_Ticks != 0))
					{
						
						float32_t f32_TempValue = (float32_t)u32_Ticks/TIMER_0_MAX_TICKS;
						gu32_OvfCounts = f32_TempValue;
						f32_TempValue -= gu32_OvfCounts;
						uint32_t u32_CountRemanider = f32_TempValue * TIMER_0_MAX_TICKS;
						
						TCNT0_R = u32_CountRemanider;
						
						/* set to prescaler */
						switch(strGpt_Channels[ChannelId].u8_Prescaler)
						{
							case(PRESCALER_1):
							{
								SET_BIT(TCCR0_R, CS00_B);
								CLEAR_BIT(TCCR0_R, CS01_B);
								CLEAR_BIT(TCCR0_R, CS02_B);
								break;
							}
							case(PRESCALER_8):
							{
								CLEAR_BIT(TCCR0_R, CS00_B);
								SET_BIT(TCCR0_R, CS01_B);
								CLEAR_BIT(TCCR0_R, CS02_B);
								break;
							}
							case(PRESCALER_64):
							{
								SET_BIT(TCCR0_R, CS00_B);
								SET_BIT(TCCR0_R, CS01_B);
								CLEAR_BIT(TCCR0_R, CS02_B);
								break;
							}
							case(PRESCALER_256):
							{
								CLEAR_BIT(TCCR0_R, CS00_B);
								CLEAR_BIT(TCCR0_R, CS01_B);
								SET_BIT(TCCR0_R, CS02_B);
								break;
							}
							case(PRESCALER_1024):
							{
								SET_BIT(TCCR0_R, CS00_B);
								CLEAR_BIT(TCCR0_R, CS01_B);
								SET_BIT(TCCR0_R, CS02_B);
								break;
							}
							default: return GPT_STATUS_ERROR_NOK;
						}
						
						SET_BIT(TIMSK_R, TOIE0_B);
							
				
					}
					else
					{
						return GPT_STATUS_ERROR_NOK;
					}
					
					break;
				}
				default: return GPT_STATUS_ERROR_NOK;
				
			}
			return GPT_STATUS_ERROR_OK;
	}
	else
	{
		return GPT_STATUS_ALREADY_RUNNING;	
	}
	return GPT_STATUS_ERROR_OK;
}



/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: stops a given timer
******************************************************************************************/
enuGpt_Status_t GptStop(uint8_t ChannelId)
{
	switch(strGpt_Channels[ChannelId].u8_TimerNumber)
	{
		case(TIMER_0):
		{
			CLEAR_BIT(TCCR0_R, CS00_B);
			CLEAR_BIT(TCCR0_R, CS01_B);
			CLEAR_BIT(TCCR0_R, CS02_B);
			TCNT0_R = 0x00;
			CLEAR_BIT(TIMSK_R, TOIE0_B);
			
			Gpt_Status = GPT_STATUS_NOT_RUNNING;
			
			break;
		}
		default: return GPT_STATUS_ERROR_NOK;
	}
	
	return GPT_STATUS_ERROR_OK;
}

/* Interrupts */

/*****************************************************************************************
* Parameters (in): pointer to function to be called from ISR
* Parameters (out): None
* Return value: None
* Description: sets the function to be called by overflow timer ISR
******************************************************************************************/
void setOvfCallback(pfGpt_CallBack_t FunToBeCalledInISR)
{
	ovfCallback = FunToBeCalledInISR;
	
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: interrupt service routine for timer 0 overflow
******************************************************************************************/
ISR(TIMER0_OVF)
{
	if(gu32_OvfCounts == 0)
	{
		 Gpt_Status = GPT_STATUS_NOT_RUNNING;
		 ovfCallback();
	}
	else
	{
		gu32_OvfCounts--;
	}
}

