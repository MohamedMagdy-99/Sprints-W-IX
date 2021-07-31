 /******************************************************************************
 *
 * Module: main
 *
 * File Name: main.c
 *
 * Description: main program
 *
 * Author: Mohamed Magdy
 *
 * Date: 14-July-2021
 *******************************************************************************/

#include "Application/CarApp.h"


int main(void)
{
   
	Car_Init();
  
    while (1) 
    {
		Car_Update();

    }
}

