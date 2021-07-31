/*****************************************************************************
* Module: Utility Module
* File Name: Utility.h
* Description: Source file for Utility Module
* Author: Mohamed Magdy
* Date: 23-July-2021
******************************************************************************/

#ifndef UTILITY_H_
#define UTILITY_H_

#include "../Std_Types.h"

#define DEC		0
#define HEX		1	
#define BIN		2

#define END_OF_STRING '\0'
#define NEW_LINE	  '\r'
#define BACK_SPACE	  '\b'

uint16_t String_3ByteHexAddress_ToDecimal(uint8_t* u8_tempAddress);
void integerToString(uint16_t u16_Num, uint8_t *pu8_String, uint8_t u8_base);
void stringToInteger(uint8_t* au8_string, uint32_t* u32_integer);
uint32_t nPowerM(uint32_t n, uint32_t m);
uint8_t stringCmp(uint8_t * str1, uint8_t * str2);
void separateInteger(uint8_t* pau8_floatString, uint8_t* pau8_integerString, uint16_t u16_lengthToStop);
void separateDecimal(uint8_t* pau8_floatString, uint8_t* pau8_decimalString, uint16_t u16_lengthToStart,  uint16_t u16_floatArraySize);
#endif /* UTILITY_H_ */