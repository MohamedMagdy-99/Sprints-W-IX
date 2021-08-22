/*
 * ExternalInterrupts.c
 *
 * Created: 20-Aug-21 12:03:55 AM
 *  Author: Mohamed Magdy
 */ 

#include "ExternalInterrupts.h"

/*- Function Definitions
-------------------------------*/
/*- External Interrupt 0
-------------------------------*/
void EnableExternalInterrupts_INT0(uint8_t senseControl)
{
	SET_BIT(GICR_R, INT0_B);
	switch(senseControl)
	{
		case(LOW_LEVEL):
		{
			CLEAR_BIT(MCUCR_R, ISC00_B);
			CLEAR_BIT(MCUCR_R, ISC01_B);
			break;
		}
		case(LOGIC_CHANGE):
		{
			SET_BIT(MCUCR_R, ISC00_B);
			CLEAR_BIT(MCUCR_R, ISC01_B);
			break;
		}
		case(FALLING_EDGE):
		{
			CLEAR_BIT(MCUCR_R, ISC00_B);
			SET_BIT(MCUCR_R, ISC01_B);
			break;
		}
		case(RISING_EDGE):
		{
			SET_BIT(MCUCR_R, ISC00_B);
			SET_BIT(MCUCR_R, ISC01_B);
			break;
		}
	}
}

void DisableExternalInterrupts_INT0()
{
	CLEAR_BIT(GICR_R, INT0_B);
}

void setExtINT0Callback(pfINT0_CallBack_t FunToBeCalledInISR)
{
	install_ISR(INT0_vectorId,FunToBeCalledInISR);
}



/*- External Interrupt 1
-------------------------------*/

void EnableExternalInterrupts_INT1(uint8_t senseControl)
{
	SET_BIT(GICR_R, INT1_B);
	switch(senseControl)
	{
		case(LOW_LEVEL):
		{
			CLEAR_BIT(MCUCR_R, ISC10_B);
			CLEAR_BIT(MCUCR_R, ISC11_B);
			break;
		}
		case(LOGIC_CHANGE):
		{
			SET_BIT(MCUCR_R, ISC10_B);
			CLEAR_BIT(MCUCR_R, ISC11_B);
			break;
		}
		case(FALLING_EDGE):
		{
			CLEAR_BIT(MCUCR_R, ISC10_B);
			SET_BIT(MCUCR_R, ISC11_B);
			break;
		}
		case(RISING_EDGE):
		{
			SET_BIT(MCUCR_R, ISC10_B);
			SET_BIT(MCUCR_R, ISC11_B);
			break;
		}
	}
}

void DisableExternalInterrupts_INT1()
{
	CLEAR_BIT(GICR_R, INT1_B);
}

void setExtINT1Callback(pfINT1_CallBack_t FunToBeCalledInISR)
{
	install_ISR(INT1_vectorId, FunToBeCalledInISR);
}


/*- External Interrupt 2
-------------------------------*/

void EnableExternalInterrupts_INT2(uint8_t senseControl)
{
	SET_BIT(GICR_R, INT2_B);
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

}

void DisableExternalInterrupts_INT2()
{
	CLEAR_BIT(GICR_R, INT2_B);
}

void setExtINT2Callback(pfINT2_CallBack_t FunToBeCalledInISR)
{
	install_ISR(INT2_vectorId, FunToBeCalledInISR);
}

