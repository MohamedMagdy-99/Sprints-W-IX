/*****************************************************************************
* Module: XO_Game Module
* File Name: XO_Game_TestCases.c
* Description: Source file for XO_Game Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
#include"XO_Game.h"
/* array which represents the grid */
extern uint8_t gau8_CharactersToBeDisplayedOnMatrix[Number_Of_Rows][Number_Of_Columns];


/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: tests if the current grid matrix has a horizontal win condition
* or not for player 'X'
************************************************************************************/
E_Status_t TestHorizontalWin_X(void)
{
    E_Status_t status = E_NOK;

    gau8_CharactersToBeDisplayedOnMatrix[0][0] = 'X';
    gau8_CharactersToBeDisplayedOnMatrix[0][1] = 'X';
    gau8_CharactersToBeDisplayedOnMatrix[0][2] = 'X';

    if(CheckWinner() == End_of_Program)
    {
        status = E_OK;
    }

    // return the array to default to not interfere with other test cases
    gau8_CharactersToBeDisplayedOnMatrix[0][0] = '1';
    gau8_CharactersToBeDisplayedOnMatrix[0][1] = '2';
    gau8_CharactersToBeDisplayedOnMatrix[0][2] = '3';

    return status;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: tests if the current grid matrix has a horizontal win condition
* or not for player 'O'
************************************************************************************/
E_Status_t TestHorizontalWin_O(void)
{
    E_Status_t status = E_NOK;

    gau8_CharactersToBeDisplayedOnMatrix[0][0] = 'O';
    gau8_CharactersToBeDisplayedOnMatrix[0][1] = 'O';
    gau8_CharactersToBeDisplayedOnMatrix[0][2] = 'O';

    if(CheckWinner() == End_of_Program)
    {
        status = E_OK;
    }

    // return the array to default to not interfere with other test cases
    gau8_CharactersToBeDisplayedOnMatrix[0][0] = '1';
    gau8_CharactersToBeDisplayedOnMatrix[0][1] = '2';
    gau8_CharactersToBeDisplayedOnMatrix[0][2] = '3';

    return status;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: tests if the current grid matrix has a vertical win condition
* or not for player 'O'
************************************************************************************/
E_Status_t TestVerticalWin_O(void)
{
    E_Status_t status = E_NOK;

    gau8_CharactersToBeDisplayedOnMatrix[0][0] = 'O';
    gau8_CharactersToBeDisplayedOnMatrix[1][0] = 'O';
    gau8_CharactersToBeDisplayedOnMatrix[2][0] = 'O';

    if(CheckWinner() == End_of_Program)
    {
        status = E_OK;
    }

    // return the array to default to not interfere with other test cases
    gau8_CharactersToBeDisplayedOnMatrix[0][0] = '1';
    gau8_CharactersToBeDisplayedOnMatrix[1][0] = '4';
    gau8_CharactersToBeDisplayedOnMatrix[2][0] = '7';

    return status;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: tests if the current grid matrix has a vertical win condition
* or not for player 'X'
************************************************************************************/
E_Status_t TestVerticalWin_X(void)
{
    E_Status_t status = E_NOK;

    gau8_CharactersToBeDisplayedOnMatrix[0][0] = 'X';
    gau8_CharactersToBeDisplayedOnMatrix[1][0] = 'X';
    gau8_CharactersToBeDisplayedOnMatrix[2][0] = 'X';

    if(CheckWinner() == End_of_Program)
    {
        status = E_OK;
    }

    // return the array to default to not interfere with other test cases
    gau8_CharactersToBeDisplayedOnMatrix[0][0] = '1';
    gau8_CharactersToBeDisplayedOnMatrix[1][0] = '4';
    gau8_CharactersToBeDisplayedOnMatrix[2][0] = '7';

    return status;
}


/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: tests if the current grid matrix has a right diagonal win condition
* or not for player 'O'
************************************************************************************/
E_Status_t TestRightDiagonalWin_O(void)
{
    E_Status_t status = E_NOK;

    gau8_CharactersToBeDisplayedOnMatrix[0][2] = 'O';
    gau8_CharactersToBeDisplayedOnMatrix[1][1] = 'O';
    gau8_CharactersToBeDisplayedOnMatrix[2][0] = 'O';

    if(CheckWinner() == End_of_Program)
    {
        status = E_OK;
    }

    // return the array to default to not interfere with other test cases
    gau8_CharactersToBeDisplayedOnMatrix[0][2] = '3';
    gau8_CharactersToBeDisplayedOnMatrix[1][1] = '5';
    gau8_CharactersToBeDisplayedOnMatrix[2][0] = '7';

    return status;
}


/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: tests if the current grid matrix has a right diagonal win condition
* or not for player 'X'
************************************************************************************/
E_Status_t TestRightDiagonalWin_X(void)
{
    E_Status_t status = E_NOK;

    gau8_CharactersToBeDisplayedOnMatrix[0][2] = 'X';
    gau8_CharactersToBeDisplayedOnMatrix[1][1] = 'X';
    gau8_CharactersToBeDisplayedOnMatrix[2][0] = 'X';

    if(CheckWinner() == End_of_Program)
    {
        status = E_OK;
    }

    // return the array to default to not interfere with other test cases
    gau8_CharactersToBeDisplayedOnMatrix[0][2] = '3';
    gau8_CharactersToBeDisplayedOnMatrix[1][1] = '5';
    gau8_CharactersToBeDisplayedOnMatrix[2][0] = '7';

    return status;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: tests if the current grid matrix has a left diagonal win condition
* or not for player 'X'
************************************************************************************/
E_Status_t TestLeftDiagonalWin_X(void)
{
    E_Status_t status = E_NOK;

    gau8_CharactersToBeDisplayedOnMatrix[0][0] = 'X';
    gau8_CharactersToBeDisplayedOnMatrix[1][1] = 'X';
    gau8_CharactersToBeDisplayedOnMatrix[2][2] = 'X';

    if(CheckWinner() == End_of_Program)
    {
        status = E_OK;
    }

    // return the array to default to not interfere with other test cases
    gau8_CharactersToBeDisplayedOnMatrix[0][0] = '1';
    gau8_CharactersToBeDisplayedOnMatrix[1][1] = '5';
    gau8_CharactersToBeDisplayedOnMatrix[2][2] = '9';

    return status;
}


/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: tests if the current grid matrix has a left diagonal win condition
* or not for player 'O'
************************************************************************************/
E_Status_t TestLeftDiagonalWin_O(void)
{
    E_Status_t status = E_NOK;

    gau8_CharactersToBeDisplayedOnMatrix[0][0] = 'O';
    gau8_CharactersToBeDisplayedOnMatrix[1][1] = 'O';
    gau8_CharactersToBeDisplayedOnMatrix[2][2] = 'O';

    if(CheckWinner() == End_of_Program)
    {
        status = E_OK;
    }

    // return the array to default to not interfere with other test cases
    gau8_CharactersToBeDisplayedOnMatrix[0][0] = '1';
    gau8_CharactersToBeDisplayedOnMatrix[1][1] = '5';
    gau8_CharactersToBeDisplayedOnMatrix[2][2] = '9';

    return status;
}


/*

int main()
{
E_Status_t status = E_NOK;
uint8_t u8_CasesCounter = Initial_Value;

status = TestHorizontalWin_X();
if(status == E_OK)
{
    printf("\n\nTest Case 1 Passed\n");
    printf("==============================\n\n");
    u8_CasesCounter++;
}
else
{
    printf("\n\nTest Case 1 Failed\n");
}

status = TestHorizontalWin_O();
if(status == E_OK)
{
    printf("\n\nTest Case 2 Passed\n");
    printf("==============================\n\n");
    u8_CasesCounter++;
}
else
{
    printf("\n\nTest Case 2 Failed\n");
}

status = TestVerticalWin_O();
if(status == E_OK)
{
    printf("\n\nTest Case 3 Passed\n");
    printf("==============================\n\n");
    u8_CasesCounter++;
}
else
{
    printf("\n\nTest Case 3 Failed\n");
}



status = TestVerticalWin_X();
if(status == E_OK)
{
    printf("\n\nTest Case 4 Passed\n");
    printf("==============================\n\n");
    u8_CasesCounter++;
}
else
{
    printf("\n\nTest Case 4 Failed\n");
}


status = TestRightDiagonalWin_O();
if(status == E_OK)
{
    printf("\n\nTest Case 5 Passed\n");
    printf("==============================\n\n");
    u8_CasesCounter++;
}
else
{
    printf("\n\nTest Case 5 Failed\n");
}


status = TestRightDiagonalWin_X();
if(status == E_OK)
{
    printf("\n\nTest Case 6 Passed\n");
    printf("==============================\n\n");
}
else
{
    printf("\n\nTest Case 6 Failed\n");
}


status = TestLeftDiagonalWin_X();
if(status == E_OK)
{
    printf("\n\nTest Case 7 Passed\n");
    printf("==============================\n\n");
    u8_CasesCounter++;
}
else
{
    printf("\n\nTest Case 7 Failed\n");
}



status = TestLeftDiagonalWin_O();
if(status == E_OK)
{
    printf("\n\nTest Case 8 Passed\n");
    printf("==============================\n\n");
    u8_CasesCounter++;
}
else
{
    printf("\n\nTest Case 8 Failed\n");
}


if(u8_CasesCounter ==7)
{
    printf("\n\nAll Cases passed successfully!\n");
}
else
{
    printf("\n\nNot all cases passed :(");
}

    return E_OK;
}
*/
