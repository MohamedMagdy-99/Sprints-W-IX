/*****************************************************************************
* Module: Atm Module
* File Name: AtmECU.c
* Description: Source file for Atm Module
* Author: Mohamed Magdy
* Date: 28-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "AtmECU.h"
#include "../MCAL/Interrupt Driver/ISR.h"
#include "../Microcontroller/Utility Module/Utility.h"


/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuAtm_Mode_t enuAtmMode = ATM_IDLE_MODE;  //store the current mode of the atm

enuUserMode_Choice_t enuUserMode = USER_NO_CHOICE_YET;  //user mode choice

enuPasscode_Status_t enuPassCodeStatus = PASS_CODE_INVALID; //admin passcode status

uint8_t gu8_FirstTimeFlag = Initial_Value; //store first time data state

uint8_t gu8_CustomerDataFlag = Initial_Value; //store if customer data available or not
uint8_t gu8_currentNumberOfCustomersStored = Initial_Value; //store the current number of customer accounts stored

uint8_t gau8_passCode[AdminPasscode_size]; //store the entered pass code from terminal

uint8_t gau8_maxAmount[MaxAmountSize]; //store maximum amount for transaction 

uint8_t gau8_atmMode[atmMode_size]; //store the input atm mode from user

uint8_t gau8_adminChoice[adminChoice_size]; //store the input from admin mode in terminal
 
uint8_t gu8_adminCurrentChoice = Initial_Value; //store the chosen mode in admin mode

uint8_t gu8_accessGranted = SessionIsInActive; // flag to monitor the login session of admin mode

uint8_t gau8_PAN[PAN_size];				//store the PAN of a new user
uint8_t gau8_Balance[Balance_size];		//store the balance of a new user

uint8_t gau8_PAN_CardECU[PAN_size]; //store the PAN of the user's card inserted from card ecu
uint8_t gau8_PIN_CardECU[PIN_size]; //store the PIN of the user's card inserted from card ecu

uint8_t gau8_PIN_AtmUser[PIN_size]; //store the PIN of the user's card inserted from atm
uint8_t gau8_Amount_AtmUser[MaxAmountSize]; //store the amount of the user's card inserted from atm

uint8_t gu8_pressedKey = NO_KEY_PRESSED; //keypad input

uint8_t u8_temperature = Initial_Value;  //ATM temperature
uint8_t u8_temperatureString[3];         //ATM temperature string to be displayed

uint8_t* gau8_userAmountIntegerPart[5];	//store integer part of input amount as a string
uint8_t* gau8_userAmountDecimalPart[3];	//store decimal part of input amount as a string

uint8_t* gau8_maxBalanceIntegerPart[5];	//store integer part of max amount as a string
uint8_t* gau8_maxBalanceDecimalPart[3];	//store decimal part of max amount as a string

uint8_t* gau8_BalanceIntegerPart[5];	//store integer part of  balance as a string
uint8_t* gau8_BalanceDecimalPart[3];	//store decimal part of  balance as a string

uint32_t gu32_userInputAmount_IntValue;	//store integer part of user input amount as a integer
uint32_t gu32_userInputAmount_DecValue;	//store decimal part of user input amount as a integer

uint32_t gu32_MaxAmount_IntValue;	//store integer part of max amount as a integer
uint32_t gu32_MaxAmount_DecValue;	//store decimal part of max amount as a integer

uint32_t gu32_userBalanceAmount_IntValue;	//store integer part of user balance as a integer
uint32_t gu32_userBalanceAmount_DecValue;	//store decimal part of user balance as a integer

volatile uint8_t gu8_insertButtonPressedFlag = InsertCardButtonNotPresssed; //flag to indicate if insert button was pressed or not
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/


/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuCar_Status_t
* Description: initializes the car module by initializing the modules used in it
************************************************************************************/
enuAtm_Status_t Atm_Init(void)
{
	/* modules initialization */
	Dio_init();
	Uart_init();
	Spi_init();
	Eeprom_24_init();
	Motor_init();
	Keypad_init();
	Lcd_init();
	Lm35_init();
	
	/* interrupt setting */
	EnableExternalInterrupts_INT0(LOW_LEVEL);
	setExtINT0Callback(FunctionWhenCardInsertedPressed);

	
	/* welcome message */
	welcomeMessage();
	
	/* virtual terminal message */
	Uart_syncTransmit_string("ATM Terminal\r*************\r");
	
	/* check if it's first boot or not */
	Eeprom_24_readByte(FirstTimeFlagAddress, &gu8_FirstTimeFlag);
	if(gu8_FirstTimeFlag == FirstTimeDataNotAvailable)
	{
		/* set server data for first time usage */
		Server_Init();
	}
	else
	{
		/* get constant data from server */
		Server_Update();

	}		
	/* get user input */
	getMode();
	
	return ATM_STATUS_ERROR_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuCar_Status_t
* Description: main task of the control system, handles all application cases
************************************************************************************/
enuAtm_Status_t Atm_Update(void)
{
		/* welcome message */
		welcomeMessage();
	/**************************************************************************************************/
	/*********************************** PROGRAMMING MODE *********************************************/
	/**************************************************************************************************/
	
	if(enuAtmMode == ATM_PROGRAMMING_MODE)
	{
		Uart_syncTransmit_string("\rYou are now in ADMIN mode\r");
		
		if(gu8_accessGranted == SessionIsInActive)
		{
			/* ask user to enter the admin pass code and check for it */
			getPasscode();
			
			if(enuAtmMode == ATM_USER_MODE)
			{
				return ATM_STATUS_ERROR_OK;
			}
			else
			{
				gu8_accessGranted = SessionIsActive;
			}			
		}

		/* get a choice from the terminal to act upon */
		getAdminChoice();
		
		/* check which option was chosen */
		switch(gu8_adminCurrentChoice)
		{
			case(CustomerDataChoice):
			{
				
				/* get PAN from the user */
				getPAN();
				/* get Balance from the user */
				getBalance();
				Uart_syncTransmit_string("\rProcessing....\r");
				/* save PAN and balance in eeprom */
				saveNewUserDataInEeprom();
				break;
			}
			case(MaxAmountChoice):
			{
				/* get max amount from the user */
				getMaxAmount();
				/* save new max amount in eeprom */
				updateMaxAmountInEeprom();
				break;
			}
			case(EXIT):
			{
				enuAtmMode = ATM_USER_MODE;
				return ATM_STATUS_ERROR_OK;
				break;
			}
			default: break;						
		}
		
	}
	
	/**************************************************************************************************/
	/*********************************** USER MODE ****************************************************/
	/**************************************************************************************************/
	
	else if(enuAtmMode == ATM_USER_MODE)
	{
		Uart_syncTransmit_string("\rYou are now in USER mode\r");
		/* log out from ADMIN mode */
		gu8_accessGranted = SessionIsInActive;
		
		/* check if data is available */
		if(gu8_CustomerDataFlag == CustomerDataNotAvailable)
		{
			enuAtmMode = ATM_PROGRAMMING_MODE;
			Uart_syncTransmit_string("\rThere is no data available, you will be directed to ADMIN mode\r");
			return ATM_STATUS_ERROR_OK;
		}
		else
		{
			
			getMode_userModeVersion();
			if(enuAtmMode == ATM_PROGRAMMING_MODE)
			{
				return ATM_STATUS_ERROR_OK;
			}
			Lcd_userModeMainMenu();
			/* get input from keypad */
			getUserInputKeypad();
			switch(enuUserMode)
			{
				/************************ TRANSACTION CASE *********************************/
				case(USER_INSERT_CARD):
				{
		     		Uart_syncTransmit_string("\rYou chose Insert Card\rPlease press the insert card button and follow instructions on LCD\r");
					/* wait till user press insert card button */
					while(gu8_insertButtonPressedFlag == InsertCardButtonNotPresssed);
					/* reset the insert card flag */
					gu8_insertButtonPressedFlag = InsertCardButtonNotPresssed;
					/* get user pin number */
					/* set the LCD for PIN */
					enterPIN_Lcd();
					/* get the PIN */
					getUserPIN_Keypad();
					/* check if PIN is correct */
					if(stringCmp(gau8_PIN_CardECU, gau8_PIN_AtmUser) == TRUE)
					{
						Uart_syncTransmit_string("\rCorrect PIN\r");
						/* ask for the amount */
						/* set LCD for amount */
						enterAmount_Lcd();
						/* get the amount */
						getUserAmount_Keypad();
						/* compare amount with max amount */
						if(compareUserAmountWithMaxAmount() == TRUE)
						{
							/* check if PAN exists */
							if(checkIfPAN_ExistsInServer() == TRUE)
							{
								/* check if enough balance */
								if(compareUserAmountWithBalance() == TRUE)
								{
									/* transaction approved */
									transactionApproved();
									return ATM_STATUS_ERROR_OK;
								}
								else
								{
									/* insufficient funds */
									insufficientFund();
									return ATM_STATUS_ERROR_OK;									
								}
							}
							else
							{
								/* PAN not found */
								PANnotExist();
								return ATM_STATUS_ERROR_OK;						
							}
						}
						else
						{
							/* max amount exceeded */
							maxAmountExceeded();
							return ATM_STATUS_ERROR_OK;					
						}					
					}
					else
					{
						/* Invalid pin message */
						incorrectPIN_message();
						
						return ATM_STATUS_ERROR_OK;
					}
									
					break;
				}
				/************************ GET TEMP CASE *********************************/
				case(USER_GET_TEMP):
				{
					/* get temp and display it for 5 seconds */
					getTemp();
					return ATM_STATUS_ERROR_OK;
					break;
				}
				default: break;				
			}
			return ATM_STATUS_ERROR_OK;
		}
	}
	/**************************************************************************************************/
	/*********************************** INVALID MODE *************************************************/
	/**************************************************************************************************/
	else
	{
		return ATM_STATUS_ERROR_NOK;
	}

	return ATM_STATUS_ERROR_OK;
}









/**************************************************************************************************/
/*********************************** USED FUNCTIOS ************************************************/
/**************************************************************************************************/

enuAtm_Status_t incorrectPIN_message(void)
{
	Lcd_sendCommand(CLEAR);
	Lcd_cursorPosition(1,1);
	Lcd_sendString("INCORRECT PIN");
	Uart_syncTransmit_string("\rIncorrecnt PIN, the process will be terminated\r");
	Delay_ms(DisplayMsgDelay);	
	
	return ATM_STATUS_ERROR_OK;
}


enuAtm_Status_t Server_Update(void)
{
	/* get current customers saved */
	Eeprom_24_readByte(CurrentCustomersSavedAddress, &gu8_currentNumberOfCustomersStored);
	/* get maximum amount */
	Eeprom_24_readPacket(MaxAmountAddress, gau8_maxAmount, MaxAmountSize);
	/* get customer data flag */
	Eeprom_24_readByte(CustomerDataFlagAddress, &gu8_CustomerDataFlag);
	
	return ATM_STATUS_ERROR_OK;
}


enuAtm_Status_t Server_Init(void)
{
	/* save admin pass code */
	Eeprom_24_writePacket(AddminPasscodeAddress, AdminPasscode, AdminPasscode_size);
	/* save default max amount */
	Eeprom_24_writePacket(MaxAmountAddress, DefaultMaxAmount, MaxAmountSize);
	/* save max customers */
	Eeprom_24_writeByte(CustomerMaxNumberAddress, CustomerMaxNumber);
	/* initialize current customers */
	Eeprom_24_writeByte(CurrentCustomersSavedAddress, CurrentCustomersSaved);
	
	/* set flag to data available */
	Eeprom_24_writeByte(FirstTimeFlagAddress, FirstTimeDataAvailable);
	
	/* set customer data flag to not available */
	Eeprom_24_writeByte(CustomerDataFlagAddress, CustomerDataNotAvailable);
	
	return ATM_STATUS_ERROR_OK;
}


enuAtm_Status_t updateMaxAmountInEeprom(void)
{
	Eeprom_24_writePacket(MaxAmountAddress, gau8_maxAmount, MaxAmountSize);
	Uart_syncTransmit_string("\rMaximum amount was updated successfully!\r");	
	
	return ATM_STATUS_ERROR_OK;
}

enuAtm_Status_t saveNewUserDataInEeprom(void)
{
	/* save PAN in eeprom */
	Eeprom_24_writePacket((FirstCustomerPANAddress+(gu8_currentNumberOfCustomersStored*CustomerAddressDataOffset)),
	gau8_PAN, PAN_size);
	/* save balance in eeprom */
	Eeprom_24_writePacket((FirstCustomerBalanceAdress+(gu8_currentNumberOfCustomersStored*CustomerAddressDataOffset)),
	gau8_Balance, Balance_size);
	/* increase the number of currently saved customers */
	gu8_currentNumberOfCustomersStored++;
	/* store currently saved customers in eeprom */
	Eeprom_24_writeByte(CurrentCustomersSavedAddress, gu8_currentNumberOfCustomersStored);
	/* success message */
	Uart_syncTransmit_string("\rA new account has been added successfully!\r");
	/* update customer data flag */
	gu8_CustomerDataFlag = CustomerDataAvailable;
	/* update flag in eeprom */
	Eeprom_24_writeByte(CustomerDataFlagAddress, CustomerDataAvailable);
	return ATM_STATUS_ERROR_OK;
}



enuAtm_Status_t enterPIN_Lcd(void)
{
	Lcd_sendCommand(CLEAR);
	Lcd_cursorPosition(1,1);
	Lcd_sendString("Enter PIN:");
	Lcd_cursorPosition(2,1);
	
	return ATM_STATUS_ERROR_OK;
}


enuAtm_Status_t enterAmount_Lcd(void)
{
	Lcd_sendCommand(CLEAR);
	Lcd_cursorPosition(1,1);
	Lcd_sendString("Enter Amount:");
	Lcd_cursorPosition(2,1);	
	
	return ATM_STATUS_ERROR_OK;
}




enuAtm_Status_t getTemp(void)
{
	Uart_syncTransmit_string("\rYou chose Get Temp, the temperature will be displayed for 5 seconds\r");
	/* get temp from sensor */
	Lm35_getTemp(ADC0_ID, &u8_temperature);
	if(u8_temperature > 99) u8_temperature = 99;
	/* convert int temperature to string */
	integerToString(u8_temperature, u8_temperatureString, DEC);
	/* set the LCD and print temp for 5 secs */
	Lcd_sendCommand(CLEAR);
	Lcd_cursorPosition(1,1);
	Lcd_sendString("Current Temp: ");
	Lcd_cursorPosition(2,1);
	Lcd_sendString(u8_temperatureString);
	Lcd_sendCharacter(' ');
	Lcd_sendCharacter(223);
	Lcd_sendCharacter('C');
	Delay_ms(DisplayMsgDelay);
	return ATM_STATUS_ERROR_OK;
}
enuAtm_Status_t welcomeMessage(void)
{
	Lcd_sendCommand(CLEAR);
	Lcd_cursorPosition(1,1);
	Lcd_sendString("   Welcome to");
	Lcd_cursorPosition(2,1);
	Lcd_sendString("  SunBytes Bank");
	
	return ATM_STATUS_ERROR_OK;
}

enuAtm_Status_t maxAmountExceeded(void)
{
	
	Lcd_sendCommand(CLEAR);
	Lcd_cursorPosition(1,1);
	Lcd_sendString("Max allowed cash:");
	Lcd_cursorPosition(2,1);
	Lcd_sendString(gau8_maxAmount);
	Uart_syncTransmit_string("\rMax Amount Exceeded, the process will be terminated\r");
	Delay_ms(DisplayMsgDelay);
	
	return ATM_STATUS_ERROR_OK;
}

	
enuAtm_Status_t PANnotExist(void)
	{
		Lcd_sendCommand(CLEAR);
		Lcd_cursorPosition(1,1);
		Lcd_sendString("ERROR: Card not");
		Lcd_cursorPosition(2,1);
		Lcd_sendString("registered");
		Uart_syncTransmit_string("\rSorry, your account doesn't exist in our servers, the process will be terminated\r");
		Delay_ms(DisplayMsgDelay);
		return ATM_STATUS_ERROR_OK;								
	}


enuAtm_Status_t insufficientFund(void)
{
	Lcd_sendCommand(CLEAR);
	Lcd_cursorPosition(1,1);
	Lcd_sendString("  Insufficient");
	Lcd_cursorPosition(2,7);
	Lcd_sendString("Fund");
	Uart_syncTransmit_string("\rSorry, Insufficient Fund, the process will be terminated\r");
	Delay_ms(DisplayMsgDelay);
	return ATM_STATUS_ERROR_OK;
}

enuAtm_Status_t transactionApproved(void)
{
	Lcd_sendCommand(CLEAR);
	Lcd_cursorPosition(1,1);
	Lcd_sendString("   Transaction");
	Lcd_cursorPosition(2,1);
	Lcd_sendString("    Approved");
	Uart_syncTransmit_string("\rYour transaction is approved!\rThank you for banking with us\r");
	/* rotate motor for 1 sec */
	Motor_moveForward(MOTOR_ATM_ID, MotorSpeed);
	Delay_ms(MotorWorkTime_ms);
	Motor_stop(MOTOR_ATM_ID);
	Delay_ms(DisplayMsgDelay-1000);	
	
	return ATM_STATUS_ERROR_OK;
}


uint8_t checkIfPAN_ExistsInServer(void)
{
	uint8_t u8_loopCounter = 1;
	for(u8_loopCounter = 1; u8_loopCounter <= CustomerMaxNumber; u8_loopCounter++)
	{
		/* get user data from eeprom */
		getUserDataFromEeprom(u8_loopCounter);
		/* check if PAN correct */
		if(stringCmp(gau8_PAN, gau8_PAN_CardECU) == TRUE)
		{
			return TRUE;
		}
	}
	return FALSE;
}

uint8_t compareUserAmountWithBalance(void)
{
	/* separate balance to integer and decimal then covert it to int */
	separateInteger(gau8_Balance, gau8_BalanceIntegerPart, 4);
	stringToInteger(gau8_BalanceIntegerPart, &gu32_userBalanceAmount_IntValue);
	
	separateDecimal(gau8_Balance, gau8_BalanceDecimalPart, 6, MaxAmountSize);
	stringToInteger(gau8_BalanceDecimalPart, &gu32_userBalanceAmount_DecValue);
	
	/* compare */
	if(gu32_userInputAmount_IntValue > gu32_userBalanceAmount_IntValue)
	{
		return FALSE;
	}
	else if(gu32_userInputAmount_IntValue == gu32_userBalanceAmount_IntValue)
	{
		if(gu32_userInputAmount_DecValue > gu32_userBalanceAmount_DecValue)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return TRUE;
	}
	return TRUE;
}


enuAtm_Status_t getUserDataFromEeprom(uint8_t u8_userId)
{
	/* get PAN from eeprom */
	Eeprom_24_readPacket((FirstCustomerPANAddress+((u8_userId-1)*CustomerAddressDataOffset)),
	gau8_PAN, PAN_size);
	/* get balance from eeprom */
	Eeprom_24_readPacket((FirstCustomerBalanceAdress+((u8_userId-1)*CustomerAddressDataOffset)),
	gau8_Balance, Balance_size);
	
	return ATM_STATUS_ERROR_OK;
}

uint8_t compareUserAmountWithMaxAmount(void)
{
	/* separate integer part and covert it to int */
	separateInteger(gau8_Amount_AtmUser, gau8_userAmountIntegerPart, 4);
	stringToInteger(gau8_userAmountIntegerPart, &gu32_userInputAmount_IntValue);
	/* seperate deimcal part and covert it to int */
	separateDecimal(gau8_Amount_AtmUser, gau8_userAmountDecimalPart, 6, MaxAmountSize);
	stringToInteger(gau8_userAmountDecimalPart, &gu32_userInputAmount_DecValue);
	/* separate max amount to integer and decimal then covert it to int */
	separateInteger(gau8_maxAmount, gau8_maxBalanceIntegerPart, 4);
	stringToInteger(gau8_maxBalanceIntegerPart, &gu32_MaxAmount_IntValue);
	
	separateDecimal(gau8_maxAmount, gau8_maxBalanceDecimalPart, 6, MaxAmountSize);
	stringToInteger(gau8_maxBalanceDecimalPart, &gu32_MaxAmount_DecValue);
	
	/* compare */
	if(gu32_userInputAmount_IntValue > gu32_MaxAmount_IntValue)
	{
		return FALSE;
	}
	else if(gu32_userInputAmount_IntValue == gu32_MaxAmount_IntValue)
	{
		if(gu32_userInputAmount_DecValue > gu32_MaxAmount_DecValue)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return TRUE;		
	}
	return TRUE;
}




enuAtm_Status_t getUserAmount_Keypad(void)
{
	uint8_t u8_loopCounter = Initial_Value;
	for(u8_loopCounter = Initial_Value; u8_loopCounter < MaxAmountSize; u8_loopCounter++)
	{
		while(TRUE)
		{
			KeypadScan(&gu8_pressedKey);
			if(gu8_pressedKey != NO_KEY_PRESSED)
			{
				if(gu8_pressedKey == '-' && u8_loopCounter > 0)
				{
					Lcd_cursorPosition(2,u8_loopCounter);
					Lcd_sendCharacter(' ');
					Lcd_cursorPosition(2,u8_loopCounter);
					u8_loopCounter-=2;
					break;
				}
				else if(gu8_pressedKey == '=')
				{
					gau8_Amount_AtmUser[u8_loopCounter] = END_OF_STRING;
					return ATM_STATUS_ERROR_OK;
				}
				else if(gu8_pressedKey != '-')
				{
					Lcd_sendCharacter(gu8_pressedKey);
					gau8_Amount_AtmUser[u8_loopCounter] = gu8_pressedKey;
					break;
				}
				else
				{
					u8_loopCounter--;
				}

			}
		}

	}
	return ATM_STATUS_ERROR_OK;
}

enuAtm_Status_t getUserPIN_Keypad(void)
{
	uint8_t u8_loopCounter = Initial_Value;
	for(u8_loopCounter = Initial_Value; u8_loopCounter < PIN_size; u8_loopCounter++)
	{
		while(TRUE)
		{
     		KeypadScan(&gu8_pressedKey);
     		if(gu8_pressedKey != NO_KEY_PRESSED)
     		{
			 	if(gu8_pressedKey == '-' && u8_loopCounter > 0)
			 	{
			     	Lcd_cursorPosition(2,u8_loopCounter);
			     	Lcd_sendCharacter(' ');
					Lcd_cursorPosition(2,u8_loopCounter);
			     	u8_loopCounter-=2;
					 break;
			 	}
			 	else if(gu8_pressedKey == '=')
			 	{
			     	gau8_PIN_AtmUser[u8_loopCounter] = END_OF_STRING;
			     	return ATM_STATUS_ERROR_OK;
			 	}
			 	else if(gu8_pressedKey != '-')
			 	{
			     	Lcd_sendCharacter('*');
			     	gau8_PIN_AtmUser[u8_loopCounter] = gu8_pressedKey;
					break;
			 	}
				else
				{
					u8_loopCounter--;
				}

     		}			
		}

	}
	return ATM_STATUS_ERROR_OK;
}


enuAtm_Status_t getUserInputKeypad(void)
{
	while(TRUE)
	{
     	KeypadScan(&gu8_pressedKey);
     	if(gu8_pressedKey != NO_KEY_PRESSED)
     	{
	     	if(gu8_pressedKey == '1')
	     	{
				enuUserMode = USER_INSERT_CARD;
				return ATM_STATUS_ERROR_OK;
				
	     	}
	     	else if(gu8_pressedKey == '2')
	     	{
				enuUserMode = USER_GET_TEMP;
				return ATM_STATUS_ERROR_OK;				 
	     	}
	     	else
	     	{
		     	Uart_syncTransmit_string("\rInavlid entry, please select a valid choice\r");
		     	enuUserMode = USER_INVALID_CHOICE;			 
	     	}
     	}		
	}
	
}







enuAtm_Status_t Lcd_userModeMainMenu(void)
{
	Lcd_sendCommand(CLEAR);
	Lcd_cursorPosition(1,1);
	Lcd_sendString("1-Insert Card");
	Lcd_cursorPosition(2,1);
	Lcd_sendString("2-Display Temp");
	
	return ATM_STATUS_ERROR_OK;
}






enuAtm_Status_t getBalance(void)
{
	while(TRUE)
	{
		Uart_syncTransmit_string("\rPlease enter the Balance of the new user (ex:5000.00): ");
		
		uint8_t u8_loopCounter = Initial_Value;
		
		for(u8_loopCounter = Initial_Value; u8_loopCounter < Balance_size; u8_loopCounter++)
		{
			Uart_syncReceive_oneFrame(&gau8_Balance[u8_loopCounter]);


			if(gau8_Balance[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
			{
				Uart_syncTransmit_oneFrame(gau8_Balance[u8_loopCounter]);
				u8_loopCounter-=2;
			}
			else if(gau8_Balance[u8_loopCounter] == NEW_LINE)
			{
				Uart_syncTransmit_oneFrame(gau8_Balance[u8_loopCounter]);
				
				gau8_Balance[u8_loopCounter] = END_OF_STRING;
				
				return ATM_STATUS_ERROR_OK;

			}
			else if(gau8_Balance[u8_loopCounter] != BACK_SPACE)
			{
				Uart_syncTransmit_oneFrame(gau8_Balance[u8_loopCounter]);
			}
			else
			{
				u8_loopCounter--;
			}
		}
	}
	return ATM_STATUS_ERROR_OK;
}



enuAtm_Status_t getPAN(void)
{
	while(TRUE)
	{
		Uart_syncTransmit_string("\rPlease enter the 9 number PAN of the new user: ");
		
		uint8_t u8_loopCounter = Initial_Value;
		
		for(u8_loopCounter = Initial_Value; u8_loopCounter < PAN_size; u8_loopCounter++)
		{
			Uart_syncReceive_oneFrame(&gau8_PAN[u8_loopCounter]);


			if(gau8_PAN[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
			{
				Uart_syncTransmit_oneFrame(gau8_PAN[u8_loopCounter]);
				u8_loopCounter-=2;
			}
			else if(gau8_PAN[u8_loopCounter] == NEW_LINE)
			{
				Uart_syncTransmit_oneFrame(gau8_PAN[u8_loopCounter]);
				
				gau8_PAN[u8_loopCounter] = END_OF_STRING;
				
				return ATM_STATUS_ERROR_OK;

			}
			else if(gau8_PAN[u8_loopCounter] != BACK_SPACE)
			{
				Uart_syncTransmit_oneFrame(gau8_PAN[u8_loopCounter]);
			}
			else
			{
				u8_loopCounter--;
			}
		}
	}
	return ATM_STATUS_ERROR_OK;
}






enuAtm_Status_t getMaxAmount(void)
{
	while(TRUE)
	{
		Uart_syncTransmit_string("\rPlease enter the maximum amount (ex:5000.00): ");
		
		uint8_t u8_loopCounter = Initial_Value;
		
		for(u8_loopCounter = Initial_Value; u8_loopCounter < MaxAmountSize; u8_loopCounter++)
		{
			Uart_syncReceive_oneFrame(&gau8_maxAmount[u8_loopCounter]);


			if(gau8_maxAmount[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
			{
				Uart_syncTransmit_oneFrame(gau8_maxAmount[u8_loopCounter]);
				u8_loopCounter-=2;
			}
			else if(gau8_maxAmount[u8_loopCounter] == NEW_LINE)
			{
				Uart_syncTransmit_oneFrame(gau8_maxAmount[u8_loopCounter]);
				
				gau8_maxAmount[u8_loopCounter] = END_OF_STRING;
				
				return ATM_STATUS_ERROR_OK;

			}
			else if(gau8_maxAmount[u8_loopCounter] != BACK_SPACE)
			{
				Uart_syncTransmit_oneFrame(gau8_maxAmount[u8_loopCounter]);
			}
			else
			{
				u8_loopCounter--;
			}
		}
	}
	return ATM_STATUS_ERROR_OK;
}



enuAtm_Status_t getAdminChoice(void)
{
	
	while(TRUE)
	{
		Uart_syncTransmit_string("\rPlease select an option:\r1-Customer Data\r2-Maximum Amount\r3-EXIT\r\r");
		
		uint8_t u8_loopCounter = Initial_Value;
		
		for(u8_loopCounter = Initial_Value; u8_loopCounter < adminChoice_size; u8_loopCounter++)
		{
			Uart_syncReceive_oneFrame(&gau8_adminChoice[u8_loopCounter]);
			
			
			if(gau8_adminChoice[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
			{
				Uart_syncTransmit_oneFrame(gau8_adminChoice[u8_loopCounter]);
				u8_loopCounter-=2;
			}
			else if(gau8_adminChoice[u8_loopCounter] == NEW_LINE)
			{
				Uart_syncTransmit_oneFrame(gau8_adminChoice[u8_loopCounter]);
				gau8_adminChoice[u8_loopCounter] = END_OF_STRING;
				if(stringCmp(gau8_adminChoice, "1") == TRUE)
				{
					gu8_adminCurrentChoice = CustomerDataChoice;
					return ATM_STATUS_ERROR_OK;
				}
				else if(stringCmp(gau8_adminChoice, "2") == TRUE)
				{
					gu8_adminCurrentChoice = MaxAmountChoice;
					return ATM_STATUS_ERROR_OK;
				}
				else if(stringCmp(gau8_adminChoice, "3") == TRUE)
				{
					gu8_adminCurrentChoice = EXIT;
					return ATM_STATUS_ERROR_OK;
				}
				else
				{
					Uart_syncTransmit_string("Please enter a correct choice.\r\r");
					u8_loopCounter = adminChoice_size;
				}
			}
			else if(gau8_adminChoice[u8_loopCounter] != BACK_SPACE)
			{
				Uart_syncTransmit_oneFrame(gau8_adminChoice[u8_loopCounter]);
			}
			else
			{
				u8_loopCounter--;
			}
		}
	}
	return ATM_STATUS_ERROR_OK;
}



enuAtm_Status_t getPasscode(void)
{
	
	while(TRUE)
	{
		Uart_syncTransmit_string("Please enter the pass code: ");
		uint8_t u8_loopCounter = Initial_Value;
		for(u8_loopCounter = Initial_Value; u8_loopCounter < AdminPasscode_size; u8_loopCounter++)
		{
			Uart_syncReceive_oneFrame(&gau8_passCode[u8_loopCounter]);
			
			if(gau8_passCode[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
			{
				Uart_syncTransmit_oneFrame(gau8_passCode[u8_loopCounter]);
				u8_loopCounter-=2;
			}
			else if(gau8_passCode[u8_loopCounter] == NEW_LINE)
			{
				Uart_syncTransmit_oneFrame(NEW_LINE);
				gau8_passCode[u8_loopCounter] = END_OF_STRING;
				if(stringCmp(gau8_passCode, AdminPasscode) == TRUE)
				{
					Uart_syncTransmit_string("\rYou successfully logged into ADMIN mode\r");
					enuPassCodeStatus = PASS_CODE_VALID;
					return ATM_STATUS_ERROR_OK;
				}
				else if(stringCmp(gau8_passCode, "USER") == TRUE)
				{
					enuAtmMode = ATM_USER_MODE;
					return ATM_STATUS_ERROR_OK;
				}
				else
				{
					Uart_syncTransmit_string("Pass code incorrect\r");
					enuPassCodeStatus = PASS_CODE_INVALID;
					u8_loopCounter = AdminPasscode_size;
				}
			}
			else if(gau8_passCode[u8_loopCounter] != BACK_SPACE)
			{
				Uart_syncTransmit_oneFrame('*');
			}
			else
			{
				u8_loopCounter--;
			}
			
		}
	}
	return ATM_STATUS_ERROR_NOK;
}



enuAtm_Status_t getMode(void)
{
	while(TRUE)
	{
		Uart_syncTransmit_string("Please type the desired mode:\r1-USER\r2-ADMIN\r\r");
		
		uint8_t u8_loopCounter = Initial_Value;
		
		for(u8_loopCounter = Initial_Value; u8_loopCounter < atmMode_size; u8_loopCounter++)
		{
			Uart_syncReceive_oneFrame(&gau8_atmMode[u8_loopCounter]);


			if(gau8_atmMode[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
			{
				Uart_syncTransmit_oneFrame(gau8_atmMode[u8_loopCounter]);
				u8_loopCounter-=2;
			}
			else if(gau8_atmMode[u8_loopCounter] == NEW_LINE)
			{
				Uart_syncTransmit_oneFrame(gau8_atmMode[u8_loopCounter]);
				gau8_atmMode[u8_loopCounter] = END_OF_STRING;
				if(stringCmp(gau8_atmMode, "ADMIN") == TRUE)
				{
					enuAtmMode = ATM_PROGRAMMING_MODE;

					return ATM_STATUS_ERROR_OK;
				}
				else if(stringCmp(gau8_atmMode, "USER") == TRUE)
				{
					enuAtmMode = ATM_USER_MODE;
					return ATM_STATUS_ERROR_OK;
				}
				else
				{
					Uart_syncTransmit_string("Please enter a correct choice.\r\r");
					u8_loopCounter = atmMode_size;
				}
			}
			else if(gau8_atmMode[u8_loopCounter] != BACK_SPACE)
			{
				Uart_syncTransmit_oneFrame(gau8_atmMode[u8_loopCounter]);
			}
			else
			{
				u8_loopCounter--;
			}
		}
	}
	return ATM_STATUS_ERROR_OK;
}


enuAtm_Status_t getMode_userModeVersion(void)
{
	while(TRUE)
	{
		
		Uart_syncTransmit_string("\rYou can go to admin mode by typing ADMIN\rOr press 'C' to continue with your process\r\r");
		
		uint8_t u8_loopCounter = Initial_Value;
		
		for(u8_loopCounter = Initial_Value; u8_loopCounter < atmMode_size; u8_loopCounter++)
		{
			Uart_syncReceive_oneFrame(&gau8_atmMode[u8_loopCounter]);


			if(gau8_atmMode[u8_loopCounter] == BACK_SPACE && u8_loopCounter > 0)
			{
				Uart_syncTransmit_oneFrame(gau8_atmMode[u8_loopCounter]);
				u8_loopCounter-=2;
			}
			else if(gau8_atmMode[u8_loopCounter] == NEW_LINE)
			{
				Uart_syncTransmit_oneFrame(gau8_atmMode[u8_loopCounter]);
				gau8_atmMode[u8_loopCounter] = END_OF_STRING;
				if(stringCmp(gau8_atmMode, "ADMIN") == TRUE)
				{
					enuAtmMode = ATM_PROGRAMMING_MODE;

					return ATM_STATUS_ERROR_OK;
				}
				else if(stringCmp(gau8_atmMode, "USER") == TRUE)
				{
					Uart_syncTransmit_string("You are already in USER mode\r\r");
					u8_loopCounter = atmMode_size;
				}
				else if(stringCmp(gau8_atmMode, "C") == TRUE || stringCmp(gau8_atmMode, "c") == TRUE)
				{
					Uart_syncTransmit_string("\rWaiting for your choice on LCD\r");
					return ATM_STATUS_ERROR_OK;
				}				
				else
				{
					Uart_syncTransmit_string("Please enter a correct choice.\r\r");
					u8_loopCounter = atmMode_size;
				}
			}
			else if(gau8_atmMode[u8_loopCounter] != BACK_SPACE)
			{
				Uart_syncTransmit_oneFrame(gau8_atmMode[u8_loopCounter]);
			}
			else
			{
				u8_loopCounter--;
			}
		}
	}
	return ATM_STATUS_ERROR_OK;
}






/* function to be called from external interrupt 0 ISR */
void FunctionWhenCardInsertedPressed(void)
{
	/* check if the ATM in the correct state to request data from CARD */
	if(gu8_CustomerDataFlag == CustomerDataAvailable && enuAtmMode != ATM_IDLE_MODE)
	{
		/* signal card ECU to start sending data and receive it in spi slave mode */
		Dio_writePin(CardRequestSignal_Pin, STD_LOW);
		Dio_writePin(CardRequestSignal_Pin, STD_HIGH);
		/* receive data */
		Spi_SlaveReceiveArray(gau8_PAN_CardECU, PAN_size);
		Spi_SlaveReceiveArray(gau8_PIN_CardECU, PIN_size);
		
		/* indicate that card button was pressed */
		gu8_insertButtonPressedFlag = InsertCardButtonPresssed;
	}
	else
	{
		Uart_syncTransmit_string("No customer data available yet on our server or\ryou are not in USER mode\r\r");
	}

}