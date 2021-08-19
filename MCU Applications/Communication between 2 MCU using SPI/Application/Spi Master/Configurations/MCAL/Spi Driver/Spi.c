/*****************************************************************************
* Module: Spi Module
* File Name: Spi.c
* Description: Source file for SPI Module
* Author: Mohamed Magdy
* Date: 20-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Spi.h"
/*- BLOBAL STATIC VARIABLES
-------------------------------*/

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuSPi_Status_t Spi_Status = SPI_STATUS_ERROR_OK;
enuSpi_initStatus_t Spi_Init = SPI_NOT_INITIALIZED;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuSpi_Status_t
* Description: initialize Spi module according to the cfg file
******************************************************************************************/
enuSPi_Status_t Spi_init(void)
{
	if(Spi_Init == SPI_INITIALIZED) return SPI_STATUS_ERROR_NOK;
	
	Spi_Init = SPI_INITIALIZED;
	
	Dio_init();
	/*******************************************************************/	
	switch(strSpi_Config.u8_selectMaster_or_Slave)
	{
		case(MASTER):
		{
			SET_BIT(SPCR_R, MSTR_B);
			break;
		}
		case(SLAVE):
		{
			CLEAR_BIT(SPCR_R, MSTR_B);
			break;
		}
		default: return SPI_STATUS_ERROR_NOK;
	}	
	switch(strSpi_Config.u8_clockPhase)
	{
		case(SAMPLE_LEADING):
		{
			CLEAR_BIT(SPCR_R, CPHA_B);
			break;
		}
		case(SAMPLE_FALLING):
		{
			SET_BIT(SPCR_R, CPHA_B);
			break;
		}
		default: return SPI_STATUS_ERROR_NOK;
	}
	switch(strSpi_Config.u8_clockPolarity)
	{
		case(SCK_HIGH_IDLE):
		{
			SET_BIT(SPCR_R, CPOL_B);
			break;
		}
		case(SCK_LOW_IDLE):
		{
			CLEAR_BIT(SPCR_R, CPOL_B);
			break;
		}
		default: return SPI_STATUS_ERROR_NOK;
	}	
	switch(strSpi_Config.u8_dataOrder)
	{
		case(MSB_FIRST):
		{
			CLEAR_BIT(SPCR_R, DORD_B);
			break;
		}
		case(LSB_FIRST):
		{
			SET_BIT(SPCR_R, DORD_B);
			break;
		}
		default: return SPI_STATUS_ERROR_NOK;
	}	
	switch(strSpi_Config.u8_clockRate)
	{
		case(DIV_4):
		{
			CLEAR_BIT(SPCR_R, SPR0_B);
			CLEAR_BIT(SPCR_R, SPR1_B);
			CLEAR_BIT(SPSR_R, SPI2X_B);
			break;
		}
		case(DIV_16):
		{
			SET_BIT(SPCR_R, SPR0_B);
			CLEAR_BIT(SPCR_R, SPR1_B);
			CLEAR_BIT(SPSR_R, SPI2X_B);			
			break;
		}
		case(DIV_64):
		{
			CLEAR_BIT(SPCR_R, SPR0_B);
			SET_BIT(SPCR_R, SPR1_B);
			CLEAR_BIT(SPSR_R, SPI2X_B);			
			break;
		}
		case(DIV_128):
		{
			SET_BIT(SPCR_R, SPR0_B);
			SET_BIT(SPCR_R, SPR1_B);
			CLEAR_BIT(SPSR_R, SPI2X_B);			
			break;
		}
		case(DIV_2):
		{
			CLEAR_BIT(SPCR_R, SPR0_B);
			CLEAR_BIT(SPCR_R, SPR1_B);
			SET_BIT(SPSR_R, SPI2X_B);			
			break;
		}
		case(DIV_8):
		{
			SET_BIT(SPCR_R, SPR0_B);
			CLEAR_BIT(SPCR_R, SPR1_B);
			SET_BIT(SPSR_R, SPI2X_B);			
			break;
		}
		case(DIV_32):
		{
			CLEAR_BIT(SPCR_R, SPR0_B);
			SET_BIT(SPCR_R, SPR1_B);
			SET_BIT(SPSR_R, SPI2X_B);
			break;
		}						
		default: return SPI_STATUS_ERROR_NOK;
	}
	
	/* enable SPI using SPIE bit */
	SET_BIT(SPCR_R, SPE_B);

	return SPI_STATUS_ERROR_OK;		
}

/*****************************************************************************************
* Parameters (in): Data to be transmitted
* Parameters (out): Error Status
* Return value: enuSpi_Status_t
* Description: spi transmits one frame through MOSI pin
******************************************************************************************/

enuSPi_Status_t Spi_TransmitChar(uint8_t u8_TxData)
{
	Dio_writePin(PORTB_PIN4_ID, STD_LOW);		 //enable slave
	
	SPDR_R = u8_TxData;							//Send input data to the Data register
	while( BIT_IS_CLEAR(SPSR_R, SPIF_B) ) ;		// While Transmission not completed wait .  (To avoid overlapping of data transmission)
	Dio_writePin(PORTB_PIN4_ID, STD_HIGH);		//disable slave
	/* clearing interrupt flag */

	return SPI_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): pointer to data which will be received
* Parameters (out): Error Status
* Return value: enuSpi_Status_t
* Description: spi receives one frame through MISO pin
******************************************************************************************/
enuSPi_Status_t Spi_ReceiveChar(uint8_t* u8_TxData)
{
	
	Dio_writePin(PORTB_PIN4_ID, STD_LOW);		 //enable slave
	SPDR_R = 0x00;                              // trigger SCK to start receive by putting dummy data 
	while( BIT_IS_CLEAR(SPSR_R, SPIF_B) ) ;       // While Transmission not completed wait until it's complete
	Dio_writePin(PORTB_PIN4_ID, STD_HIGH);		//disable slave
	 *u8_TxData =  SPDR_R;                      //Return the received data found in Data register .
	 /* clearing interrupt flag */

	return SPI_STATUS_ERROR_OK;   
}


/*****************************************************************************************
* Parameters (in): pointer array to be transmitted
* Parameters (out): Error Status
* Return value: enuSpi_Status_t
* Description: spi array through MOSI pin
******************************************************************************************/
enuSPi_Status_t Spi_Transmit_array(uint8_t* u8_TxArray, uint16_t u16_arraySize)
{
	uint8_t  u8_loopCounter = Initial_Value ;
	for (u8_loopCounter = Initial_Value; u8_loopCounter < u16_arraySize ; u8_loopCounter++)
	{
		Spi_TransmitChar(u8_TxArray[u8_loopCounter]);
	}
	return SPI_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): pointer to string to be transmitted
* Parameters (out): Error Status
* Return value: enuSpi_Status_t
* Description: spi transmits string through MOSI pin
******************************************************************************************/
enuSPi_Status_t Spi_Transmit_string(uint8_t* u8_TxString)
{
	uint8_t  u8_loopCounter = Initial_Value ;
	while(u8_TxString[u8_loopCounter] != '\0')
	{
		Spi_TransmitChar(u8_TxString[u8_loopCounter]);
		u8_loopCounter++;
	}
	return SPI_STATUS_ERROR_OK;
}