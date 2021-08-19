/*****************************************************************************
* Module: EEPROM_24 Module
* File Name: EEPROM_24_Cfg.h
* Description: Header file for EEPROM_24 Module
* Author: Mohamed Magdy
* Date: 22-July-2021
******************************************************************************/

#ifndef EEPROM_24_CFG_H_
#define EEPROM_24_CFG_H_

#define AT24C256B    1
#define AT24C16B	 2

#define MODEL	AT24C16B

#if MODEL == AT24C16B
#define SLAVE_ADDRESS_EEPROM		0x0A
#elif MODEL == AT24C256B
#define SLAVE_ADDRESS_EEPROM		0xA0
#endif


#endif /* EEPROM_24_CFG_H_ */