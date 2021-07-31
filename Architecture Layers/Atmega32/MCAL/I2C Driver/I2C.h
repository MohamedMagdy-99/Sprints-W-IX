/*****************************************************************************
* Module: I2C Module
* File Name: I2C.h
* Description: Header file for I2C Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/

#ifndef I2C_H_
#define I2C_H_


/* INCLUDES */

#include "../../Microcontroller/Std_Types.h"
#include "../../Microcontroller/Common_Macros.h"
#include "../../Microcontroller/I2C_Regs.h"
#include "I2C_Cfg.h"



/* CONSTANTS */
#define I2C_TWBR_VALUE()		(uint8_t)(((F_OSC/I2C_SCL_CLK)-16)/(2*PRESCALER))
/* STATUS CODES */
#define Address_W_Sent_AckReceived										0x18
	
#define OwnAddressReceived_W_AckSent									0x60
#define MasterLostArbitration_OwnAddressReceived_W_AckSent				0x68

#define GeranlCallAddressReceived_AckSent								0x70
#define MasterLostArbitration_GeranlCallAddressReceived_AckSent			0x78

#define OwnAddressReceived_R_AckSent									0xA8
#define MasterLostArbitration_OwnAddressReceived_R_AckSent				0xB0

#define DataByteSent_AckReceived										0xB8
#define DataByteSent_NackReceived										0xC0


#define Stop_RepeatedStart_Recevied_InSlaveMode							0xA0

#define	SlaveWrite														0xFF
#define SlaveRead														0xAA
/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/
typedef enum
{
	I2C_STATUS_ERROR_NOK,
	I2C_STATUS_ERROR_OK

}enuI2C_Status_t;

typedef enum
{
	I2C_INITIALIZED,
	I2C_NOT_INITIALIZED
}enuI2C_initStatus_t;



/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{

	uint8_t u8_selectMaster_or_Slave;
	uint8_t u8_prescaler;
	uint8_t u8_slaveAdress;

}strI2C_Config_t;

/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/
enuI2C_Status_t I2C_init(void);
enuI2C_Status_t I2C_Start(uint8_t address);
enuI2C_Status_t I2C_Stop(void);
enuI2C_Status_t I2C_RepeatedStart(uint8_t address);
enuI2C_Status_t I2C_StartWait(uint8_t address);

enuI2C_Status_t I2C_MasterWrite(uint8_t data);
enuI2C_Status_t I2C_MasterRead_Ack(uint8_t* RxData);
enuI2C_Status_t I2C_MasterRead_Nack(uint8_t* RxData);

enuI2C_Status_t I2C_SlaveListen(void);
enuI2C_Status_t I2C_SlaveWrite(uint8_t data);
enuI2C_Status_t I2C_SlaveRead(uint8_t* RxData);
/* configuration variable */
extern strI2C_Config_t strI2C_Config;
/* extern */
extern uint8_t gu8_SlaveListenStatus;
extern uint8_t gu8_SlaveWriteStatus;
extern uint8_t gu8_SlaveReadStatus;
#endif /* I2C_H_ */