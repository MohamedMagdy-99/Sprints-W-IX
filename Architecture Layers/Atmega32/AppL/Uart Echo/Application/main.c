

#include "MCAL/Uart Driver/Uart.h"

int main(void)
{
	 uint8_t c;
	Uart_init();
	Uart_syncTransmit_array("Echo Test\r", 9);
    /* Replace with your application code */
  	
			
			while(1)
			{
				
				Uart_syncReceive_oneFrame(&c);
				Uart_syncTransmit_oneFrame(c);
			}
 
}

