/*****************************************************************************
* Module: Binary Search Module
* File Name: bSearch_TestCases.c
* Description: Source file for Binary Search Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
/*- INCLUDES -----------------------------------------------*/
#include "bSearch.h"

/* array samples used to test */
uint8_t arr_notSorted[10] = {5,9,8,6,1,22,78,96,1,0};
uint8_t arr_Sorted[10] = {1,2,3,4,5,6,7,8,9,10};

/************************************************************************************
* Parameters (in): array to be searched, size of array, number to be searched for
* Parameters (out): Error State
* Return value: EN_Error_t
* Description: tests the case if a number exists in an array
************************************************************************************/
EN_Error_t TestCase1_NumberExist(uint8_t* au8_arr, uint8_t u8_NumberOfElements, uint8_t u8_Number)
{
    if(binarySearch(au8_arr, u8_NumberOfElements, u8_Number) != Number_Not_Found)
    {
        return E_OK;
    }
    else
    {
        return E_NOK;
    }
}

/************************************************************************************
* Parameters (in): array to be searched, size of array, number to be searched for
* Parameters (out): Error State
* Return value: EN_Error_t
* Description: tests the case if a number doesn't exists in an array
************************************************************************************/
EN_Error_t TestCase2_NumberNotExist(uint8_t* au8_arr, uint8_t u8_NumberOfElements, uint8_t u8_Number)
{
    if(binarySearch(au8_arr, u8_NumberOfElements, u8_Number) != Number_Not_Found)
    {
        return E_NOK;
    }
    else
    {
        return E_OK;
    }
}

/************************************************************************************
* Parameters (in): array to be searched, size of array
* Parameters (out): Error State
* Return value: EN_Error_t
* Description: tests the case if an array is sorted
************************************************************************************/
EN_Error_t TestCase3_ArraySorted(uint8_t* au8_arr, uint8_t u8_NumberOfElements)
{
    if(arraySortedOrNot(au8_arr, u8_NumberOfElements) == Arr_Sorted)
    {
        return E_OK;
    }
    else
    {
        return E_NOK;
    }
}

/************************************************************************************
* Parameters (in): array to be searched, size of array
* Parameters (out): Error State
* Return value: EN_Error_t
* Description: tests the case if an array is not sorted
************************************************************************************/
EN_Error_t TestCase4_ArrayNotSorted(uint8_t* au8_arr, uint8_t u8_NumberOfElements)
{
    if(arraySortedOrNot(au8_arr, u8_NumberOfElements) == Arr_Not_Sorted)
    {
        return E_OK;
    }
    else
    {
        return E_NOK;
    }
}

int main()
{
    if(TestCase1_NumberExist(arr_notSorted,10,1) == E_OK)
    {
        printf("\n\nTest Case 1 Passed\n");
    }
    else
    {
       printf("\n\nTest Case 1 Failed\n");
    }

    if(TestCase2_NumberNotExist(arr_notSorted,10,10) == E_OK)
    {
        printf("\n\nTest Case 2 Passed\n");
    }
    else
    {
       printf("\n\nTest Case 2 Failed\n");
    }

    if(TestCase3_ArraySorted(arr_Sorted,10) == E_OK)
    {
        printf("\n\nTest Case 3 Passed\n");
    }
    else
    {
       printf("\n\nTest Case 3 Failed\n");
    }

    if(TestCase4_ArrayNotSorted(arr_notSorted,10) == E_OK)
    {
        printf("\n\nTest Case 4 Passed\n");
    }
    else
    {
       printf("\n\nTest Case 4 Failed\n");
    }
}
