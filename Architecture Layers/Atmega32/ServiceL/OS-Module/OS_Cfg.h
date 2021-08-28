/*
 * OS_Cfg.h
 *
 * Created: 28-Aug-21 5:22:58 PM
 *  Author: Megz
 */ 


#ifndef OS_CFG_H_
#define OS_CFG_H_

 /*- Constants
 -------------------------------*/
 #define OS_BASE_SYSTICKS_TIMERTICKS	(125U) // 125 ticks for 8Mhz 8 bits timer is 1ms
 
 #define MAX_NUM_TASKS					(5U)

 #define MAX_PRIOIRTY					(255U)

#endif /* OS_CFG_H_ */