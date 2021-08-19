/*****************************************************************************
* Module: Lm35 Module
* File Name: Lm35.h
* Description: Header file for Lm35 Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/

#ifndef LM35_H_
#define LM35_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../../MCAL/Adc Driver/Adc.h"

/* CONSTANT */
#define SensorResolution_Millivolts		10


/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
 * Data Type for Motor return status
 */
typedef enum
{
	LM35_STATUS_ERROR_NOK,
	LM35_STATUS_ERROR_OK,
	
}enuLm35_Status_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
enuLm35_Status_t Lm35_init(void);

enuLm35_Status_t Lm35_getTemp(uint8_t u8_channelId, uint8_t* u8_temperature);



#endif /* LM35_H_ */