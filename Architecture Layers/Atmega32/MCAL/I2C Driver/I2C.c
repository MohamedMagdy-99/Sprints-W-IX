/*****************************************************************************
* Module: I2C Module
* File Name: I2C.c
* Description: Source file for I2C Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "I2C.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuI2C_Status_t	    I2C_Status = I2C_STATUS_ERROR_OK;
enuI2C_initStatus_t I2C_Init = I2C_NOT_INITIALIZED;

uint8_t gu8_SlaveListenStatus= Initial_Value;
uint8_t gu8_SlaveWriteStatus= Initial_Value;
uint8_t gu8_SlaveReadStatus= Initial_Value;


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: initialize i2c module according to the cfg file
******************************************************************************************/
enuI2C_Status_t I2C_init(void)
{
	if(I2C_Init == I2C_INITIALIZED) return I2C_STATUS_ERROR_NOK;
	
	I2C_Init = I2C_INITIALIZED;
	
	/*******************************************************************/
	switch(strI2C_Config.u8_selectMaster_or_Slave)
	{
		case(MASTER_I2C):
		{
			switch(strI2C_Config.u8_prescaler)
			{
				case(PRESCALER_1):
				{
					CLEAR_BIT(TWSR_R, TWPS0_B);
					CLEAR_BIT(TWSR_R, TWPS1_B);					
					break;
				}
				case(PRESCALER_4):
				{
					SET_BIT(TWSR_R, TWPS0_B);
					CLEAR_BIT(TWSR_R, TWPS1_B);					
					break;
				}
				case(PRESCALER_16):
				{
					CLEAR_BIT(TWSR_R, TWPS0_B);
					SET_BIT(TWSR_R, TWPS1_B);					
					break;
				}
				case(PRESCALER_64):
				{
					SET_BIT(TWSR_R, TWPS0_B);
					SET_BIT(TWSR_R, TWPS1_B);					
					break;
				}												
			}
			/* set bit rate value */
			TWBR_R = I2C_TWBR_VALUE(); 						
			break;
		}
		case(SLAVE_I2C):
		{
			TWAR_R |= (SLAVE_ADDRESS<<1);
			TWCR_R = (1<<TWEA_B) | (1<<TWINT_B) | (1<<TWEN_B);	
			break;
		}
		default: return I2C_STATUS_ERROR_NOK;
	}
	return I2C_STATUS_ERROR_OK;
}


/*****************************************************************************************
* Parameters (in): address of slave
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c sends a start condition to a specific slave address 
******************************************************************************************/
enuI2C_Status_t I2C_Start(uint8_t address)  
{

	TWCR_R = (1<<TWSTA_B) | (1<<TWINT_B) | (1<<TWEN_B);
		
	/* Wait until TWI finish its current job */
	while(BIT_IS_CLEAR(TWCR_R, TWINT_B));
	I2C_MasterWrite(address);	
	
	return I2C_STATUS_ERROR_OK;	
	
}

/*****************************************************************************************
* Parameters (in): address of slave
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c sends a start condition to a specific slave address
******************************************************************************************/
enuI2C_Status_t I2C_StartWait(uint8_t address)
{
	while(1)
	{
		TWCR_R = (1<<TWSTA_B) | (1<<TWINT_B) | (1<<TWEN_B);
		
		/* Wait until TWI finish its current job */
		while(BIT_IS_CLEAR(TWCR_R, TWINT_B));
		I2C_MasterWrite(address);
		if((TWSR_R & 0xF8) == Address_W_Sent_AckReceived) break;
	}

	
	return I2C_STATUS_ERROR_OK;
	
}


/*****************************************************************************************
* Parameters (in): data
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c sends data to the bus
******************************************************************************************/
enuI2C_Status_t I2C_MasterWrite(uint8_t data)	
{
	/* Copy data in TWI data register */
	TWDR_R = data;
	
	TWCR_R = (1<<TWINT_B) | (1<<TWEN_B);
	/* Wait until TWI finish its current job */
	while(BIT_IS_CLEAR(TWCR_R, TWINT_B));

	return I2C_STATUS_ERROR_OK;	
}

/*****************************************************************************************
* Parameters (in): none
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c sends a stop condition to bus
******************************************************************************************/
enuI2C_Status_t I2C_Stop(void)			
{

	TWCR_R = (1<<TWSTO_B) | (1<<TWINT_B) | (1<<TWEN_B);
		
	/* Wait until TWI finish its current job */
	BIT_IS_SET(TWCR_R, TWSTO_B);

	return I2C_STATUS_ERROR_OK;
}


/*****************************************************************************************
* Parameters (in): pointer to data
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c 1 byte from bus and send Ack
******************************************************************************************/
enuI2C_Status_t I2C_MasterRead_Ack(uint8_t* RxData)		
{
	
	TWCR_R = (1<<TWEA_B) | (1<<TWINT_B) | (1<<TWEN_B);	
	/* Wait until TWI finish its current job */
	while(BIT_IS_CLEAR(TWCR_R, TWINT_B));
	/* Return received data */
	*RxData = TWDR_R;
	return I2C_STATUS_ERROR_OK;			
}

/*****************************************************************************************
* Parameters (in): pointer to data
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c 1 byte from bus and send nack
******************************************************************************************/
enuI2C_Status_t I2C_MasterRead_Nack(uint8_t* RxData)		
{
	TWCR_R = (1<<TWINT_B) | (1<<TWEN_B);	
	/* Wait until TWI finish its current job */
	while(BIT_IS_CLEAR(TWCR_R, TWINT_B));
	/* Return received data */
	*RxData = TWDR_R;
	return I2C_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): none
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c sends a repeated start condition to bus
******************************************************************************************/
enuI2C_Status_t I2C_RepeatedStart(uint8_t address)
{

	I2C_Start(address);

	return I2C_STATUS_ERROR_OK;
	
}
/******************************************************************************/
/******************************************************************************/
/*****************************************************************************************
* Parameters (in): none
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c slave waits to be called
******************************************************************************************/
enuI2C_Status_t I2C_SlaveListen(void)
{
	gu8_SlaveListenStatus= Initial_Value;
	while(1)
	{
		uint8_t u8_status = Initial_Value;			

		//PORTA_REG = 0xFF;
		/* Wait until TWI finish its current job */
		while(BIT_IS_CLEAR(TWCR_R, TWINT_B));
		//PORTA_REG = 0x55;
		u8_status=TWSR_R & 0xF8;		/* Read TWI status register */
			
        switch(u8_status)
		{
			case(OwnAddressReceived_W_AckSent):
			{
				gu8_SlaveListenStatus = SlaveRead;
				return I2C_STATUS_ERROR_OK;
				break;
			}
			case(MasterLostArbitration_OwnAddressReceived_W_AckSent):
			{
				gu8_SlaveListenStatus = SlaveRead;
				return I2C_STATUS_ERROR_OK;				
				break;
			}
			case(GeranlCallAddressReceived_AckSent):
			{
				gu8_SlaveListenStatus = SlaveRead;
				return I2C_STATUS_ERROR_OK;				
				break;
			}
			case(MasterLostArbitration_GeranlCallAddressReceived_AckSent):
			{
				gu8_SlaveListenStatus = SlaveRead;
				return I2C_STATUS_ERROR_OK;				
				break;
			}
			case(OwnAddressReceived_R_AckSent):
			{
				gu8_SlaveListenStatus = SlaveWrite;
				return I2C_STATUS_ERROR_OK;				
				break;
			}
			case(MasterLostArbitration_OwnAddressReceived_R_AckSent):
			{
				gu8_SlaveListenStatus = SlaveWrite;
				return I2C_STATUS_ERROR_OK;				
				break;
			}
			default:
			{
				
				break;
			}
				 															
		}
	
	}
	return I2C_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): data
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c slave sends data to bus
******************************************************************************************/
enuI2C_Status_t I2C_SlaveWrite(uint8_t data)
{
	uint8_t u8_status = Initial_Value;			
	gu8_SlaveWriteStatus = Initial_Value;
	TWDR_R = data;

	TWCR_R = (1<<TWEA_B) | (1<<TWINT_B) | (1<<TWEN_B);
	
	/* Wait until TWI finish its current job */
	while(BIT_IS_CLEAR(TWCR_R, TWINT_B));
	
	u8_status=TWSR_R & 0xF8;		/* Read TWI status register */	
	
	if(u8_status == DataByteSent_AckReceived)
	{
		gu8_SlaveWriteStatus = DataByteSent_AckReceived;
		return I2C_STATUS_ERROR_OK;
	}
	else
	{
		gu8_SlaveWriteStatus = Initial_Value;
		SET_BIT(TWCR_R, TWINT_B);
		return I2C_STATUS_ERROR_OK;
	}
	return I2C_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): data
* Parameters (out): Error Status
* Return value: enuUart_Status_t
* Description: i2c slave reads data from bus
******************************************************************************************/
enuI2C_Status_t I2C_SlaveRead(uint8_t* RxData)
{
	uint8_t u8_status = Initial_Value;
	gu8_SlaveReadStatus = Initial_Value;

	TWCR_R = (1<<TWEA_B) | (1<<TWINT_B) | (1<<TWEN_B);
	
	/* Wait until TWI finish its current job */
	while(BIT_IS_CLEAR(TWCR_R, TWINT_B));
	
	u8_status=TWSR_R & 0xF8;		/* Read TWI status register */
	
	if(u8_status == Stop_RepeatedStart_Recevied_InSlaveMode)
	{
		gu8_SlaveReadStatus = Stop_RepeatedStart_Recevied_InSlaveMode;
        SET_BIT(TWCR_R, TWINT_B);		
		return I2C_STATUS_ERROR_OK;
	}
	else
	{
		gu8_SlaveReadStatus = Initial_Value;
		*RxData = TWDR_R;
		return I2C_STATUS_ERROR_OK;
	}
	return I2C_STATUS_ERROR_OK;	
}

