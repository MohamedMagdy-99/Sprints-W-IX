/*
 * I2C Slave.c
 *
 * Created: 22-Jul-21 3:54:15 AM
 * Author : Mohamed Magdy
 */ 

#include "MCAL/I2C Driver/I2C.h"
#include "Microcontroller/Port_Regs.h"

int main(void)
{
	uint8_t rxData;
	DDRA_REG = 0xFF;
	PORTA_REG = 0x00;
	I2C_init();
	/* Replace with your application code */
	while (1)
	{
		I2C_SlaveListen();
	
		switch(gu8_SlaveListenStatus)
		{
	
			case(SlaveWrite):
			{	
				do 
				{
					I2C_SlaveWrite(0xFF);
				}while(gu8_SlaveWriteStatus == DataByteSent_AckReceived);
				break;
			}
			case(SlaveRead):
			{
				do 
				{
					I2C_SlaveRead(&rxData);
				}while(gu8_SlaveReadStatus != Stop_RepeatedStart_Recevied_InSlaveMode);
				break;
			}
			default: break;
		}
	
		PORTA_REG = rxData;
	}	
}

