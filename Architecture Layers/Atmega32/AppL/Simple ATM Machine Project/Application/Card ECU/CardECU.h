/*****************************************************************************
* Module: Card Module
* File Name: CardECU.c
* Description: Header file for Card Module
* Author: Mohamed Magdy
* Date: 27-July-2021
******************************************************************************/


#ifndef CARDAPP_H_
#define CARDAPP_H_

/*- INCLUDES -----------------------------------------------*/
#include "../MCAL/Dio Driver/Dio.h"
#include "../MCAL/Spi Driver/Spi.h"
#include "../MCAL/Uart Driver/Uart.h"
#include "../ECUAL/Eeprom Driver/EEPROM_24.h"
#include "../MCAL/Interrupt Driver/ISR.h"
/*- CONSTANTS ----------------------------------------------*/

#define EepromFlagAddress	0x00
#define EpromEmpty			0xFF
#define EepromHasData		0xCD

#define PAN_SIZE			10
#define PanAddress			0x01

#define PIN_SIZE_EE			5
#define PIN_SIZE_ARR		10
#define PinAddress			0x0B

#define USER_MODE_MAX		10

#define ExternalAtmEcuSignal	PORTD_PIN2_ID
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
typedef enum
{
	CARD_STATUS_ERROR_NOK,
	CARD_STATUS_ERROR_OK,
	
}enuCard_Status_t;

typedef enum
{
	CARD_IDLE_MODE,
	CARD_PROGRAMMING_MODE,
	CARD_USER_MODE
	
}enuCard_Mode_t;
/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/

enuCard_Status_t Card_Init(void);
enuCard_Status_t Card_Update(void);

enuCard_Status_t getPAN(void);

enuCard_Status_t getPIN(void);
void FunctionWhenATM_WantsCardData(void);



enuCard_Status_t getMode_userModeVersion(void);
#endif /* CARDAPP_H_ */