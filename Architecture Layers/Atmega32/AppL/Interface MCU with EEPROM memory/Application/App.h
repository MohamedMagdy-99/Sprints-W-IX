/*****************************************************************************
* Module: App Module
* File Name: App.h
* Description: Header file for App Module
* Author: Mohamed Magdy
* Date: 23-July-2021
******************************************************************************/


#ifndef APP_H_
#define APP_H_

/*- INCLUDES -----------------------------------------------*/
#include "../ECUAL/Eeprom Driver/EEPROM_24.h"
#include "../MCAL/Uart Driver/Uart.h"
#include "../Microcontroller/Utility Module/Utility.h"
/*- CONSTANTS ----------------------------------------------*/
#define WRITE		395
#define READ		284
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