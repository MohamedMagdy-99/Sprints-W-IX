/*****************************************************************************
* Module: I2C Module
* File Name: I2C_Cfg.h
* Description: Header file for I2C Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/ 


#ifndef I2C_CFG_H_
#define I2C_CFG_H_

/* CONSTANTS */
#define F_OSC		8000000UL
#define I2C_SCL_CLK 25000UL

#define PRESCALER_1		1
#define PRESCALER_4		4
#define PRESCALER_16	16
#define PRESCALER_64	64

#define PRESCALER		PRESCALER_16

#define MASTER_I2C				0xAB
#define SLAVE_I2C				0xFF

#define SLAVE_ADDRESS		0x20

#define SLAVE_ADDRESS_W		(SLAVE_ADDRESS<<1)
#define SLAVE_ADDRESS_R		(SLAVE_ADDRESS<<1) | (1)





#endif /* I2C_CFG_H_ */