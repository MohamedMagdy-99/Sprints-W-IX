/*
 * Control MCU over UART communication.c
 *
 * Created: 20-Jul-21 3:38:54 AM
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

