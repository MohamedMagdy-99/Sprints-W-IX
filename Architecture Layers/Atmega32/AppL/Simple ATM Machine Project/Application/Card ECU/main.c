/*
 *		Card ECU
 *
 * Created: 26-Jul-21 1:07:44 PM
 * Author : Mohamed Magdy
 */ 

#include "Application/CardECU.h"


int main(void)
{
	Card_Init();
	
    /* Replace with your application code */
    while (1) 
    {
		Card_Update();
    }
}

