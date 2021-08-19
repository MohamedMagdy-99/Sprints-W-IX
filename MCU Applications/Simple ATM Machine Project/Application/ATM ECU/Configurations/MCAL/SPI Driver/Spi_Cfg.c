/*****************************************************************************
* Module: Spi Module
* File Name: Spi_Cfg.c
* Description: Source file for SPI Module
* Author: Mohamed Magdy
* Date: 20-July-2021
******************************************************************************/


/*- INCLUDES
----------------------------------------------*/
#include "Spi.h"


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* configuration of used spi */
strSpi_Config_t strSpi_Config =
{
	/* dataOrder */       /* clockPolarity */   /* clockPhase */    /* clockRate */     /* selectMaster_or_Slave */
	   MSB_FIRST    ,			SCK_LOW_IDLE  ,	     SAMPLE_LEADING  ,	 DIV_128         ,       SLAVE_SPI
		
};