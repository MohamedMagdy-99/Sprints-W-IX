/*****************************************************************************
* Module: Keypad Module
* File Name: Keypad_Cfg.h
* Description: Header file for Keypad Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#include "Keypad.h"

#define Keypad_PinsNumber	8
#define Number_Rows			4
#define Number_Columns		4



#define ROW_1_DIO_ID			PORTC_PIN4_ID
#define ROW_2_DIO_ID			PORTC_PIN5_ID
#define ROW_3_DIO_ID			PORTC_PIN6_ID
#define ROW_4_DIO_ID			PORTC_PIN7_ID
									
#define COLUMN_1_DIO_ID			PORTC_PIN0_ID
#define COLUMN_2_DIO_ID			PORTC_PIN1_ID
#define COLUMN_3_DIO_ID			PORTC_PIN2_ID
#define COLUMN_4_DIO_ID			PORTC_PIN3_ID


#endif /* KEYPAD_CFG_H_ */