/*****************************************************************************
* Module: Dio Module
* File Name: Dio_Cfg.c
* Description: Source file for DIO Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/


/*- INCLUDES
----------------------------------------------*/
#include "Dio.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* configuration of pins to be used */
strDio_Config_t strDio_pins[DIO_USED_PINS_NUM]=
{
	/*Port Number*/ /*Pin Number*/  /*Direction*/      /*Initial State*/
	{  PORT_D    ,   PIN_5       , DIO_PIN_DIR_OUTPUT   , PIN_LOW    },
	{  PORT_D    ,   PIN_6       , DIO_PIN_DIR_OUTPUT   , PIN_LOW    },
	{  PORT_D    ,   PIN_7       , DIO_PIN_DIR_OUTPUT   , PIN_LOW    }



};   