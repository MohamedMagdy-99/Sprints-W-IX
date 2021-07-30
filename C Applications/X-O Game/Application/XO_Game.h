/*****************************************************************************
* Module: XO_Game Module
* File Name: XO_Game.h
* Description: Header file for XO_Game Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
#ifndef XO_GAME_H_INCLUDED
#define XO_GAME_H_INCLUDED

/*- INCLUDES -----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "Std_Types.h"
/*- CONSTANTS ----------------------------------------------*/
#define Initial_Value             0
#define Number_Of_Rows            3
#define Number_Of_Columns         3
#define Matrix_Size               9
#define True                      1
#define False                     0
#define Win_Condition             3


#define End_of_Program            100
#define No_Winner                 99

/*- ENUMS --------------------------------------------------*/
typedef enum
{
    E_OK,
    E_NOK
}E_Status_t;
/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct PlayerInfo
{
    uint8_t u8_Player_Id;
    uint8_t au8_Player_Name[20];

}PlayerInfo;

/*- FUNCTION DECLARATIONS ----------------------------------*/
E_Status_t PrintMatrix (void);
E_Status_t InputAssign_X(uint8_t u8_Input);
E_Status_t InputAssign_O(uint8_t u8_Input);
E_Status_t InputPlayerName(void);
E_Status_t ErrorCheck_ValidNumber(uint8_t u8_Input);
E_Status_t ErrorCheck_RepeatedNumber(uint8_t u8_Input);
E_Status_t GetPlayerInputMove (void);
uint8_t HorizontalWinnerCheck(void);
uint8_t VerticalWinnerCheck(void);
uint8_t RightDiagonalWinnerCheck(void);
uint8_t LeftDiagonalWinnerCheck(void);
uint8_t CheckWinner(void);
E_Status_t StartGame(void);
#endif // XO_GAME_H_INCLUDED
