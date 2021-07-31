/*****************************************************************************
* Module: Car Module
* File Name: CarApp.h
* Description: Header file for Car Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/


#ifndef CARAPP_H_
#define CARAPP_H_

/*- INCLUDES -----------------------------------------------*/
#include "../MCAL/Dio Driver/Dio.h"
#include "../MCAL/Gpt Driver/Gpt.h"
#include "../MCAL/SW_Pwm Driver/SWPwm.h"
#include "../ECUAL/Button Driver/Button.h"
#include "../ECUAL/Motor Driver/Motor.h"
/*- CONSTANTS ----------------------------------------------*/
#define SPEED_30_FORWARD	1
#define SPEED_60_FORWARD	2
#define SPEED_90_FORWARD	3
#define SPEED_30_BACKWARD	4

#define SPEED_30	30
#define SPEED_60	60
#define SPEED_90	90
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
typedef enum
{
	CAR_STATUS_ERROR_NOK,
	CAR_STATUS_ERROR_OK,
	CAR_STATUS_INITIAL,
	CAR_STATUS_SPEED_30_FW,
	CAR_STATUS_SPEED_60_FW,
	CAR_STATUS_SPEED_90_FW,
	CAR_STATUS_SPEED_30_BW,
	CAR_STATUS_SPEED_30_L,
	CAR_STATUS_SPEED_30_R
	
}enuCar_Status_t;

/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/

enuCar_Status_t Car_Init(void);
enuCar_Status_t Car_Update(void);


#endif /* CARAPP_H_ */