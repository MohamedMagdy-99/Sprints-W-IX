/******************************************************************************
 *
 * Module: Standard - Types
 *
 * File Name: Std_Types.h
 *
 * Description: Commonly used standard data types
 *
 * Author: Mohamed Magdy
 *
 * Date: 14-July-2021
 *******************************************************************************/

#ifndef STD_TYPES_H_INCLUDED
#define STD_TYPES_H_INCLUDED


/*
 * Boolean Values
 */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

typedef unsigned char         boolean;

typedef unsigned char         uint8_t;          /*           0 .. 255             */
typedef signed char           sint8_t;          /*        -128 .. +127            */
typedef unsigned short        uint16_t;         /*           0 .. 65535           */
typedef signed short          sint16_t;         /*      -32768 .. +32767          */
typedef unsigned long         uint32_t;         /*           0 .. 4294967295      */
typedef signed long           sint32_t;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64_t;         /*       0..18446744073709551615  */
typedef signed long long      sint64_t;
typedef float                 float32_t;
typedef double				  float64_t;

#define Initial_Value	0x00U
#define Null_Ptr	(void* 0)

#define STD_HIGH        0x01U       /* Standard HIGH */
#define STD_LOW         0x00U       /* Standard LOW */

#endif // STD_TYPES_H_INCLUDED
