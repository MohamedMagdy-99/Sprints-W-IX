/*****************************************************************************
* Module: Binary Search Module
* File Name: bSearch.h
* Description: Header file for Binary Search Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
#ifndef BSEARCH_H_INCLUDED
#define BSEARCH_H_INCLUDED
/*- INCLUDES -----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "Std_Types.h"
/*- CONSTANTS ----------------------------------------------*/
#define Initial_Value   0
#define Number_Not_Found 100
#define Arr_Sorted   99
#define Arr_Not_Sorted  98

/*- ENUMS --------------------------------------------------*/
typedef enum EN_Error_t
{
    E_OK,
    E_NOK
}EN_Error_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/
EN_Error_t insertionSort(uint8_t* au8_arr, uint8_t u8_NumberOfElements);
uint8_t arraySortedOrNot(uint8_t* au8_arr, uint8_t u8_NumberOfElements);
uint8_t binarySearch(uint8_t* au8_arr, uint8_t u8_NumberOfElements, uint8_t u8_Number);



#endif // BSEARCH_H_INCLUDED
