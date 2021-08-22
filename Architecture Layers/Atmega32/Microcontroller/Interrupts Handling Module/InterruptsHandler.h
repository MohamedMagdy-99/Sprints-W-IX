/*****************************************************************************
* Module: Interrupt Module
* File Name: InterruptsHandler.h
* Description: Header file for Interrupt Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/


#ifndef INTH_H_
#define INTH_H_

#include "../Std_Types.h"
#include "../../Libraries/Common_Macros.h"

/*- Primitive Types
-------------------------------*/
typedef void(*vectorPtr_t)(void);
typedef uint8_t peripheralVectorId_t;

 /*- Constants
 -------------------------------*/
#define NUM_INT_VECTOR_HANDLERS			(20U)

/*- Function Declarations
-------------------------------*/
void handleInterrupt_INT0(void);
void handleInterrupt_INT1(void);
void handleInterrupt_INT2(void);
void handleInterrupt_TIMER2_COMP(void);
void handleInterrupt_TIMER2_OVF(void);
void handleInterrupt_TIMER1_CAPT(void);
void handleInterrupt_TIMER1_COMPA(void);
void handleInterrupt_TIMER1_COMPB(void);
void handleInterrupt_TIMER1_OVF(void);
void handleInterrupt_TIMER0_COMP(void);
void handleInterrupt_TIMER0_OVF(void);
void handleInterrupt_SPI_STC(void);
void handleInterrupt_USART_RXC(void);
void handleInterrupt_USART_UDRE(void);
void handleInterrupt_USART_TXC(void);
void handleInterrupt_ADC(void);
void handleInterrupt_EE_RDY(void);
void handleInterrupt_ANA_COMP(void);
void handleInterrupt_TWI(void);
void handleInterrupt_SPM_RDY(void);

void handleInterrupt_Default(void);

/*- Extern Variables
-------------------------------*/
extern vectorPtr_t oldVectors[NUM_INT_VECTOR_HANDLERS];

#endif /* INTH_H_ */