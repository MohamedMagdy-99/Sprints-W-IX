/*****************************************************************************
* Module: Keypad Module
* File Name: Keypad.h
* Description: Header file for Keypad Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/


#ifndef KEYPAD_H_
#define KEYPAD_H_


/* INCLUDES */

#include "../../Microcontroller/Std_Types.h"
#include "../../Microcontroller/Common_Macros.h"
#include "../../MCAL/Dio Driver/Dio.h"
#include "Keypad_Cfg.h"
#include "../../Microcontroller/Delay Module/Delay.h"

/* CONSTANTS */
#define NO_KEY_PRESSED		0xFF

#define ROW_1					0
#define ROW_2					1
#define ROW_3					2
#define ROW_4					3

#define COLUMN_1				0
#define COLUMN_2				1
#define COLUMN_3				2	
#define COLUMN_4				3

/*- ENUMS --------------------------------------------------*/
typedef enum
{
	KEYPAD_STATUS_ERROR_NOK,
	KEYPAD_STATUS_ERROR_OK

}enuKeypad_Status_t;


/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/


enuKeypad_Status_t Keypad_init(void);
enuKeypad_Status_t KeypadScan(uint8_t* u8_pressedKey);



#endif /* KEYPAD_H_ */