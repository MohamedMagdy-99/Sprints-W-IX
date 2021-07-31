/*****************************************************************************
* Module: SW_PWM Module
* File Name: SWPwm.h
* Description: Header file for SW_PWM Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/


#ifndef SW_PWM_H_
#define SW_PWM_H_

/*- INCLUDES -----------------------------------------------*/
#include "../../MCAL/Dio Driver/Dio.h"
#include "../../MCAL/Gpt Driver/Gpt.h"
#include "SWPwm_Cfg.h"
/*- CONSTANTS ----------------------------------------------*/
#define F_CPU 1000000UL

/*- ENUMS --------------------------------------------------*/
typedef enum
{
	SWPWM_STATUS_ERROR_NOK,
	SWPWM_STATUS_ERROR_OK,
	SWPWM_STATUS_ALREADY_RUNNING,
	SWPWM_STATUS_NOT_RUNNING
}enuSWPwm_Status_t;

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t u8_DioId;
	uint8_t u8_TimerChannelId;


}strPwm_Config_t;

typedef struct
{
	uint8_t u8_ChannelID;
	uint8_t u8_TurnTicks;
	uint32_t u32_OnTimeTicks;
	uint32_t u32_OffTimeTicks;

}strPwm_sharedData_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/
enuSWPwm_Status_t SWPwm_Init(void); 

enuSWPwm_Status_t SWPwm_Start(uint8_t u8_ChannelID, uint32_t u32_Freq, uint8_t u8_DutyCycle);

enuSWPwm_Status_t SWPwm_Stop(uint8_t u8_ChannelID);
 
 void PWM_Generate(void);
 
/*- EXTERN VARIABLE DECLARATIONS ----------------------------------*/
extern strPwm_Config_t strPwm_channels[USED_PWM_CHANNELS];

#endif /* SW_PWM_H_ */