/*****************************************************************************
* Module: Spi Module
* File Name: Spi_Cfg.h
* Description: Header file for UART Module
* Author: Mohamed Magdy
* Date: 19-July-2021
******************************************************************************/


#ifndef SPI_CFG_H_
#define SPI_CFG_H_

/* CONSTANTS */
/**********************/
/* dataOrder */
#define MSB_FIRST		0
#define LSB_FIRST		1
/* clockPolarity */
#define SCK_HIGH_IDLE	0
#define SCK_LOW_IDLE	1
/* clockPhase */
#define SAMPLE_LEADING	0
#define SAMPLE_FALLING	1
/* clockRate */
#define DIV_4			0
#define DIV_16			1
#define DIV_64			2
#define DIV_128			3
#define DIV_2			4
#define DIV_8			5
#define DIV_32			6

 /* selectMaster_or_Slave */
#define MASTER_SPI			0xC0
#define SLAVE_SPI			0xEE

/* DIO Pins ID */
#define MISO	PORTB_PIN6_ID
#define MOSI	PORTB_PIN5_ID
#define SS		PORTB_PIN4_ID
#define SCK		PORTB_PIN7_ID
/* selectMaster_or_Slave */



#endif /* SPI_CFG_H_ */