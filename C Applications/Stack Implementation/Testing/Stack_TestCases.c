/*****************************************************************************
* Module: Stack Module
* File Name: Stack_TestCases.c
* Description: Source file for Stack Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
#include "Stack.h"

/************************************************************************************
* Parameters (in): Expression
* Parameters (out): Error State
* Return value: EN_Error_t*
* Description: tests the case if the given array expression is balanced
************************************************************************************/
EN_Error_t TestCase1_Balanced(void)
{
    uint8_t expression[20] = "[{{{{((123))}}}}]";
    if(balancedParentheses(expression) == "Balanced")
    {
        return E_OK;
    }
    else
    {
        return E_NOK;
    }
}

/************************************************************************************
* Parameters (in): Expression
* Parameters (out): Error State
* Return value: EN_Error_t*
* Description: tests the case if the given array expression is not balanced
************************************************************************************/
EN_Error_t TestCase2_NotBalanced(void)
{
    uint8_t expression[15] = "[{{{{((123))}}}}";
    if(balancedParentheses(expression) == "Not Balanced")
    {
        return E_OK;
    }
    else
    {
        return E_NOK;
    }
}
/*

int main()
{
    if(TestCase1_Balanced == E_NOK)
    {
        printf("\n\nTest Case 1 Failed\n");
    }
    else
    {
        printf("\n\nTest Case 1 Passed\n");
    }

    if(TestCase2_NotBalanced == E_NOK)
    {
        printf("\n\nTest Case 2 Failed\n");
    }
    else
    {
        printf("\n\nTest Case 2 Passed\n");
    }
    return E_OK;
}
*/
