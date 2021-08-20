/*****************************************************************************
* Module: Dio Module
* File Name: Dio.h
* Description: Header file for DIO Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/


#ifndef DIO_H_
#define DIO_H_

/* INCLUDES */

#include "../../Microcontroller/Std_Types.h"
#include "../../Libraries/Common_Macros.h"
#include "../../Microcontroller/Atmega32 Registers/Port_Regs.h"
#include "Dio_Cfg.h"



/*- ENUMS --------------------------------------------------*/
typedef enum 
{
	DIO_STATUS_ERROR_NOK,
	DIO_STATUS_ERROR_OK

}enuDio_Status_t;

typedef enum
{
	DIO_INITIALIZED,
	DIO_NOT_INITIALIZED
}enuDio_initStatus_t;

typedef enum
{
	DIO_PIN_DIR_INPUT,
	DIO_PIN_DIR_OUTPUT
}enuDio_Direction_t;

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t u8_PortNum;
	uint8_t u8_PinNum;
	enuDio_Direction_t u8_Direction;
	uint8_t u8_InitState; /* 1 or 0 for output pin // Pull Down or Pull Up for Input pin*/
}strDio_Config_t;

/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/

/** pinID is the index of the pin structure in the configuration array of structures */

/* initalize the pins function */
enuDio_Status_t Dio_init(void);

/* read pin state */
enuDio_Status_t Dio_readPin(uint8_t u8_pinID, uint8_t *pu8_pinValue);

/* write a state to the pin */
enuDio_Status_t Dio_writePin(uint8_t u8_pinID, uint8_t u8_pinValue);

/* toggle a pin */
enuDio_Status_t Dio_togglePin(uint8_t u8_pinID);


/* configuration variable */
extern strDio_Config_t strDio_pins[DIO_USED_PINS_NUM];

#endif /* DIO_H_ */