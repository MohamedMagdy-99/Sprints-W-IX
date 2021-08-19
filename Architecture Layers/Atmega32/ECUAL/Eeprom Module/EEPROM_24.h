/*****************************************************************************
* Module: EEPROM_24 Module
* File Name: EEPROM_24.h
* Description: Header file for EEPROM_24 Module
* Author: Mohamed Magdy
* Date: 22-July-2021
******************************************************************************/

#ifndef EEPROM_24_H_
#define EEPROM_24_H_


/* INCLUDES */

#include "Std_Types.h"
#include "Common_Macros.h"
#include "I2C.h"
#include "EEPROM_24_Cfg.h"



/* CONSTANTS */




/*- ENUMS --------------------------------------------------*/
typedef enum
{
	EEPROM_STATUS_ERROR_NOK,
	EEPROM_STATUS_ERROR_OK

}enuEeprom_24_Status_t;

/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/

/*- Initialize the EEPROM Module -*/
enuEeprom_24_Status_t Eeprom_24_init(void);

/*- Write Byte to specific location in the Memory -*/
enuEeprom_24_Status_t  Eeprom_24_writeByte(uint16_t u16_location, uint8_t u8_data);

/*- Read Byte from specific location in the Memory -*/
enuEeprom_24_Status_t  Eeprom_24_readByte(uint16_t u16_location, uint8_t* pu8_data);

// /*- Write Page to specific location in the Memory -*/
// enuEeprom_24_Status_t  Eeprom_24_writePage(uint8_t u8_page, uint8_t *pu8_data);
// 
// /*- Read Page from specific location in the Memory -*/
// enuEeprom_24_Status_t  Eeprom_24_readPage(uint8_t u8_page, uint8_t *pu8_data);

/*- Write Multiple Bytes to specific location in the Memory -*/
enuEeprom_24_Status_t  Eeprom_24_writePacket(uint16_t u16_location, uint8_t *pu8_data, uint16_t u16_dataLen);

/*- Read Multiple Bytes from specific location in the Memory -*/
enuEeprom_24_Status_t  Eeprom_24_readPacket(uint16_t u16_location, uint8_t *pu8_data, uint16_t u16_dataLen);
/* configuration variable */

/* extern */



#endif /* EEPROM_24_H_ */