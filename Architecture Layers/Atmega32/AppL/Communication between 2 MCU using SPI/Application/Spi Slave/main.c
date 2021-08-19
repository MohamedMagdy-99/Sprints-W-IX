/*
 * Spi Communication Protocol_Slave.c
 *
 * Created: 21-Jul-21 4:15:44 AM
 * Author : Megz
 */ 

#include "MCAL/Spi Driver/Spi.h"
#include "MCAL/Uart Driver/Uart.h"


int main(void)
{
	uint8_t u8_spiDataRx = Initial_Value;
	uint8_t au8_spiRxBuffer[256];
	uint16_t u16_counter = Initial_Value;
	Uart_init();
	Spi_init();
	/* Replace with your application code */
	while (1)
	{
		while(1)
		{
			Spi_ReceiveChar(&u8_spiDataRx);

			if(u8_spiDataRx == '\0')
			{
				au8_spiRxBuffer[u16_counter] = '\0';
				u16_counter = Initial_Value;
				break;
			}
			
			au8_spiRxBuffer[u16_counter] = u8_spiDataRx;
			++u16_counter;
		}
		
		Uart_syncTransmit_string(au8_spiRxBuffer);
		Uart_syncTransmit_oneFrame('\r');
	}
}