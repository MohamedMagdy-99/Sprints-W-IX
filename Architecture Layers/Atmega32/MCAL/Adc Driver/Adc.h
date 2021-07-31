/*****************************************************************************
* Module: Adc Module
* File Name: Adc.h
* Description: Header file for Adc Module
* Author: Mohamed Magdy
* Date: 25-July-2021
******************************************************************************/


#ifndef ADC_H_
#define ADC_H_

/* INCLUDES */

#include "../../Microcontroller/Std_Types.h"
#include "../../Microcontroller/Common_Macros.h"
#include "../../Microcontroller/Adc_Regs.h"
#include "Adc_Cfg.h"
#include "../Dio Driver/Dio.h"
#include "../Interrupt Driver/ISR.h"

/* CONSTANTS */

#define ResolutionLevels	1024
/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void (*pfAdc_CallBack_t)(void);
/*- ENUMS --------------------------------------------------*/
typedef enum
{
	ADC_STATUS_ERROR_NOK,
	ADC_STATUS_ERROR_OK

}enuAdc_Status_t;

typedef enum
{
	ADC_INITIALIZED,
	ADC_NOT_INITIALIZED
}enuAdc_initStatus_t;



/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t u8_channelId;
	uint8_t u8_channelVref;
	
}strAdc_Config_t;

/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/

enuAdc_Status_t Adc_init(void);
enuAdc_Status_t Adc_start(uint8_t u8_channelId, uint16_t* pu16_milliVolts); 
enuAdc_Status_t Adc_startWithInterrupt(uint8_t u8_channelId,  pfAdc_CallBack_t FunToBeCalledInISR);

enuAdc_Status_t Adc_readFromISR(uint16_t* pu16_milliVolts);

enuAdc_Status_t Adc_stop(void); 

void Adc_setCallBack(pfAdc_CallBack_t FunToBeCalledInISR);


/* configuration variable */
extern strAdc_Config_t strAdc_Channles[ADC_USED_CHANNELS_NUM];

#endif /* ADC_H_ */