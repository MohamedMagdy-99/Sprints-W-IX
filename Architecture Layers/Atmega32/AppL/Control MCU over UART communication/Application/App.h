/*****************************************************************************
* Module: App Module
* File Name: App.h
* Description: Header file for App Module
* Author: Mohamed Magdy
* Date: 20-July-2021
******************************************************************************/


#ifndef APP_H_
#define APP_H_

/*- INCLUDES -----------------------------------------------*/
#include "../ECUAL/Led Driver/Led.h"
#include "../MCAL/Uart Driver/Uart.h"

/*- CONSTANTS ----------------------------------------------*/
#define START				398
#define WAIT				309
#define STOP				326
#define AT					149
#define MAX_COMMAND_CHARS	5
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