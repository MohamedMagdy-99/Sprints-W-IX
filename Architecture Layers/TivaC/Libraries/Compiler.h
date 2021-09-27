 /******************************************************************************
 *
 * Module: Common - Compiler Abstraction
 *
 * File Name: Compiler.h
 *
 * Description:  This file contains the definitions and macros specified
 *               for the abstraction of compiler specific keywords.
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/

#ifndef COMPILER_H
#define COMPILER_H

/* The memory class is used for the declaration of local pointers */
#define AUTOMATIC

/* The memory class is used within type definitions, where no memory
   qualifier can be specified */
#define TYPEDEF

/* This is used to define the void pointer to zero definition */
#define NULL_PTR          ((void *)0)

/* This is used to define the abstraction of compiler keyword inline */
#define INLINE            inline

/* This is used to define the local inline function */
#define LOCAL_INLINE      static inline

/* This is used to define the abstraction of compiler keyword static */
#define STATIC            static

/* Switch to unprivileged mode */
#define Switch_CPU_Unprivileged()\
   __asm("MRS R0, CONTROL");\
   __asm("ORR R0, R0, #0x01");\
   __asm("MSR CONTROL, R0")

/* Switch to privileged mode */
#define Switch_CPU_Privileged() \
   __asm("MRS R0, CONTROL");\
   __asm("AND R0, R0, #0xFE");\
   __asm("MSR CONTROL, R0")

/* Pend SVC Interrupt */
#define SVCall_Pend()                __asm("SVC #0x00")

/* Enable Global Interrupts. */
#define Enable_GlobalInterrupts()\
     __asm("CPSIE I");\
     __asm("CPSIE F")
     
/* Disable Global Interrupts. */
#define Disable_GlobalInterrupts()\
         __asm("CPSID I");\
         __asm("CPSID F")


#endif
