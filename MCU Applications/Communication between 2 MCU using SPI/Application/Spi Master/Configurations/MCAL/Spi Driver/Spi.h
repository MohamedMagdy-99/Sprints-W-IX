/*****************************************************************************
* Module: Uart Module
* File Name: Uart.h
* Description: Header file for UART Module
* Author: Mohamed Magdy
* Date: 19-July-2021
******************************************************************************/

#ifndef SPI_H_
#define SPI_H_


/* INCLUDES */

#include "../../Microcontroller/Std_Types.h"
#include "../../Microcontroller/Common_Macros.h"
#include "../../Microcontroller/Spi_Regs.h"
#include "Spi_Cfg.h"
#include "../Dio Driver/Dio.h"
#include "../Interrupt Driver/ISR.h"

/* CONSTANTS */

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/
typedef enum
{
	SPI_STATUS_ERROR_NOK,
	SPI_STATUS_ERROR_OK

}enuSPi_Status_t;

typedef enum
{
	SPI_INITIALIZED,
	SPI_NOT_INITIALIZED
}enuSpi_initStatus_t;



/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t u8_dataOrder;
	uint8_t u8_clockPolarity;
	uint8_t u8_clockPhase;
	uint8_t u8_clockRate;
	uint8_t u8_selectMaster_or_Slave;

}strSpi_Config_t;

/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/
enuSPi_Status_t Spi_init(void);
enuSPi_Status_t Spi_TransmitChar(uint8_t u8_TxData);
enuSPi_Status_t Spi_ReceiveChar(uint8_t* u8_TxData);
enuSPi_Status_t Spi_Transmit_array(uint8_t* u8_TxArray, uint16_t u16_arraySize);
enuSPi_Status_t Spi_Transmit_string(uint8_t* u8_TxString);

/* configuration variable */
extern strSpi_Config_t strSpi_Config;

#endif /* SPI_H_ */