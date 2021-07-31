/*
 * Spi Communication Protocol_Slave.c
 *
 * Created: 21-Jul-21 4:15:44 AM
 * Author : Megz
 */ 

#include "MCAL/Spi Driver/Spi.h"



int main(void)
{
	uint8_t u8_spiDataRx = Initial_Value;
	DDRD_REG = 0xFF;
	PORTD_REG = 0x00;
	Spi_init();
	/* Replace with your application code */
	while (1)
	{
		
		Spi_SlaveReceiveChar(&u8_spiDataRx);
		PORTD_REG = u8_spiDataRx;
	}
}