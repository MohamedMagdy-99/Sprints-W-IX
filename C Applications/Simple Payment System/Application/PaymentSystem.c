/*****************************************************************************
* Module: Payment System Module
* File Name: PaymentSystem.c
* Description: Source file for Payment System Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "PaymentSystem.h"
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* card data entered by the user through terminal */
ST_cardData_t st_CardData;

/* data which is already saved in the terminal plus the trans amount by the user */
ST_terminalData_t st_terminalData = {Initial_Value, Max_Amount, Initial_Value};

/* transaction state */
EN_transStat_t EN_transState = DECLINED;

/* error state */
EN_Error_t EN_ErrorState = E_NOK;

/* the trans data collected by terminal and sent to the server */
ST_transactionData_t st_transactionData;

/* server database which has clients accounts information like balance and primary number */
ST_accountBalance_ServerData_t ast_AccountsData_Server[Number_Accounts] =
{
 {10000, "5587128404600545"},
 {5000,  "5587122095504736"},
 {100,   "5184331056065598"},
 {0,     "5182988573731390"},
 {250,   "5183154639544496"},
 {900,   "4377103949108426"},
 {25000, "4377099841444085"},
 {50000, "4377119348742177"},
 {0,     "4377116211090635"},
 {600,   "4377115857311586"}
};


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Transaction Status
* Return value: EN_transStat_t
* Description: check if the card is expired or not
************************************************************************************/

EN_transStat_t ExpiryDateCheck(void)
{

    if(st_CardData.au8_cardExpirtationDate[3]< st_terminalData.au8_transactionDate[6])
    {

        return DECLINED;
    }
    else if(st_CardData.au8_cardExpirtationDate[3] == st_terminalData.au8_transactionDate[6])
    {

        if(st_CardData.au8_cardExpirtationDate[4] < st_terminalData.au8_transactionDate[7])
        {

            return DECLINED;
        }
        else if(st_CardData.au8_cardExpirtationDate[4] == st_terminalData.au8_transactionDate[7])
        {
            if(st_CardData.au8_cardExpirtationDate[0]< st_terminalData.au8_transactionDate[3])
            {

                return DECLINED;
            }
            else if(st_CardData.au8_cardExpirtationDate[0]== st_terminalData.au8_transactionDate[3])
            {
                if(st_CardData.au8_cardExpirtationDate[1]< st_terminalData.au8_transactionDate[4])
                {
                    return DECLINED;
                }
            }
        }
    }
    else
    {
        return APPROVED;
    }

}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Transaction Status
* Return value: EN_transStat_t
* Description: checks if the transaction amount is less than the maximum limit or not
************************************************************************************/
EN_transStat_t TransactionAmountCheck(void)
{
    if(st_terminalData.f_transAmount > st_terminalData.f_maxTranAmount)
    {
        return DECLINED;
    }
    else
    {
        return APPROVED;
    }
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Transaction Status
* Return value: EN_transStat_t
* Description: takes the card's data from the user (name, PAN, expiry date and trans. date)
* and checks for its validity
************************************************************************************/
EN_transStat_t GetUserInput(void)
{
    printf("Please Enter Card Data:\nPlease Enter the Card Holder Name:\n");
    scanf("%s", st_CardData.au8_cardHolderName);

    printf("\nPlease Enter the Primary Account Number\n");
    scanf("%s", st_CardData.au8_primaryAccountNumber);

    printf("\nPlease Enter the Expiry Date MM/YY\n");
    scanf("%s", st_CardData.au8_cardExpirtationDate);

    printf("\nPlease Enter the transaction Amount:\n");
    scanf("%f", &(st_terminalData.f_transAmount));

    if(TransactionAmountCheck() == DECLINED)
    {
        return DECLINED;
    }

    printf("\nPlease Enter the transaction date DD/MM/YY:\n");
    scanf("%s", st_terminalData.au8_transactionDate);

    if(ExpiryDateCheck() == DECLINED)
    {

        return DECLINED;
    }

    return APPROVED;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: EN_Error_t
* Description: sends the transaction data to the server
************************************************************************************/
EN_Error_t SendTransDataToServer(void)
{
    /* card holder data */
           strcpy(st_transactionData.st_cardHolderData.au8_cardExpirtationDate,
                  st_CardData.au8_cardExpirtationDate);

           strcpy(st_transactionData.st_cardHolderData.au8_cardHolderName,
                  st_CardData.au8_cardHolderName);

           strcpy(st_transactionData.st_cardHolderData.au8_primaryAccountNumber,
                  st_CardData.au8_primaryAccountNumber);
    /* terminal data */
           strcpy(st_transactionData.st_transData.au8_transactionDate,
                  st_terminalData.au8_transactionDate);

           st_transactionData.st_transData.f_maxTranAmount = Max_Amount;

           st_transactionData.st_transData.f_transAmount = st_terminalData.f_transAmount;
   /* transaction state */
           st_transactionData.transStat =  EN_transState;

    return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Transaction Status
* Return value: EN_transStat_t
* Description: checks if the card's PAN exists and if it has enough balance or not
************************************************************************************/
EN_transStat_t ServerDataCheck(void)
{
    uint8_t u8_Counter = Initial_Value;
    uint8_t u8_Flag = Initial_Value;

    for(u8_Counter=Initial_Value; u8_Counter < Number_Accounts; u8_Counter++)
    {
        if(strcmp(st_transactionData.st_cardHolderData.au8_primaryAccountNumber,
           ast_AccountsData_Server[u8_Counter].au8_primaryAccountNumber) == 0)
        {
             if(st_transactionData.st_transData.f_transAmount <= ast_AccountsData_Server[u8_Counter].f_balance)
            {
               u8_Flag = Server_Approve;
               break;
            }
        }
    }

    if(u8_Flag == Server_Approve)
    {
        st_transactionData.transStat = APPROVED;
        return APPROVED;
    }
    else
    {
        st_transactionData.transStat = DECLINED;
        return DECLINED;
    }
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: EN_Error_t
* Description: API to start the payment system
************************************************************************************/
EN_Error_t PaymentSystemStart(void)
{
    if(GetUserInput() == DECLINED)
    {
        printf("\nThe Transaction is DECLINED\n");
        return E_NOK;
    }
    else
    {
        EN_transState = APPROVED;
    }
    SendTransDataToServer();

    if(ServerDataCheck()== DECLINED)
    {
        printf("\nThe Transaction is DECLINED\n");
        return E_NOK;
    }

    printf("\nThe Transaction is APPROVED\n");
    return E_OK;
}
