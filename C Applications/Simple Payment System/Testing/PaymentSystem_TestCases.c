/*****************************************************************************
* Module: Payment System Module
* File Name: PaymentSystem_TestCases.c
* Description: Source file for Payment System Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/

/*************************************************
* Maximum Amount = 5000
*
* Server Saved Data
* =================
* {10000, "5587128404600545"},
* {5000,  "5587122095504736"},
* {100,   "5184331056065598"},
* {0,     "5182988573731390"},
* {250,   "5183154639544496"},
* {900,   "4377103949108426"},
* {25000, "4377099841444085"},
* {50000, "4377119348742177"},
* {0,     "4377116211090635"},
* {600,   "4377115857311586"}
****************************************************/

#include "PaymentSystem.h"
#include "PaymentSystem_TestCases.h"

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: EN_Error_t
* Description: tests the card passes all the conditions
************************************************************************************/
EN_Error_t TestCase1_CorrectData(void)
{
    strcpy(st_CardData.au8_cardHolderName,"Mohamed");
    strcpy(st_CardData.au8_primaryAccountNumber,"5587128404600545");
    strcpy(st_CardData.au8_cardExpirtationDate, "09/21");
    st_terminalData.f_transAmount = 3000;
    strcpy(st_terminalData.au8_transactionDate, "11/07/21");
    SendTransDataToServer();
    if(TransactionAmountCheck()== DECLINED)
    {
        return E_NOK;
    }
    if(ExpiryDateCheck() == DECLINED)
    {
       return E_NOK;
    }
    if(ServerDataCheck() == DECLINED)
    {
        return E_NOK;
    }

    return E_OK;
}


/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: EN_Error_t
* Description: tests if the card is expired or not
************************************************************************************/
EN_Error_t TestCase2_CardExpired(void)
{
    strcpy(st_CardData.au8_cardHolderName,"Mohamed");
    strcpy(st_CardData.au8_primaryAccountNumber,"5587128404600545");
    strcpy(st_CardData.au8_cardExpirtationDate, "09/19");
    st_terminalData.f_transAmount = 5000;
    strcpy(st_terminalData.au8_transactionDate, "11/07/21");
    SendTransDataToServer();

    if(ExpiryDateCheck() == DECLINED)
    {
       return E_OK;
    }


    return E_NOK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: EN_Error_t
* Description: tests if the card has enough balance or not
************************************************************************************/
EN_Error_t TestCase3_NotEnoughBalance(void)
{
    strcpy(st_CardData.au8_cardHolderName,"Mohamed");
    strcpy(st_CardData.au8_primaryAccountNumber,"5184331056065598");
    strcpy(st_CardData.au8_cardExpirtationDate, "09/21");
    st_terminalData.f_transAmount = 500;
    strcpy(st_terminalData.au8_transactionDate, "11/07/21");
    SendTransDataToServer();

    if(ServerDataCheck() == DECLINED)
    {
        return E_OK;
    }

    return E_NOK;
}


/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: EN_Error_t
* Description: tests if the card's exists in the server's database or not
************************************************************************************/
EN_Error_t TestCase4_PAN_NotExist(void)
{
    strcpy(st_CardData.au8_cardHolderName,"Mohamed");
    strcpy(st_CardData.au8_primaryAccountNumber,"5587128404707545");
    strcpy(st_CardData.au8_cardExpirtationDate, "09/21");
    st_terminalData.f_transAmount = 5000;
    strcpy(st_terminalData.au8_transactionDate, "11/07/21");
    SendTransDataToServer();

    if(ServerDataCheck() == DECLINED)
    {
        return E_OK;
    }

    return E_NOK;
}


/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: EN_Error_t
* Description: tests the transaction is exceeding the maximum allowed amount or not
************************************************************************************/
EN_Error_t TestCase5_MaxTransAmount(void)
{
    strcpy(st_CardData.au8_cardHolderName,"Mohamed");
    strcpy(st_CardData.au8_primaryAccountNumber,"5587128404600545");
    strcpy(st_CardData.au8_cardExpirtationDate, "09/21");
    st_terminalData.f_transAmount = 10000;
    strcpy(st_terminalData.au8_transactionDate, "11/07/21");
    SendTransDataToServer();

    if(TransactionAmountCheck()== DECLINED)
    {
        return E_OK;
    }


    return E_NOK;
}
/*

int main()
{
    if(TestCase1_CorrectData() == E_NOK)
    {
        printf("\nTest Case 1 Failed\n\n");
    }
    else
    {
        printf("\nTest Case 1 Passed\n\n");
    }

    if(TestCase2_CardExpired() == E_NOK)
    {
        printf("\nTest Case 2 Failed\n\n");
    }
    else
    {
        printf("\nTest Case 2 Passed\n\n");
    }

    if(TestCase3_NotEnoughBalance() == E_NOK)
    {
        printf("\nTest Case 3 Failed\n\n");
    }
    else
    {
        printf("\nTest Case 3 Passed\n\n");
    }

    if(TestCase4_PAN_NotExist() == E_NOK)
    {
        printf("\nTest Case 4 Failed\n\n");
    }
    else
    {
        printf("\nTest Case 4 Passed\n\n");
    }

    if(TestCase5_MaxTransAmount() == E_NOK)
    {
        printf("\nTest Case 5 Failed\n\n");
    }
    else
    {
        printf("\nTest Case 5 Passed\n\n");
    }

    return 0;
}

*/
