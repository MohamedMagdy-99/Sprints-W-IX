/*****************************************************************************
* Module: Atm Module
* File Name: AtmECU.c
* Description: Header file for Atm Module
* Author: Mohamed Magdy
* Date: 28-July-2021
******************************************************************************/


#ifndef CARDAPP_H_
#define CARDAPP_H_

/*- INCLUDES -----------------------------------------------*/
#include "../MCAL/Dio Driver/Dio.h"
#include "../MCAL/Spi Driver/Spi.h"
#include "../MCAL/Uart Driver/Uart.h"
#include "../ECUAL/Lcd Driver/Lcd.h"
#include "../ECUAL/Keypad Driver/Keypad.h"
#include "../ECUAL/Lm35 Driver/Lm35.h"
#include "../ECUAL/Motor Driver/Motor.h"
#include "../ECUAL/Eeprom Driver/EEPROM_24.h"
#include "../MCAL/Interrupt Driver/ISR.h"
/*- CONSTANTS ----------------------------------------------*/
#define CardRequestSignal_Pin		PORTC_PIN2_ID

#define atmMode_size					6
#define adminChoice_size				2

/* firs time data section */
#define FirstTimeFlagAddress			0

#define AdminPasscode					"7410"
#define AdminPasscode_size				5
#define AddminPasscodeAddress			1

#define FirstTimeDataAvailable			0xBB
#define FirstTimeDataNotAvailable		0xFF

#define DefaultMaxAmount				"5000.00"
#define MaxAmountSize					8
#define MaxAmountAddress				16
/****************************************************************/
/* customer section */
#define CustomerDataNotAvailable		0xFF
#define CustomerDataAvailable			0xAF

#define CustomerMaxNumber				10
#define CustomerMaxNumberAddress		8

#define CurrentCustomersSaved			Initial_Value
#define CurrentCustomersSavedAddress	9

#define CustomerDataFlagAddress			7

#define PAN_size						10
#define PIN_size						5
#define Balance_size					8

#define FirstCustomerPANAddress			32
#define FirstCustomerBalanceAdress		48
#define BytesPerPage					16
#define CustomerAddressDataOffset		BytesPerPage*2

/****************************************************************/
#define CustomerDataChoice				9
#define MaxAmountChoice					8
#define EXIT							10

#define SessionIsActive					0xAB
#define SessionIsInActive				0xAF


#define InsertCardButtonPresssed		0xEF
#define InsertCardButtonNotPresssed		0xDC

#define MotorSpeed						50

#define DisplayMsgDelay					5000
#define MotorWorkTime_ms				1000
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
typedef enum
{
	ATM_STATUS_ERROR_NOK,
	ATM_STATUS_ERROR_OK
	
}enuAtm_Status_t;

typedef enum
{
	ATM_IDLE_MODE,
	ATM_PROGRAMMING_MODE,
	ATM_USER_MODE
	
}enuAtm_Mode_t;

typedef enum
{
	PASS_CODE_VALID,
	PASS_CODE_INVALID
	
}enuPasscode_Status_t;


typedef enum
{
	USER_NO_CHOICE_YET,
	USER_INSERT_CARD,
	USER_GET_TEMP,
	USER_INVALID_CHOICE
	
}enuUserMode_Choice_t;
/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/

enuAtm_Status_t Atm_Init(void);
enuAtm_Status_t Atm_Update(void);

enuAtm_Status_t getMaxAmount(void);
enuAtm_Status_t getMode(void);
enuAtm_Status_t getPasscode(void);
enuAtm_Status_t getAdminChoice(void);
enuAtm_Status_t getPAN(void);
enuAtm_Status_t getBalance(void);
enuAtm_Status_t getUserDataFromEeprom(uint8_t u8_userId);
enuAtm_Status_t getUserInputKeypad(void);
enuAtm_Status_t Lcd_userModeMainMenu(void);
enuAtm_Status_t getMode_userModeVersion(void);
enuAtm_Status_t getUserPIN_Keypad(void);
enuAtm_Status_t getUserAmount_Keypad(void);
enuAtm_Status_t getTemp(void);
enuAtm_Status_t welcomeMessage(void);
enuAtm_Status_t maxAmountExceeded(void);
enuAtm_Status_t PANnotExist(void);
enuAtm_Status_t insufficientFund(void);
enuAtm_Status_t transactionApproved(void);
uint8_t checkIfPAN_ExistsInServer(void);
uint8_t compareUserAmountWithBalance(void);
enuAtm_Status_t Server_Update(void);
enuAtm_Status_t Server_Init(void);
enuAtm_Status_t updateMaxAmountInEeprom(void);
enuAtm_Status_t saveNewUserDataInEeprom(void);
enuAtm_Status_t enterPIN_Lcd(void);
enuAtm_Status_t enterAmount_Lcd(void);
enuAtm_Status_t incorrectPIN_message(void);
enuAtm_Status_t saveUserNewBalance(uint8_t u8_userId);
enuAtm_Status_t updateBalanceAfterTransaction(void);
uint8_t compareUserAmountWithMaxAmount(void);

void FunctionWhenCardInsertedPressed(void);





#endif /* CARDAPP_H_ */