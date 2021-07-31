/*****************************************************************************
* Module: Uart Module
* File Name: Uart_Cfg.h
* Description: Header file for UART Module
* Author: Mohamed Magdy
* Date: 19-July-2021
******************************************************************************/


#ifndef UART_CFG_H_
#define UART_CFG_H_

#define UART_FREQ	8000000UL


#define NO_PARITY		0
#define ODD_PARITY		1
#define EVEN_PARTIY		2

#define ONE_STOP_BIT	0
#define TWO_STOP_BIT	1

#define DATA_5BITS		0
#define DATA_6BITS		1
#define DATA_7BITS		2
#define DATA_8BITS		3
#define DATA_9BITS		4

#define BR_2400			2400
#define BR_4800			4800
#define BR_9600			9600
#define BR_14400	    14400
#define BR_19200	    19200
#define BR_28800	    28800

#define SINGLE_RATE		0
#define DOUBLE_RATE		1



#endif /* UART_CFG_H_ */