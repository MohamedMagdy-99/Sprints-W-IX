/*****************************************************************************
* Module: Payment System Module
* File Name: PaymentSystem_TestCases.h
* Description: Header file for Payment System Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
#ifndef PAYMENTSYSTEM_TESTCASES_H_INCLUDED
#define PAYMENTSYSTEM_TESTCASES_H_INCLUDED

extern ST_cardData_t st_CardData;
extern ST_terminalData_t st_terminalData;
extern EN_transStat_t EN_transState ;

extern ST_transactionData_t st_transactionData;

extern ST_accountBalance_ServerData_t ast_AccountsData_Server[Number_Accounts];

extern EN_Error_t EN_ErrorState ;


EN_Error_t TestCase1_CorrectData(void);
EN_Error_t TestCase2_CardExpired(void);
EN_Error_t TestCase3_NotEnoughBalance(void);
EN_Error_t TestCase4_PAN_NotExist(void);
EN_Error_t TestCase5_MaxTransAmount(void);

#endif // PAYMENTSYSTEM_TESTCASES_H_INCLUDED
