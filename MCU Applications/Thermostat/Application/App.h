/*****************************************************************************
* Module: App Module
* File Name: App.h
* Description: Header file for App Module
* Author: Mohamed Magdy
* Date: 25-July-2021
******************************************************************************/


#ifndef APP_H_
#define APP_H_

/*- INCLUDES -----------------------------------------------*/
#include "../ECUAL/Lcd Driver/Lcd.h"
#include "../ECUAL/Keypad Driver/Keypad.h"
#include "../MCAL/Dio Driver/Dio.h"
#include "../ECUAL/Lm35 Driver/Lm35.h"
/*- CONSTANTS ----------------------------------------------*/


/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
typedef enum
{
	APP_STATUS_ERROR_NOK,
	APP_STATUS_ERROR_OK,

}enuApp_Status_t;

/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/

enuApp_Status_t App_Init(void);
enuApp_Status_t App_Update(void);


#endif /* APP_H_ */