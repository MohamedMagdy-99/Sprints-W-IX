/*****************************************************************************
* Module: Lcd Module
* File Name: Lcd_Cfg.h
* Description: Header file for Lcd Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "Lcd.h"

#define Lcd_Rows			2
#define Lcd_Columns			16

#define RS_DIO_ID			PORTC_PIN5_ID	
#define RW_DIO_ID			PORTC_PIN6_ID	
#define EN_DIO_ID			PORTC_PIN7_ID

#define D4_DIO_ID			PORTD_PIN4_ID
#define D5_DIO_ID			PORTD_PIN5_ID
#define D6_DIO_ID			PORTD_PIN6_ID
#define D7_DIO_ID			PORTD_PIN7_ID

#endif /* LCD_CFG_H_ */