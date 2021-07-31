/*****************************************************************************
* Module: Dio Module
* File Name: Dio_Cfg.h
* Description: Header file for DIO Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/

#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/* CONSTANTS */

/* user set the number of pins used in the project */

#define DIO_USED_PINS_NUM   5


/* CONSTANTS */
#define PIN_0		0
#define PIN_1		1
#define PIN_2		2
#define PIN_3		3
#define PIN_4		4
#define PIN_5		5
#define PIN_6		6
#define PIN_7		7

#define PORT_A		0
#define PORT_B		1
#define PORT_C		2
#define PORT_D		3

#define PIN_LOW		0U
#define PIN_HIGH	1U

#define PIN_PUR		2U /* Pull Up Resistor */
#define PIN_NO_PUR  3U /* No Pull Up Resistor */

#define PORTB_PIN4_ID	0
#define PORTB_PIN5_ID	1
#define PORTB_PIN6_ID	2
#define PORTB_PIN7_ID	3

#define PORTD_PIN2_ID	4
#endif /* DIO_CFG_H_ */