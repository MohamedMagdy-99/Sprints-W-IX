/*****************************************************************************
* Module: Main Module
* File Name: main.c
* Description: Source file for Main Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
#include "PaymentSystem.h"

int main()
{
    uint8_t u8_NewTrans = Initial_Value;
    do
    {
        PaymentSystemStart();
        printf("\nDo you want to continue (y/n)\n");
        scanf(" %c", &u8_NewTrans);
    }
    while(u8_NewTrans == 'y');

    return 0;
}

