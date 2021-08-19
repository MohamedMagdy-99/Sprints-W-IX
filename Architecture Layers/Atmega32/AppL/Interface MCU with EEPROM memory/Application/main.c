/*
 * Interface MCU with EEPROM memory.c
 *
 * Created: 23-Jul-21 6:26:43 PM
 * Author : Megz
 */ 

#include "Application/App.h"


int main(void)
{
	App_Init();
	/* Replace with your application code */
	while (1)
	{
		App_Update();
	}
}


