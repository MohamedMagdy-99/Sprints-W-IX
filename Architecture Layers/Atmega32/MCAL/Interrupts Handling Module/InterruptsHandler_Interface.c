/*****************************************************************************
* Module: Interrupt Module
* File Name: InterruptsHandler_Interface.c
* Description: Source file for Interrupt Module Interface
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/
#include "InterruptsHandler.h"
#include "InterruptsHandler_Interface.h"
/*************************************************************************************/
/*- Function Definitions
-------------------------------*/

void EnableGlobalInterrupts(void)
{
	SET_BIT(SREG_R, GLOBAL_INT);
}

void DisableGlobalInterrupts(void)
{
	CLEAR_BIT(SREG_R, GLOBAL_INT);
}

void install_ISR(peripheralVectorId_t peripheralId,  vectorPtr_t CallBackFun)
{
	if(CallBackFun != NULL_PTR && peripheralId < INVALID_vectorId)
	{
		oldVectors[peripheralId] = CallBackFun;
	}

	
}

void deinstall_ISR(peripheralVectorId_t peripheralId)
{
	if(peripheralId < INVALID_vectorId)
	{
		oldVectors[peripheralId] = handleInterrupt_Default;
	}
}