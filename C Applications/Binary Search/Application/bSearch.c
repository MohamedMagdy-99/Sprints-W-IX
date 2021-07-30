/*****************************************************************************
* Module: Binary Search Module
* File Name: bSearch.c
* Description: Source file for Binary Search Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "bSearch.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* error state */
EN_Error_t E_State = E_NOK;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): array to be searched, size of array
* Parameters (out): Error State
* Return value: EN_Error_t
* Description: sorts a given array using insertion sort algorithm
************************************************************************************/
/* Function to sort an array using insertion sort*/
EN_Error_t insertionSort(uint8_t* au8_arr, uint8_t u8_NumberOfElements)
{
    uint8_t u8_LoopCounter = Initial_Value;
    uint8_t u8_HoleIndex = Initial_Value;
    uint8_t u8_tempValue = Initial_Value;

    for(u8_LoopCounter=1; u8_LoopCounter < u8_NumberOfElements-1; u8_LoopCounter++)
    {
        u8_HoleIndex = u8_LoopCounter;
        u8_tempValue = au8_arr[u8_LoopCounter];
        while(u8_HoleIndex > 0 && au8_arr[u8_HoleIndex-1]>u8_tempValue)
        {
            au8_arr[u8_HoleIndex] = au8_arr[u8_HoleIndex-1];
            u8_HoleIndex--;
        }
        au8_arr[u8_HoleIndex] = u8_tempValue;
    }
    return E_OK;
}

/************************************************************************************
* Parameters (in): array to be searched, size of array
* Parameters (out): Array State
* Return value: uint8_t
* Description: checks if a given array is sorted or not
************************************************************************************/
uint8_t arraySortedOrNot(uint8_t* au8_arr, uint8_t u8_NumberOfElements)
{
    // Array has one or no element
    if (u8_NumberOfElements == 0 || u8_NumberOfElements == 1)
        return Arr_Sorted;

    uint8_t u8_LoopCounter = Initial_Value;
    for (u8_LoopCounter = 1; u8_LoopCounter < u8_NumberOfElements; u8_LoopCounter++)
    {
        // Unsorted pair found
        if (au8_arr[u8_LoopCounter - 1] > au8_arr[u8_LoopCounter])
        {
            return Arr_Not_Sorted;
        }

    }
    // No unsorted pair found
    return Arr_Sorted;
}

/************************************************************************************
* Parameters (in): array to be searched, size of array, number to be searched for
* Parameters (out): Number
* Return value: uint8_t
* Description: searches for a number in an array
************************************************************************************/
uint8_t binarySearch(uint8_t* au8_arr, uint8_t u8_NumberOfElements, uint8_t u8_Number)
{
    if(arraySortedOrNot(au8_arr,u8_NumberOfElements)== Arr_Not_Sorted)
    {
        insertionSort(au8_arr,u8_NumberOfElements);
    }
   uint8_t u8_Start = Initial_Value;
   uint8_t u8_End = u8_NumberOfElements-1;
   uint8_t u8_Mid = Initial_Value;

   while(u8_Start <= u8_End)
   {
       u8_Mid = u8_Start + ((u8_End-u8_Start)/2);

       if(au8_arr[u8_Mid] == u8_Number)
       {
           //printf("\nNumber ( %d ) was found\n", u8_Number);
           return au8_arr[u8_Mid];
       }
       else if(u8_Number < au8_arr[u8_Mid])
       {
           u8_End = u8_Mid-1;
       }
       else
       {
           u8_Start = u8_Mid+1;
       }
   }

        printf("\nNumber ( %d ) was not found\n", u8_Number);
       return Number_Not_Found;
   }


/*- APIs IMPLEMENTATION
-----------------------------------*/
