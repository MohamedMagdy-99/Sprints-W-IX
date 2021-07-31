/*****************************************************************************
* Module: Uart Module
* File Name: Uart_Cfg.c
* Description: Source file for UART Module
* Author: Mohamed Magdy
* Date: 19-July-2021
******************************************************************************/


/*- INCLUDES
----------------------------------------------*/
#include "Uart.h"


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* configuration of used timer channels */
strUart_Config_t strUart_Config =
{
	/* Parity */         /* stop bits*/   /* data size */    /* baud rate*/        /*  uart rate */
	  NO_PARITY    ,       ONE_STOP_BIT  ,   DATA_8BITS  ,    BR_4800          ,    SINGLE_RATE     
	
};