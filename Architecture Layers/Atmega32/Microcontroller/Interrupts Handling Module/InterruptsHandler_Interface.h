/*****************************************************************************
* Module: Interrupt Module
* File Name: InterruptsHandler_Interface.h
* Description: Header file for Interrupt Module Interface
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/


#ifndef INTERRUPTSHANDLER_INTERFACE_H_
#define INTERRUPTSHANDLER_INTERFACE_H_

#include "InterruptsHandler.h"
#include "Interrupts_Regs.h"

/*- CONSTATNS
-------------------------------*/
#define INT0_vectorId					0					//External Interrupt Request 0
#define INT1_vectorId					1					//External Interrupt Request 1
#define INT2_vectorId					2					//External Interrupt Request 2
#define TIMER2_COMP_vectorId			3					//Timer/Counter2 Compare Match
#define TIMER2_OVF_vectorId				4					//Timer/Counter2 Overflow
#define TIMER1_CAPT_vectorId			5  					//Timer/Counter1 Capture Event
#define TIMER1_COMPA_vectorId			6					//Timer/Counter1 Compare Match A
#define TIMER1_COMPB_vectorId			7					//Timer/Counter1 Compare Match B
#define TIMER1_OVF_vectorId				8					//Timer/Counter1 Overflow
#define TIMER0_COMP_vectorId			9					//Timer/Counter0 Compare Match
#define TIMER0_OVF_vectorId				10					//Timer/Counter0 Overflow
#define SPI_STC_vectorId				11					//SPI Serial Transfer Complete
#define USART_RXC_vectorId				12					//USART, Rx Complete
#define USART_UDRE_vectorId				13					//USART Data Register Empty
#define USART_TXC_vectorId				14					//USART, Tx Complete
#define ADC_vectorId					15					//ADC Conversion Complete
#define EE_RDY_vectorId					16					//EEPROM Ready
#define ANA_COMP_vectorId				17					//Analog Comparator
#define TWI_vectorId					18					//Two-wire Serial Interface
#define SPM_RDY_vectorId				19					//Store Program Memory Ready
#define INVALID_vectorId				20					//Invalid Vector Id

/*- Function Declarations
-------------------------------*/
void EnableGlobalInterrupts(void);
void DisableGlobalInterrupts(void);

void install_ISR(peripheralVectorId_t peripheralId,  vectorPtr_t CallBackFun);
void deinstall_ISR(peripheralVectorId_t peripheralId);

#endif /* INTERRUPTSHANDLER_INTERFACE_H_ */