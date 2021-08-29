/*****************************************************************************
* Module: OS Module
* File Name: OS_Cfg.h
* Description: Header file for OS Module
* Author: Mohamed Magdy
* Date: 28-Aug-2021
******************************************************************************/


#ifndef OS_CFG_H_
#define OS_CFG_H_

 /*- Constants
 -------------------------------*/
 #define OS_BASE_SYSTICKS_TIMERTICKS	(125U) /* N ticks for 8Mhz 8 bits timer is 1ms */
 
 #define MAX_NUM_TASKS					(5U)

 #define MAX_PRIOIRTY					(255U)  /* 0 is least priority */
 
 #define CPU_LOAD_FRAME					(10U)  /* N OS ticks */
 
 #define CPU_LOAD_CALC_CYCLES			(2u)    /* calculate CPU load N times every CPU_LOAD_FRAME  */

#endif /* OS_CFG_H_ */