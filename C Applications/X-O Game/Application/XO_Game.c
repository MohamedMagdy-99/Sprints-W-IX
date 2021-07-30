/*****************************************************************************
* Module: XO_Game Module
* File Name: XO_Game.c
* Description: Source file for XO_Game Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "XO_Game.h"


/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* array which represents the grid */
uint8_t gau8_CharactersToBeDisplayedOnMatrix[Number_Of_Rows][Number_Of_Columns]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
/* enum for error status */
E_Status_t E_Status = E_NOK;
/* structure that holds player data */
PlayerInfo Player[2];
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: prints the grid matrix
************************************************************************************/
E_Status_t PrintMatrix (void)
{
    uint8_t u8_Rows = Initial_Value;
    uint8_t u8_Columns = Initial_Value;

    printf("\n* * * * * * * * * *\n");
    for (u8_Rows=0; u8_Rows<Number_Of_Rows; u8_Rows++)
    {
        for(u8_Columns=0; u8_Columns<Number_Of_Columns; u8_Columns++)
        {
            printf("*  %c  ", gau8_CharactersToBeDisplayedOnMatrix[u8_Rows][u8_Columns]);
        }
        printf("*\n* * * * * * * * * *\n");

    }
    return E_OK;
}

/************************************************************************************
* Parameters (in): Player Input To Play
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: takes the input number the player 'X' wants to play
* and assign it to the grid matrix
************************************************************************************/
E_Status_t InputAssign_X(uint8_t u8_Input)
{
    switch(u8_Input)
    {
    case 1:
        gau8_CharactersToBeDisplayedOnMatrix[0][0] = 'X';
        break;
    case 2:
        gau8_CharactersToBeDisplayedOnMatrix[0][1] = 'X';
        break;
    case 3:
        gau8_CharactersToBeDisplayedOnMatrix[0][2] = 'X';
        break;
    case 4:
        gau8_CharactersToBeDisplayedOnMatrix[1][0] = 'X';
        break;
    case 5:
        gau8_CharactersToBeDisplayedOnMatrix[1][1] = 'X';
        break;
    case 6:
        gau8_CharactersToBeDisplayedOnMatrix[1][2] = 'X';
        break;
    case 7:
        gau8_CharactersToBeDisplayedOnMatrix[2][0] = 'X';
        break;
    case 8:
        gau8_CharactersToBeDisplayedOnMatrix[2][1] = 'X';
        break;
    case 9:
        gau8_CharactersToBeDisplayedOnMatrix[2][2] = 'X';
        break;
    default:
        break;

    }
    return E_OK;
}

/************************************************************************************
* Parameters (in): Player Input To Play
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: takes the input number the player 'O' wants to play
* and assign is to the grid matrix
************************************************************************************/
E_Status_t InputAssign_O(uint8_t u8_Input)
{
    switch(u8_Input)
    {
    case 1:
        gau8_CharactersToBeDisplayedOnMatrix[0][0] = 'O';
        break;
    case 2:
        gau8_CharactersToBeDisplayedOnMatrix[0][1] = 'O';
        break;
    case 3:
        gau8_CharactersToBeDisplayedOnMatrix[0][2] = 'O';
        break;
    case 4:
        gau8_CharactersToBeDisplayedOnMatrix[1][0] = 'O';
        break;
    case 5:
        gau8_CharactersToBeDisplayedOnMatrix[1][1] = 'O';
        break;
    case 6:
        gau8_CharactersToBeDisplayedOnMatrix[1][2] = 'O';
        break;
    case 7:
        gau8_CharactersToBeDisplayedOnMatrix[2][0] = 'O';
        break;
    case 8:
        gau8_CharactersToBeDisplayedOnMatrix[2][1] = 'O';
        break;
    case 9:
        gau8_CharactersToBeDisplayedOnMatrix[2][2] = 'O';
        break;
    default:
        break;

    }
    return E_OK;
}

/************************************************************************************
* Parameters (in): Player's Name
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: takes the players' names
************************************************************************************/
E_Status_t InputPlayerName()
{
    printf("Please Enter First Player Name:\n");
    scanf(" %s", &Player[0].au8_Player_Name);
    Player[0].u8_Player_Id = 'X';


    printf("\nPlease Enter Second Player Name:\n");
    scanf(" %s", &Player[1].au8_Player_Name);
    Player[1].u8_Player_Id = 'O';

    printf("\n%s will be X\n%s will be O\n\n%s will start playing\n\n", Player[0].au8_Player_Name, Player[1].au8_Player_Name, Player[0].au8_Player_Name);

    return E_OK;
}

/************************************************************************************
* Parameters (in): Player Input To Play
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: checks if the input number the player wants to play is valid
* (range from 1 to 9)
************************************************************************************/
E_Status_t ErrorCheck_ValidNumber(uint8_t u8_Input)
{
    if(u8_Input <= 0 || u8_Input >=10) return E_NOK;
    else return E_OK;
}

/************************************************************************************
* Parameters (in): Player Input To Play
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: checks if the input number the player wants to play was entered
* before or not (repeated)
************************************************************************************/
E_Status_t ErrorCheck_RepeatedNumber(uint8_t u8_Input)
{
    switch(u8_Input)
    {
    case 1:
        if(gau8_CharactersToBeDisplayedOnMatrix[0][0] == 'X' || gau8_CharactersToBeDisplayedOnMatrix[0][0] == 'O') return E_NOK;
        break;
    case 2:
        if(gau8_CharactersToBeDisplayedOnMatrix[0][1] == 'X' || gau8_CharactersToBeDisplayedOnMatrix[0][1] == 'O') return E_NOK;
        break;
    case 3:
        if(gau8_CharactersToBeDisplayedOnMatrix[0][2] == 'X' || gau8_CharactersToBeDisplayedOnMatrix[0][2] == 'O') return E_NOK;
        break;
    case 4:
        if(gau8_CharactersToBeDisplayedOnMatrix[1][0] == 'X' || gau8_CharactersToBeDisplayedOnMatrix[1][0] == 'O') return E_NOK;
        break;
    case 5:
        if(gau8_CharactersToBeDisplayedOnMatrix[1][1] == 'X' || gau8_CharactersToBeDisplayedOnMatrix[1][1] == 'O') return E_NOK;
        break;
    case 6:
        if(gau8_CharactersToBeDisplayedOnMatrix[1][2] == 'X' || gau8_CharactersToBeDisplayedOnMatrix[1][2] == 'O') return E_NOK;
        break;
    case 7:
        if(gau8_CharactersToBeDisplayedOnMatrix[2][0] == 'X' || gau8_CharactersToBeDisplayedOnMatrix[2][0] == 'O') return E_NOK;
        break;
    case 8:
        if(gau8_CharactersToBeDisplayedOnMatrix[2][1] == 'X' || gau8_CharactersToBeDisplayedOnMatrix[2][1] == 'O') return E_NOK;
        break;
    case 9:
        if(gau8_CharactersToBeDisplayedOnMatrix[2][2] == 'X' || gau8_CharactersToBeDisplayedOnMatrix[2][2] == 'O') return E_NOK;
        break;
    default:
        break;

    }
    return E_OK;
}

/************************************************************************************
* Parameters (in): Player Input To Play
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: takes the input number the player wants to play
* and assign is to the grid matrix
************************************************************************************/
E_Status_t GetPlayerInputMove (void)
{
    uint8_t u8_Input = Initial_Value;

    static uint8_t u8_PlayerTurn = Initial_Value;

        PrintMatrix();

        if(u8_PlayerTurn == Initial_Value)
        {
            while(True)
            {
                printf("\n%s 'X', write the place number you want to play\n", Player[0].au8_Player_Name);
                scanf(" %d", &u8_Input);

                if(ErrorCheck_ValidNumber(u8_Input)==E_NOK)
                {
                    printf("\n\nThe number you entered is out of range, please enter a number from 1 to 9\n\n");
                }
                else if(ErrorCheck_RepeatedNumber(u8_Input)== E_NOK)
                {
                    printf("\n\nThe number you entered is repeated, please enter a number from the grid\n\n");
                }
                else break;
            }
                InputAssign_X(u8_Input);
                ++u8_PlayerTurn;
        }
        else if(u8_PlayerTurn == Initial_Value+1)
        {
            while(True)
            {
                printf("\n%s 'O', write the place number you want to play\n", Player[1].au8_Player_Name);
                scanf(" %d", &u8_Input);

                if(ErrorCheck_ValidNumber(u8_Input)==E_NOK)
                {
                    printf("\n\nThe number you entered is out of range, please enter a number from 1 to 9\n\n");
                }
                else if(ErrorCheck_RepeatedNumber(u8_Input)== E_NOK)
                {
                    printf("\n\nThe number you entered is repeated, please enter a number from the grid\n\n");
                }
                else break;
            }
                InputAssign_O(u8_Input);
                --u8_PlayerTurn;

        }
    return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Win Status
* Return value: uint8_t
* Description: checks if the current grid matrix has a horizontal win condition or not
************************************************************************************/
uint8_t HorizontalWinnerCheck(void)
{
    uint8_t u8_Rows = Initial_Value;
    uint8_t u8_Columns = Initial_Value;
    uint8_t u8_X_Counter, u8_Y_Counter = Initial_Value;

    for (u8_Rows=0; u8_Rows<Number_Of_Rows; u8_Rows++)
    {
        for(u8_Columns=0; u8_Columns<Number_Of_Columns; u8_Columns++)
        {
            if(gau8_CharactersToBeDisplayedOnMatrix[u8_Rows][u8_Columns] == 'X')
            {
                u8_X_Counter++;
            }
            else if(gau8_CharactersToBeDisplayedOnMatrix[u8_Rows][u8_Columns] == 'O')
            {
                u8_Y_Counter++;

            }
            if (u8_X_Counter == Win_Condition || u8_Y_Counter == Win_Condition)
            {

                 return u8_X_Counter > u8_Y_Counter ? 'X':'O';
            }
        }
        u8_X_Counter = Initial_Value;
        u8_Y_Counter = Initial_Value;
    }
    return No_Winner;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Win Status
* Return value: uint8_t
* Description: checks if the current grid matrix has a vertical win condition or not
************************************************************************************/
uint8_t VerticalWinnerCheck(void)
{
    uint8_t u8_Rows = Initial_Value;
    uint8_t u8_Columns = Initial_Value;
    uint8_t u8_X_Counter, u8_Y_Counter = Initial_Value;

    for (u8_Rows=0; u8_Rows<Number_Of_Rows; u8_Rows++)
    {
        for(u8_Columns=0; u8_Columns<Number_Of_Columns; u8_Columns++)
        {
            if(gau8_CharactersToBeDisplayedOnMatrix[u8_Columns][u8_Rows] == 'X')
            {
                u8_X_Counter++;
            }
            else if(gau8_CharactersToBeDisplayedOnMatrix[u8_Columns][u8_Rows] == 'O')
            {
                u8_Y_Counter++;
            }
            if (u8_X_Counter == Win_Condition || u8_Y_Counter == Win_Condition)
            {

                 return u8_X_Counter > u8_Y_Counter ? 'X':'O';
            }
        }
        u8_X_Counter = Initial_Value;
        u8_Y_Counter = Initial_Value;
    }
    return No_Winner;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Win Status
* Return value: uint8_t
* Description: checks if the current grid matrix has a right diagonal win condition or not
************************************************************************************/
uint8_t RightDiagonalWinnerCheck(void)
{
    if(gau8_CharactersToBeDisplayedOnMatrix[0][0] == 'X' && gau8_CharactersToBeDisplayedOnMatrix[1][1] == 'X' && gau8_CharactersToBeDisplayedOnMatrix[2][2] == 'X') return 'X';
    else if(gau8_CharactersToBeDisplayedOnMatrix[0][0] == 'O' && gau8_CharactersToBeDisplayedOnMatrix[1][1] == 'O' && gau8_CharactersToBeDisplayedOnMatrix[2][2] == 'O') return 'O';
    else return No_Winner;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Win Status
* Return value: uint8_t
* Description: checks if the current grid matrix has a left diagonal win condition or not
************************************************************************************/
uint8_t LeftDiagonalWinnerCheck(void)
{
    if(gau8_CharactersToBeDisplayedOnMatrix[0][2] == 'X' && gau8_CharactersToBeDisplayedOnMatrix[1][1] == 'X' && gau8_CharactersToBeDisplayedOnMatrix[2][0] == 'X') return 'X';
    else if(gau8_CharactersToBeDisplayedOnMatrix[0][2] == 'O' && gau8_CharactersToBeDisplayedOnMatrix[1][1] == 'O' && gau8_CharactersToBeDisplayedOnMatrix[2][0] == 'O') return 'O';
    else return No_Winner;
}


/************************************************************************************
* Parameters (in): None
* Parameters (out): Win Status
* Return value: uint8_t
* Description: checks if any of player 'X' or 'Y' has a win condition or not
************************************************************************************/
uint8_t CheckWinner(void)
{
    static uint8_t u8_FunctionCounter = Initial_Value;

    if(HorizontalWinnerCheck() == 'X')
    {
        PrintMatrix();
        printf("\nCongratulations, %s you won!",Player[0].au8_Player_Name);
        return End_of_Program;
    }
    else if(HorizontalWinnerCheck() == 'O')
    {
       PrintMatrix();
       printf("\nCongratulations, %s you won!",Player[1].au8_Player_Name);
       return End_of_Program;
    }

    if(VerticalWinnerCheck() == 'X')
    {
        PrintMatrix();
        printf("\nCongratulations, %s you won!",Player[0].au8_Player_Name);
        return End_of_Program;
    }
    else if(VerticalWinnerCheck() == 'O')
    {
       PrintMatrix();
       printf("\nCongratulations, %s you won!",Player[1].au8_Player_Name);
       return End_of_Program;
    }

    if(RightDiagonalWinnerCheck() == 'X')
    {
        PrintMatrix();
        printf("\nCongratulations, %s you won!",Player[0].au8_Player_Name);
        return End_of_Program;
    }
    else if(RightDiagonalWinnerCheck() == 'O')
    {
       PrintMatrix();
       printf("\nCongratulations, %s you won!",Player[1].au8_Player_Name);
       return End_of_Program;
    }

    if(LeftDiagonalWinnerCheck() == 'X')
    {
        PrintMatrix();
        printf("\nCongratulations, %s you won!",Player[0].au8_Player_Name);
        return End_of_Program;
    }
    else if(LeftDiagonalWinnerCheck() == 'O')
    {
       PrintMatrix();
       printf("\nCongratulations, %s you won!",Player[1].au8_Player_Name);
       return End_of_Program;
    }

    u8_FunctionCounter++;

    if(u8_FunctionCounter == 9)
    {
        PrintMatrix();
        printf("\nThat's a draw, no one won\n");
        return End_of_Program;
    }
    else return No_Winner;
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: E_Status_t
* Description: API that starts the game
************************************************************************************/
E_Status_t StartGame (void)
{
    InputPlayerName();
    while(True)
    {
       GetPlayerInputMove();
       if(CheckWinner()== End_of_Program) return E_OK;
    }

}
