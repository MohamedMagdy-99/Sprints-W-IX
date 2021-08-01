/*****************************************************************************
* Module: EEPROM_24 Module
* File Name: EEPROM_24.c
* Description: Source file for EEPROM_24 Module
* Author: Mohamed Magdy
* Date: 22-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "EEPROM_24.h"

/*- BLOBAL STATIC VARIABLES
-------------------------------*/

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuEeprom_24_Status_t	    EEPROM_Status = EEPROM_STATUS_ERROR_OK;


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
#if MODEL == AT24C256B
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: initialize Eeprom_24 module according to the cfg file
******************************************************************************************/
enuEeprom_24_Status_t Eeprom_24_init(void)
{
	I2C_init();
	return EEPROM_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): location and data to be put into
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: eeprom writes a byte to specific location
******************************************************************************************/
enuEeprom_24_Status_t  Eeprom_24_writeByte(uint16_t u16_location, uint8_t u8_data)
{
	I2C_StartWait(SLAVE_ADDRESS_EEPROM);
	
	I2C_MasterWrite((uint8_t)(u16_location<<8));
	I2C_MasterWrite((uint8_t)u16_location);
	
	I2C_MasterWrite(u8_data);
	I2C_Stop();
	
	return EEPROM_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): location and data to read from
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: eeprom reads a byte from specific location
******************************************************************************************/
enuEeprom_24_Status_t  Eeprom_24_readByte(uint16_t u16_location, uint8_t* pu8_data)
{
	I2C_StartWait(SLAVE_ADDRESS_EEPROM);
	I2C_MasterWrite((uint8_t)(u16_location<<8));
	I2C_MasterWrite((uint8_t)u16_location);
	
	I2C_RepeatedStart(SLAVE_ADDRESS_EEPROM | 1);
	
	I2C_MasterRead_Nack(pu8_data);
	
	I2C_Stop();	
	
	return EEPROM_STATUS_ERROR_OK;
	
}


/*****************************************************************************************
* Parameters (in): location and array of data to be written 
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: eeprom writes a stream of bytes to specific location
******************************************************************************************/
enuEeprom_24_Status_t  Eeprom_24_writePacket(uint16_t u16_location, uint8_t *pu8_data, uint16_t u16_dataLen)
{
	uint16_t u16_loopCounter = Initial_Value;
	
	I2C_StartWait(SLAVE_ADDRESS_EEPROM);
	I2C_MasterWrite((uint8_t)(u16_location<<8));
	I2C_MasterWrite((uint8_t)u16_location);
	
	for(u16_loopCounter = Initial_Value; u16_loopCounter < u16_dataLen; u16_loopCounter++)
	{
		I2C_MasterWrite(pu8_data[u16_loopCounter]);
	}
	
	
	I2C_Stop();	
	
	return EEPROM_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): location and array of data to be read
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: eeprom reads a stream of bytes from specific location
******************************************************************************************/
enuEeprom_24_Status_t  Eeprom_24_readPacket(uint16_t u16_location, uint8_t *pu8_data, uint16_t u16_dataLen)
{
	uint16_t u16_loopCounter = Initial_Value;
	
	I2C_StartWait(SLAVE_ADDRESS_EEPROM);
	I2C_MasterWrite((uint8_t)(u16_location<<8));
	I2C_MasterWrite((uint8_t)u16_location);
	
	I2C_RepeatedStart(SLAVE_ADDRESS_EEPROM | 1);
	
	for(u16_loopCounter = Initial_Value; u16_loopCounter < u16_dataLen; u16_loopCounter++)
	{
		if(u16_loopCounter == u16_dataLen-1) 
		{
			I2C_MasterRead_Nack(&pu8_data[u16_loopCounter]);
			break;
		}
		
		I2C_MasterRead_Ack(&pu8_data[u16_loopCounter]);
	}
	
	I2C_Stop();	
	
	return EEPROM_STATUS_ERROR_OK;
}


/*- Write Page to specific location in the Memory -*/
//enuEeprom_24_Status_t  Eeprom_24_writePage(uint8_t u8_page, uint8_t *pu8_data)


/*- Read Page from specific location in the Memory -*/
//enuEeprom_24_Status_t  Eeprom_24_readPage(uint8_t u8_page, uint8_t *pu8_data);

#elif MODEL == AT24C16B
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: initialize Eeprom_24 module according to the cfg file
******************************************************************************************/
enuEeprom_24_Status_t Eeprom_24_init(void)
{
	I2C_init();
	return EEPROM_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): location and data to be put into
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: eeprom writes a byte to specific location
******************************************************************************************/
enuEeprom_24_Status_t  Eeprom_24_writeByte(uint16_t u16_location, uint8_t u8_data)
{
	I2C_StartWait((uint8_t)((SLAVE_ADDRESS_EEPROM<<4) | ((u16_location>>7) & 0x0E)));
	
	I2C_MasterWrite((uint8_t)u16_location);
	
	I2C_MasterWrite(u8_data);
	
	I2C_Stop();
	
	return EEPROM_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): location and data to read from
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: eeprom reads a byte from specific location
******************************************************************************************/
enuEeprom_24_Status_t  Eeprom_24_readByte(uint16_t u16_location, uint8_t* pu8_data)
{
	I2C_StartWait((uint8_t)((SLAVE_ADDRESS_EEPROM<<4) | ((u16_location>>7) & 0x0E)));
	I2C_MasterWrite((uint8_t)u16_location);
	
	I2C_RepeatedStart((uint8_t)(((SLAVE_ADDRESS_EEPROM<<4) | ((u16_location>>7) & 0x0E)) | 0x01));
	
	I2C_MasterRead_Nack(pu8_data);
	
	I2C_Stop();	
	
	return EEPROM_STATUS_ERROR_OK;
	
}


/*****************************************************************************************
* Parameters (in): location and array of data to be written 
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: eeprom writes a stream of bytes to specific location
******************************************************************************************/
enuEeprom_24_Status_t  Eeprom_24_writePacket(uint16_t u16_location, uint8_t *pu8_data, uint16_t u16_dataLen)
{
	uint16_t u16_loopCounter = Initial_Value;
	
	I2C_StartWait((uint8_t)((SLAVE_ADDRESS_EEPROM<<4) | ((u16_location>>7) & 0x0E)));
	
	I2C_MasterWrite((uint8_t)u16_location);
	
	for(u16_loopCounter = Initial_Value; u16_loopCounter < u16_dataLen; u16_loopCounter++)
	{
		I2C_MasterWrite(pu8_data[u16_loopCounter]);
	}
	
	
	I2C_Stop();	
	
	return EEPROM_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): location and array of data to be read
* Parameters (out): Error Status
* Return value: enuEeprom_24_Status_t
* Description: eeprom reads a stream of bytes from specific location
******************************************************************************************/
enuEeprom_24_Status_t  Eeprom_24_readPacket(uint16_t u16_location, uint8_t *pu8_data, uint16_t u16_dataLen)
{
	uint16_t u16_loopCounter = Initial_Value;
	
	I2C_StartWait((uint8_t)((SLAVE_ADDRESS_EEPROM<<4) | ((u16_location>>7) & 0x0E)));
	I2C_MasterWrite((uint8_t)u16_location);
	
	I2C_RepeatedStart((uint8_t)(((SLAVE_ADDRESS_EEPROM<<4) | ((u16_location>>7) & 0x0E)) | 0x01));
	
	for(u16_loopCounter = Initial_Value; u16_loopCounter < u16_dataLen; u16_loopCounter++)
	{
		if(u16_loopCounter == u16_dataLen-1) 
		{
			I2C_MasterRead_Nack(&pu8_data[u16_loopCounter]);
			break;
		}
		
		I2C_MasterRead_Ack(&pu8_data[u16_loopCounter]);
	}
	
	I2C_Stop();	
	
	return EEPROM_STATUS_ERROR_OK;
}

#endif