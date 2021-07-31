/*
 * I2C Master.c
 *
 * Created: 22-Jul-21 3:39:41 AM
 * Author : Mohamed Magdy
 */ 
#include "MCAL/I2C Driver/I2C.h"


int main(void)
{
int i;
	I2C_init();	
for(i=0;i<5000;i++);
	I2C_Start(SLAVE_ADDRESS_W);
	for(i=0;i<5000;i++);

	I2C_MasterWrite(0xAA);
	for(i=0;i<5000;i++);
	I2C_Stop();
    /* Replace with your application code */
    while (1) 
    {
    }
}

