/*
 * ATM ECU.c
 *
 * Created: 28-Jul-21 2:54:09 PM
 * Author : Megz
 */ 

#include "Application/AtmECU.h"


int main(void)
{
	Atm_Init();
    /* Replace with your application code */
    while (1) 
    {
		Atm_Update();
    }
}

