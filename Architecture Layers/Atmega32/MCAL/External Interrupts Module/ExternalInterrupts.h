/*
 * ExternalInterrupts.h
 *
 * Created: 20-Aug-21 12:04:17 AM
 *  Author: Mohamed Magdy
 */ 


#ifndef EXTERNALINTERRUPTS_H_
#define EXTERNALINTERRUPTS_H_
/* INCLUDES */
#include "../../Microcontroller/Interrupts Handling Module/InterruptsHandler_Interface.h"
#include "../../Microcontroller/Atmega32 Registers/Interrupts_Regs.h"
/* CONSTANTS */

#define LOW_LEVEL			0			//The low level of INT0 generates an interrupt request.
#define LOGIC_CHANGE		1			//Any logical change on INT0 generates an interrupt request.
#define FALLING_EDGE		2			//The falling edge of INT0 generates an interrupt request.
#define RISING_EDGE			3			//The rising edge of INT0 generates an interrupt request.
/*************************************************************************************/
/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void (*pfINT0_CallBack_t)(void);
typedef void (*pfINT2_CallBack_t)(void);
typedef void (*pfINT1_CallBack_t)(void);
/*************************************************************************************/
/*- Function Declarations
-------------------------------*/
void DisableExternalInterrupts_INT0();
void EnableExternalInterrupts_INT0(uint8_t senseControl);
void setExtINT0Callback(pfINT0_CallBack_t FunToBeCalledInISR);

void DisableExternalInterrupts_INT2();
void EnableExternalInterrupts_INT2(uint8_t senseControl);
void setExtINT2Callback(pfINT2_CallBack_t FunToBeCalledInISR);

void DisableExternalInterrupts_INT1();
void EnableExternalInterrupts_INT1(uint8_t senseControl);
void setExtINT1Callback(pfINT1_CallBack_t FunToBeCalledInISR);

#endif /* EXTERNALINTERRUPTS_H_ */