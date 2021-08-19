/*
 * Spi Communication Protocol_Master.c
 *
 * Created: 21-Jul-21 3:16:50 AM
 * Author : Mohamed Magdy
 */ 

#include "MCAL/Spi Driver/Spi.h"



int main(void)
{

	Spi_init();
    /* Replace with your application code */
    while (1) 
    {
		Spi_MasterTransmitChar(0x55);
	}

}

