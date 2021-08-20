/*****************************************************************************
* Module: Interrupt Module
* File Name: InterruptsHandler.c
* Description: Source file for Interrupt Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/
#include "InterruptsHandler.h"
#include "InterruptsHandler_Interface.h"

/*- Vector Table
-------------------------------*/
#define INT0         __vector_1					//External Interrupt Request 0
#define INT1         __vector_2					//External Interrupt Request 1
#define INT2		 __vector_3					//External Interrupt Request 2
#define TIMER2_COMP	 __vector_4					//Timer/Counter2 Compare Match
#define TIMER2_OVF	 __vector_5					//Timer/Counter2 Overflow
#define TIMER1_CAPT	 __vector_6  				//Timer/Counter1 Capture Event
#define TIMER1_COMPA __vector_7					//Timer/Counter1 Compare Match A
#define TIMER1_COMPB __vector_8					//Timer/Counter1 Compare Match B
#define TIMER1_OVF	 __vector_9					//Timer/Counter1 Overflow
#define TIMER0_COMP	 __vector_10				//Timer/Counter0 Compare Match
#define TIMER0_OVF	 __vector_11				//Timer/Counter0 Overflow
#define SPI_STC		 __vector_12				//SPI Serial Transfer Complete
#define USART_RXC	 __vector_13				//USART, Rx Complete
#define USART_UDRE	 __vector_14				//USART Data Register Empty
#define USART_TXC	 __vector_15				//USART, Tx Complete
#define ADC			 __vector_16				//ADC Conversion Complete
#define EE_RDY		 __vector_17				//EEPROM Ready
#define ANA_COMP	 __vector_18				//Analog Comparator
#define TWI			 __vector_19				//Two-wire Serial Interface
#define SPM_RDY		 __vector_20				//Store Program Memory Ready

#define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal,used)) __VA_ARGS__; \
void vector (void)

/*************************************************************************************/

/*- Vectors Initialization
-------------------------------*/
vectorPtr_t oldVectors[NUM_INT_VECTOR_HANDLERS] =
{
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default,
	handleInterrupt_Default
	
};
/*- Interrupt Service Routines
-------------------------------*/
ISR(INT0)
{
	 handleInterrupt_INT0();
}

ISR(INT1)
{
	handleInterrupt_INT1();
}

ISR(INT2)
{
	handleInterrupt_INT2();
}

ISR(TIMER2_COMP)
{
	handleInterrupt_TIMER2_COMP();
}

ISR(TIMER2_OVF)
{
	handleInterrupt_TIMER2_OVF();
}

ISR(TIMER1_CAPT)
{
	handleInterrupt_TIMER1_CAPT();
}

ISR(TIMER1_COMPA)
{
	handleInterrupt_TIMER1_COMPA();
}

ISR(TIMER1_COMPB)
{
	handleInterrupt_TIMER1_COMPB();
}

ISR(TIMER1_OVF)
{
	handleInterrupt_TIMER1_OVF();
}

ISR(TIMER0_COMP)
{
	handleInterrupt_TIMER0_COMP();
}

ISR(TIMER0_OVF)
{
	handleInterrupt_TIMER0_OVF();
}

ISR(SPI_STC)
{
	handleInterrupt_SPI_STC();
}

ISR(USART_RXC)
{
	handleInterrupt_USART_RXC();
}

ISR(USART_UDRE)
{
	handleInterrupt_USART_UDRE();
}

ISR(USART_TXC)
{
	handleInterrupt_USART_TXC();
}

ISR(ADC)
{
	handleInterrupt_ADC();
}

ISR(EE_RDY)
{
	handleInterrupt_EE_RDY();
}

ISR(ANA_COMP)
{
	handleInterrupt_ANA_COMP();
}

ISR(TWI)
{
	handleInterrupt_TWI();
}

ISR(SPM_RDY)
{
	handleInterrupt_SPM_RDY();
}

/*- Interrupt Handlers
-------------------------------*/
void handleInterrupt_INT0(void)
{
	oldVectors[INT0_vectorId]();
}

void handleInterrupt_INT1(void)
{
	oldVectors[INT1_vectorId]();
}

void handleInterrupt_INT2(void)
{
	oldVectors[INT2_vectorId]();
}

void handleInterrupt_TIMER2_COMP(void)
{
	oldVectors[TIMER2_COMP_vectorId]();
}

void handleInterrupt_TIMER2_OVF(void)
{
	oldVectors[TIMER2_OVF_vectorId]();
}

void handleInterrupt_TIMER1_CAPT(void)
{
	oldVectors[TIMER1_CAPT_vectorId]();
}

void handleInterrupt_TIMER1_COMPA(void)
{
	oldVectors[TIMER1_COMPA_vectorId]();
}

void handleInterrupt_TIMER1_COMPB(void)
{
	oldVectors[TIMER1_COMPB_vectorId]();
}

void handleInterrupt_TIMER1_OVF(void)
{
	oldVectors[TIMER1_OVF_vectorId]();
}

void handleInterrupt_TIMER0_COMP(void)
{
	oldVectors[TIMER0_COMP_vectorId]();
}

void handleInterrupt_TIMER0_OVF(void)
{
	oldVectors[TIMER0_OVF_vectorId]();
}

void handleInterrupt_SPI_STC(void)
{
	oldVectors[SPI_STC_vectorId]();
}

void handleInterrupt_USART_RXC(void)
{
	oldVectors[USART_RXC_vectorId]();
}

void handleInterrupt_USART_UDRE(void)
{
	oldVectors[USART_UDRE_vectorId]();
}

void handleInterrupt_USART_TXC(void)
{
	oldVectors[USART_TXC_vectorId]();
}

void handleInterrupt_ADC(void)
{
	oldVectors[ADC_vectorId]();
}

void handleInterrupt_EE_RDY(void)
{
	oldVectors[EE_RDY_vectorId]();
}

void handleInterrupt_ANA_COMP(void)
{
	oldVectors[ANA_COMP_vectorId]();
}

void handleInterrupt_TWI(void)
{
	oldVectors[TWI_vectorId]();
}

void handleInterrupt_SPM_RDY(void)
{
	oldVectors[SPM_RDY_vectorId]();
}

void handleInterrupt_Default(void)
{
	while(1)
	{
		
	}
}
