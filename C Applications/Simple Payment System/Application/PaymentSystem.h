/*****************************************************************************
* Module: Payment System Module
* File Name: PaymentSystem.h
* Description: Header file for Payment System Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
#ifndef PAYEMENTSYSTEM_H_INCLUDED
#define PAYEMENTSYSTEM_H_INCLUDED

/*- INCLUDES -----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "Std_Types.h"
/*- CONSTANTS ----------------------------------------------*/
#define Initial_Value   0
#define Max_Amount   5000
#define Number_Accounts   10
#define Server_Approve  100
#define Server_Decline   99

/*- ENUMS --------------------------------------------------*/

/* error state */
typedef enum EN_Error_t
{
    E_OK,
    E_NOK
}EN_Error_t;


/* transaction state */
typedef enum EN_transStat_t
{
    DECLINED,
    APPROVED
}EN_transStat_t;

/*- STRUCTS AND UNIONS -------------------------------------*/

/* card data entered by the user through terminal */
typedef struct ST_cardData_t
{
    uint8_t au8_cardHolderName[25];
    uint8_t au8_primaryAccountNumber[20];
    uint8_t au8_cardExpirtationDate[6];

}ST_cardData_t;

/* data which is already saved in the terminal plus the trans amount by the user */
typedef struct ST_terminalData_t
{
    float f_transAmount;
    float f_maxTranAmount;
    uint8_t au8_transactionDate[11];

}ST_terminalData_t;


/* the trans data collected by terminal and sent to the server */
typedef struct ST_transactionData_t
{
    ST_cardData_t st_cardHolderData;
    ST_terminalData_t st_transData;
    EN_transStat_t transStat;

}ST_transactionData_t;

/* server database which has clients accounts information like balance and primary number */
typedef struct ST_accountBalance_ServerData_t
{
    float f_balance;
    uint8_t au8_primaryAccountNumber[20];

}ST_accountBalance_ServerData_t;


/*- FUNCTION DECLARATIONS ----------------------------------*/
EN_transStat_t ExpiryDateCheck(void);
EN_transStat_t TransactionAmountCheck(void);
EN_transStat_t GetUserInput(void);
EN_Error_t SendTransDataToServer(void);
EN_Error_t PaymentSystemStart(void);
EN_transStat_t ServerDataCheck(void);

#endif // PAYEMENTSYSTEM_H_INCLUDED
