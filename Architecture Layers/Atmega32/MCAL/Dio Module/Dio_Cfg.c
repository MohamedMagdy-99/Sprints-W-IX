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
	/* SPI Slave */
	{  PORT_B    ,   PIN_4       , DIO_PIN_DIR_INPUT   ,  PIN_PUR  },
	{  PORT_B    ,   PIN_5       , DIO_PIN_DIR_INPUT   ,  PIN_PUR  },
	{  PORT_B    ,   PIN_6       , DIO_PIN_DIR_OUTPUT  ,  PIN_LOW  },
	{  PORT_B    ,   PIN_7       , DIO_PIN_DIR_INPUT   ,  PIN_PUR  },
	/* interrupt pin card insertion button */
	{  PORT_D    ,   PIN_2       , DIO_PIN_DIR_INPUT   ,  PIN_PUR  },
	/* keypad */
	{  PORT_A    ,   PIN_1       , DIO_PIN_DIR_INPUT   ,  PIN_PUR  },
	{  PORT_A    ,   PIN_2       , DIO_PIN_DIR_INPUT   ,  PIN_PUR  },
	{  PORT_A    ,   PIN_3       , DIO_PIN_DIR_INPUT   ,  PIN_PUR  },
	{  PORT_A    ,   PIN_4       , DIO_PIN_DIR_INPUT   ,  PIN_PUR  },
	{  PORT_A    ,   PIN_5       , DIO_PIN_DIR_OUTPUT  ,  PIN_HIGH },
	{  PORT_A    ,   PIN_6       , DIO_PIN_DIR_OUTPUT  ,  PIN_HIGH },
	{  PORT_A    ,   PIN_7       , DIO_PIN_DIR_OUTPUT  ,  PIN_HIGH },
	{  PORT_C    ,   PIN_3       , DIO_PIN_DIR_OUTPUT  ,  PIN_HIGH },
	/* LCD */
	{  PORT_C    ,   PIN_5       , DIO_PIN_DIR_OUTPUT   ,  PIN_LOW },
	{  PORT_C    ,   PIN_6       , DIO_PIN_DIR_OUTPUT   ,  PIN_LOW },
	{  PORT_C    ,   PIN_7       , DIO_PIN_DIR_OUTPUT   ,  PIN_LOW },
	{  PORT_D    ,   PIN_4       , DIO_PIN_DIR_OUTPUT   ,  PIN_LOW },
	{  PORT_D    ,   PIN_5       , DIO_PIN_DIR_OUTPUT   ,  PIN_LOW },
	{  PORT_D    ,   PIN_6       , DIO_PIN_DIR_OUTPUT   ,  PIN_LOW },
	{  PORT_D    ,   PIN_7       , DIO_PIN_DIR_OUTPUT   ,  PIN_LOW },
    /* temp sensor */
	{  PORT_A    ,   PIN_0       , DIO_PIN_DIR_INPUT   ,  PIN_NO_PUR  },	
	/* Motor control */	
	{  PORT_B    ,   PIN_0       , DIO_PIN_DIR_OUTPUT  ,  PIN_LOW  },
	{  PORT_B    ,   PIN_1       , DIO_PIN_DIR_OUTPUT  ,  PIN_LOW  },
	{  PORT_B    ,   PIN_2       , DIO_PIN_DIR_OUTPUT  ,  PIN_LOW  },
	/* request data from card signal */		
	{  PORT_C    ,   PIN_2       , DIO_PIN_DIR_OUTPUT  ,  PIN_HIGH },			
};   