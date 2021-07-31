/*
 * Spi Communication Protocol_Master.c
 *
 * Created: 21-Jul-21 3:16:50 AM
 * Author : Mohamed Magdy
 */ 

#include "MCAL/Spi Driver/Spi.h"
#include "MCAL/Uart Driver/Uart.h"


int main(void)
{
	uint8_t u8_uartDataRx = Initial_Value;
	uint8_t au8_uartRxBuffer[256];
	uint16_t u16_counter = Initial_Value;
	uint8_t u8_dontSendFlag = Initial_Value;
	Uart_init();
	Spi_init();
    /* Replace with your application code */
    while (1) 
    {
		while(1)
		{

			Uart_syncReceive_oneFrame(&u8_uartDataRx);

			if(u8_uartDataRx == '\r')
			{
				if(u16_counter >= 256)
				{
					Uart_syncTransmit_string("\rERROR, you can't enter a message more than 255 chars\r");
					u16_counter = Initial_Value;
					u8_dontSendFlag = 1;
					break;
				}
				 Uart_syncTransmit_oneFrame(u8_uartDataRx);
				 au8_uartRxBuffer[u16_counter] = '\0';
				 u16_counter = Initial_Value;
				 break;
			}
			Uart_syncTransmit_oneFrame(u8_uartDataRx);
			if(u16_counter < 256) au8_uartRxBuffer[u16_counter] = u8_uartDataRx;
			++u16_counter;
		}
		
		if(u8_dontSendFlag == 1)
		{
			u8_dontSendFlag = 0;
		}
		else
		{
		
			Spi_Transmit_string(au8_uartRxBuffer);
			Spi_TransmitChar('\0');			
		}

    }
}

