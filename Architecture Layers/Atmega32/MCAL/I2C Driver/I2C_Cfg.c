/*****************************************************************************
* Module: I2C Module
* File Name: I2C_Cfg.c
* Description: Source file for I2C Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/


/*- INCLUDES
----------------------------------------------*/
#include "I2C.h"


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* configuration of used i2c */
strI2C_Config_t strI2C_Config =
{
	/* Master or Slave */     /* Prescaler */    /* Slave Address */   
	    MASTER_I2C         ,		PRESCALER        ,  SLAVE_ADDRESS  
	
};