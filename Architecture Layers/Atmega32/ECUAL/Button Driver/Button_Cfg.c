/*****************************************************************************
* Module: Button Module
* File Name: Button_Cfg.c
* Description: Source file for Button Module
* Author: Mohamed Magdy
* Date: 16-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Button.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* here you adjust the buttons configurations */
strButton_Config_t strButton_Config[BUTTONS_USED]=
{
	/*Button Pin */ 
	{  BUTTON_G_DIO_ID },
	{  BUTTON_M_DIO_ID },
	{  BUTTON_R_DIO_ID },
	{  BUTTON_L_DIO_ID }
	
};
/*- APIs IMPLEMENTATION
-----------------------------------*/