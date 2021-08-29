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
 #define OS_BASE_SYSTICKS_TIMERTICKS	(125U) // 125 ticks for 8Mhz 8 bits timer is 1ms
 
 #define MAX_NUM_TASKS					(5U)

 #define MAX_PRIOIRTY					(255U)  /* 0 is least priority */

#endif /* OS_CFG_H_ */