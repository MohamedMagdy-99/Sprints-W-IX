/*****************************************************************************
* Module: Dio Module
* File Name: Dio.c
* Description: Source file for DIO Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Dio.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuDio_Status_t Dio_Status = DIO_STATUS_ERROR_OK;
enuDio_initStatus_t Dio_Init = DIO_NOT_INITIALIZED;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuDio_Status_t
* Description: initialize the pins direction and initial state according to the cfg file
******************************************************************************************/
enuDio_Status_t Dio_init(void)
{
	if(Dio_Init == DIO_INITIALIZED) return DIO_STATUS_ERROR_NOK;
	
	Dio_Init = DIO_INITIALIZED;
	
	uint8_t u8_Counter = Initial_Value;

	for(u8_Counter=Initial_Value; u8_Counter<DIO_USED_PINS_NUM; u8_Counter++)
	{
		switch(strDio_pins[u8_Counter].u8_PortNum)
		{
			case(PORT_A):
			{
				if(strDio_pins[u8_Counter].u8_Direction == DIO_PIN_DIR_OUTPUT)
				{
					SET_BIT(DDRA_REG,strDio_pins[u8_Counter].u8_PinNum);
					if(strDio_pins[u8_Counter].u8_InitState == PIN_HIGH)
					{
						SET_BIT(PORTA_REG,strDio_pins[u8_Counter].u8_PinNum);
					}
					else if(strDio_pins[u8_Counter].u8_InitState == PIN_LOW)
					{
						CLEAR_BIT(PORTA_REG,strDio_pins[u8_Counter].u8_PinNum);
						
					}	
				}
				else if(strDio_pins[u8_Counter].u8_Direction == DIO_PIN_DIR_INPUT)
				{
					CLEAR_BIT(DDRA_REG,strDio_pins[u8_Counter].u8_PinNum);
					if(strDio_pins[u8_Counter].u8_InitState == PIN_PUR)
					{
						SET_BIT(PORTA_REG,strDio_pins[u8_Counter].u8_PinNum);
					}
					else if(strDio_pins[u8_Counter].u8_InitState == PIN_NO_PUR)
					{
						CLEAR_BIT(PORTA_REG,strDio_pins[u8_Counter].u8_PinNum);
						
					}					
				}
				else
				{
					return DIO_STATUS_ERROR_NOK;
				}
				
				break;
			}

			case(PORT_B):
			{
   				if(strDio_pins[u8_Counter].u8_Direction == DIO_PIN_DIR_OUTPUT)
   				{
      				SET_BIT(DDRB_REG,strDio_pins[u8_Counter].u8_PinNum);
   					if(strDio_pins[u8_Counter].u8_InitState == PIN_HIGH)
   					{
	   					SET_BIT(PORTB_REG,strDio_pins[u8_Counter].u8_PinNum);
   					}
   					else if(strDio_pins[u8_Counter].u8_InitState == PIN_LOW)
   					{
	   					CLEAR_BIT(PORTB_REG,strDio_pins[u8_Counter].u8_PinNum);
   					}					  
   				}
   				else if(strDio_pins[u8_Counter].u8_Direction == DIO_PIN_DIR_INPUT)
   				{
      				CLEAR_BIT(DDRB_REG,strDio_pins[u8_Counter].u8_PinNum);
   					if(strDio_pins[u8_Counter].u8_InitState == PIN_PUR)
   					{
	   					SET_BIT(PORTB_REG,strDio_pins[u8_Counter].u8_PinNum);
   					}
   					else if(strDio_pins[u8_Counter].u8_InitState == PIN_NO_PUR)
   					{
	   					CLEAR_BIT(PORTB_REG,strDio_pins[u8_Counter].u8_PinNum);
   					}					  
   				}
   				else
   				{
      				return DIO_STATUS_ERROR_NOK;
   				}
   				break;
			}

			case(PORT_C):
			{
   				if(strDio_pins[u8_Counter].u8_Direction == DIO_PIN_DIR_OUTPUT)
   				{
      				SET_BIT(DDRC_REG,strDio_pins[u8_Counter].u8_PinNum);
	   				if(strDio_pins[u8_Counter].u8_InitState == PIN_HIGH)
	   				{
		   				SET_BIT(PORTC_REG,strDio_pins[u8_Counter].u8_PinNum);
	   				}
	   				else if(strDio_pins[u8_Counter].u8_InitState == PIN_LOW)
	   				{
		   				CLEAR_BIT(PORTC_REG,strDio_pins[u8_Counter].u8_PinNum);
	   				}				  
   				}
   				else if(strDio_pins[u8_Counter].u8_Direction == DIO_PIN_DIR_INPUT)
   				{
      				CLEAR_BIT(DDRC_REG,strDio_pins[u8_Counter].u8_PinNum);
	   				if(strDio_pins[u8_Counter].u8_InitState == PIN_PUR)
	   				{
		   				SET_BIT(PORTC_REG,strDio_pins[u8_Counter].u8_PinNum);
	   				}
	   				else if(strDio_pins[u8_Counter].u8_InitState == PIN_NO_PUR)
	   				{
		   				CLEAR_BIT(PORTC_REG,strDio_pins[u8_Counter].u8_PinNum);
	   				}					  
   				}
   				else
   				{
      				return DIO_STATUS_ERROR_NOK;
   				}

   				break;
			}

			case(PORT_D):
			{
   				if(strDio_pins[u8_Counter].u8_Direction == DIO_PIN_DIR_OUTPUT)
   				{
      				SET_BIT(DDRD_REG,strDio_pins[u8_Counter].u8_PinNum);
	   				if(strDio_pins[u8_Counter].u8_InitState == PIN_HIGH)
	   				{
		   				SET_BIT(PORTD_REG,strDio_pins[u8_Counter].u8_PinNum);
	   				}
	   				else if(strDio_pins[u8_Counter].u8_InitState == PIN_LOW)
	   				{
		   				CLEAR_BIT(PORTD_REG,strDio_pins[u8_Counter].u8_PinNum);
	   				}				  
   				}
   				else if(strDio_pins[u8_Counter].u8_Direction == DIO_PIN_DIR_INPUT)
   				{
      				CLEAR_BIT(DDRD_REG,strDio_pins[u8_Counter].u8_PinNum);
		   			if(strDio_pins[u8_Counter].u8_InitState == PIN_PUR)
		   			{
			   			SET_BIT(PORTD_REG,strDio_pins[u8_Counter].u8_PinNum);
		   			}
		   			else if(strDio_pins[u8_Counter].u8_InitState == PIN_NO_PUR)
		   			{
			   			CLEAR_BIT(PORTD_REG,strDio_pins[u8_Counter].u8_PinNum);
		   			}				  
   				}
   				else
   				{
      				return DIO_STATUS_ERROR_NOK;
   				}

   				break;
			}
			default: return DIO_STATUS_ERROR_NOK;

		}
		
	}


		return DIO_STATUS_ERROR_OK;

}

/*****************************************************************************************
* Parameters (in): pin ID and pointer to pin Value you want to read
* Parameters (out): Error Status
* Return value: enuDio_Status_t
* Description: reads the level of a given pin
******************************************************************************************/
enuDio_Status_t Dio_readPin(uint8_t u8_pinID, uint8_t *pu8_pinValue)
{
	
   	switch(strDio_pins[u8_pinID].u8_PortNum)
   	{
      	case(PORT_A):
      	{
			if(BIT_IS_SET(PINA_REG,strDio_pins[u8_pinID].u8_PinNum))
			{
				*pu8_pinValue = PIN_HIGH;
			}
			else if(BIT_IS_CLEAR(PINA_REG,strDio_pins[u8_pinID].u8_PinNum))
			{
				*pu8_pinValue = PIN_LOW;
			}
			else
			{
				return DIO_STATUS_ERROR_NOK;
			}
         	
         	break;
      	}

      	case(PORT_B):
      	{
			if(BIT_IS_SET(PINB_REG,strDio_pins[u8_pinID].u8_PinNum))
			{
   				*pu8_pinValue = PIN_HIGH;
			}
			else if(BIT_IS_CLEAR(PINB_REG,strDio_pins[u8_pinID].u8_PinNum))
			{
   				*pu8_pinValue = PIN_LOW;
			}
			else
			{
   				return DIO_STATUS_ERROR_NOK;
			}
         	break;
      	}

      	case(PORT_C):
      	{
			if(BIT_IS_SET(PINC_REG,strDio_pins[u8_pinID].u8_PinNum))
			{
   				*pu8_pinValue = PIN_HIGH;
			}
			else if(BIT_IS_CLEAR(PINC_REG,strDio_pins[u8_pinID].u8_PinNum))
			{
   				*pu8_pinValue = PIN_LOW;
			}
			else
			{
   				return DIO_STATUS_ERROR_NOK;
			}
         	break;
      	}

      	case(PORT_D):
      	{
			if(BIT_IS_SET(PIND_REG,strDio_pins[u8_pinID].u8_PinNum))
			{
   				*pu8_pinValue = PIN_HIGH;
			}
			else if(BIT_IS_CLEAR(PIND_REG,strDio_pins[u8_pinID].u8_PinNum))
			{
   				*pu8_pinValue = PIN_LOW;
			}
			else
			{
   				return DIO_STATUS_ERROR_NOK;
			}
         	break;
      	}
      	default: return DIO_STATUS_ERROR_NOK;

   	}
   	

	return DIO_STATUS_ERROR_OK;	
}


/*****************************************************************************************
* Parameters (in): pin ID and pin Value
* Parameters (out): Error Status
* Return value: enuDio_Status_t
* Description: writes level to a given pin
******************************************************************************************/
enuDio_Status_t Dio_writePin(uint8_t u8_pinID, uint8_t u8_pinValue)
{
   	switch(strDio_pins[u8_pinID].u8_PortNum)
   	{
	   	case(PORT_A):
	   	{
			if(u8_pinValue == PIN_HIGH)		SET_BIT(PORTA_REG,strDio_pins[u8_pinID].u8_PinNum);
			else if(u8_pinValue == PIN_LOW) CLEAR_BIT(PORTA_REG,strDio_pins[u8_pinID].u8_PinNum);
			else return DIO_STATUS_ERROR_NOK;
		   	
		   	break;
	   	}

	   	case(PORT_B):
	   	{
			if(u8_pinValue == PIN_HIGH)		SET_BIT(PORTB_REG,strDio_pins[u8_pinID].u8_PinNum);
			else if(u8_pinValue == PIN_LOW) CLEAR_BIT(PORTB_REG,strDio_pins[u8_pinID].u8_PinNum);
			else return DIO_STATUS_ERROR_NOK;
		   	break;
	   	}

	   	case(PORT_C):
	   	{
			if(u8_pinValue == PIN_HIGH)		SET_BIT(PORTC_REG,strDio_pins[u8_pinID].u8_PinNum);
			else if(u8_pinValue == PIN_LOW) CLEAR_BIT(PORTC_REG,strDio_pins[u8_pinID].u8_PinNum);
			else return DIO_STATUS_ERROR_NOK;
		   	break;
	   	}

	   	case(PORT_D):
	   	{
			if(u8_pinValue == PIN_HIGH)		SET_BIT(PORTD_REG,strDio_pins[u8_pinID].u8_PinNum);
			else if(u8_pinValue == PIN_LOW) CLEAR_BIT(PORTD_REG,strDio_pins[u8_pinID].u8_PinNum);
			else return DIO_STATUS_ERROR_NOK;
		   	break;
	   	}
	   	default: return DIO_STATUS_ERROR_NOK;

   	}
   	

   	return DIO_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): pin ID 
* Parameters (out): Error Status
* Return value: enuDio_Status_t
* Description: toggles a given pin's state
******************************************************************************************/
enuDio_Status_t Dio_togglePin(uint8_t u8_pinID)
{
   	switch(strDio_pins[u8_pinID].u8_PortNum)
   	{
	   	case(PORT_A):
	   	{
			TOGGLE_BIT(PORTA_REG, strDio_pins[u8_pinID].u8_PinNum);
		   	break;
	   	}

	   	case(PORT_B):
	   	{
			TOGGLE_BIT(PORTB_REG, strDio_pins[u8_pinID].u8_PinNum);
		   	break;
	   	}

	   	case(PORT_C):
	   	{
			TOGGLE_BIT(PORTC_REG, strDio_pins[u8_pinID].u8_PinNum);
		   	break;
	   	}

	   	case(PORT_D):
	   	{
			TOGGLE_BIT(PORTD_REG, strDio_pins[u8_pinID].u8_PinNum);
		   	break;
	   	}
	   	default: return DIO_STATUS_ERROR_NOK;

   	}
   	

   	return DIO_STATUS_ERROR_OK;
}

