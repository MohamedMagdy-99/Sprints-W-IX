/*
 * ExternalInterrupts.c
 *
 * Created: 20-Aug-21 12:03:55 AM
 *  Author: Mohamed Magdy
 */ 

#include "../Interrupts Handling Module/InterruptsHandler_Interface.h"
#include "ExternalInterrupts.h"

/*- Function Definitions
-------------------------------*/
void EnableExternalInterrupts_INT0(uint8_t senseControl)
{
	SET_BIT(GICR_R, INT0_B);
	switch(senseControl)
	{
		case(LOW_LEVEL):
		{
			CLEAR_BIT(MCUCR_R, ISC00_B);
			CLEAR_BIT(MCUCR_R, ISC00_B);
			break;
		}
		case(LOGIC_CHANGE):
		{
			SET_BIT(MCUCR_R, ISC00_B);
			CLEAR_BIT(MCUCR_R, ISC00_B);
			break;
		}
		case(FALLING_EDGE):
		{
			CLEAR_BIT(MCUCR_R, ISC00_B);
			SET_BIT(MCUCR_R, ISC00_B);
			break;
		}
		case(RISING_EDGE):
		{
			SET_BIT(MCUCR_R, ISC00_B);
			SET_BIT(MCUCR_R, ISC00_B);
			break;
		}
	}
	EnableGlobalInterrupts();
}

void DisableExternalInterrupts_INT0()
{
	CLEAR_BIT(GICR_R, INT0_B);
}



void EnableExternalInterrupts_INT2(uint8_t senseControl)
{
	
	switch(senseControl)
	{
		case(FALLING_EDGE):
		{
			CLEAR_BIT(MCUCSR_R, ISC2_B);
			break;
		}
		case(RISING_EDGE):
		{
			SET_BIT(MCUCSR_R, ISC2_B);
			break;
		}
		default: break;
		
	}
	SET_BIT(GICR_R, INT2_B);
	EnableGlobalInterrupts();
}

void DisableExternalInterrupts_INT2()
{
	CLEAR_BIT(GICR_R, INT2_B);
}
