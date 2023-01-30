#include "./server.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


ST_accountsDB_t accountsDB[255] = {{2000,RUNNING,"9274563281928470917"},{10000,RUNNING,"53726536234234672"},{50,RUNNING,"1029384726453283746"},{11000,RUNNING,"231428492736152734"},{123142,BLOCKED,"8172630472627182926"}};

ST_transaction_t transactionsDB[255] = {0};

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
  ST_accountsDB_t account;
  ST_accountsDB_t *accountReference= &account;

  if(isValidAccount((&transData->cardHolderData),accountReference)==ACCOUNT_NOT_FOUND){
    return FRAUD_CARD;
  }
  if(isAmountAvailable((&transData->terminalData),accountReference)==LOW_BALANCE){
    return DECLINED_INSUFFECIENT_FUND;
  }
  if(isBlockedAccount(accountReference)){
    return DECLINED_STOLEN_CARD;
  }
  if(saveTransaction(transData)==SAVING_FAILED){
    return INTERNAL_SERVER_ERROR;
  }
  account.balance-=transData->terminalData.transAmount;
  return APPROVED;

}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
  for(int i=0;i<255;i++){
    if(!strcmp((*cardData).primaryAccountNumber,accountsDB[i].primaryAccountNumber)){
      *accountRefrence=accountsDB[i];
      return SERVER_OK;
    }
  }
  return ACCOUNT_NOT_FOUND;

}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
  if((*accountRefrence).state==BLOCKED){
    return BLOCKED_ACCOUNT;
  }
  return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){
  if((*termData).transAmount<=(*accountRefrence).balance){
    return SERVER_OK;
  }
  return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    if(transactionsDB[0].transactionSequenceNumber==0){
      transactionsDB[0].cardHolderData=(*transData).cardHolderData;
      transactionsDB[0].terminalData=(*transData).terminalData;
      transactionsDB[0].transState=(*transData).transState;
      transactionsDB[0].transactionSequenceNumber=1;
      return SERVER_OK;
    }
    int i;
    for(i=0;i<255;i++){
      if(transactionsDB[i].transactionSequenceNumber==0){
        break;
      }
    }
      transactionsDB[i].cardHolderData=(*transData).cardHolderData;
      transactionsDB[i].terminalData=(*transData).terminalData;
      transactionsDB[i].transState=(*transData).transState;
      transactionsDB[i].transactionSequenceNumber=transactionsDB[i-1].transactionSequenceNumber+1;
      return SERVER_OK;
}

void listSavedTransactions(void){
  for(int i=0;i<255;i++){
  if(transactionsDB[i].transactionSequenceNumber==0){
    break;
  }
  printf("################### \n");
  printf("Transaction Sequence Number: %u \n",transactionsDB[i].transactionSequenceNumber); 
  printf("Transaction Amount: %f \n",transactionsDB[i].terminalData.transAmount);
  printf("Transaction State: %s \n",getState(transactionsDB[i].transState));
  printf("Terminal Max Amount: %f \n",transactionsDB[i].terminalData.maxTransAmount);
  printf("Cardholder Name: %s \n",transactionsDB[i].cardHolderData.cardHolderName);
  printf("PAN: %s \n",transactionsDB[i].cardHolderData.primaryAccountNumber);
  printf("Card Expiration Date: %s \n",transactionsDB[i].cardHolderData.cardExpirationDate);
  printf("################### \n");
  }
}

const char* getState(enum EN_transState_t state) 
{
   switch (state) 
   {
      case APPROVED: return "Approved";break;
      case DECLINED_INSUFFECIENT_FUND: return "DECLINED_INSUFFECIENT_FUND";break;
      case DECLINED_STOLEN_CARD: return "DECLINED_STOLEN_CARD";break;
      case FRAUD_CARD: return "FRAUD_CARD";break;
      case INTERNAL_SERVER_ERROR: return "INTERNAL_SERVER_ERROR";break;
   }
}

void recieveTransactionDataTest(void){
  ST_cardData_t cardData={"","9274563281928470917",""};
  ST_cardData_t *cardDataPTR =&cardData;

  ST_terminalData_t termData={10,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR =&termData;

  ST_transaction_t tr={cardData,termData,APPROVED,0};
  ST_transaction_t *tra=&tr;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: recieveTransactionDataTest \n");

  printf("Test Case 1: \n");
  printf("Input Data: Valid Account \n");
  printf("Expected Result: APPROVED \n");
  switch (recieveTransactionData(tra))
  {
  case FRAUD_CARD:
  printf("Actual Result: FRAUD_CARD \n");break;
  case DECLINED_INSUFFECIENT_FUND:
  printf("Actual Result: DECLINED_INSUFFECIENT_FUND \n");break;
  case DECLINED_STOLEN_CARD:
  printf("Actual Result: DECLINED_STOLEN_CARD \n");break;
  case INTERNAL_SERVER_ERROR:
  printf("Actual Result: INTERNAL_SERVER_ERROR \n");break;
  case APPROVED:
  printf("Actual Result: APPROVED \n");break;
  }
  ST_cardData_t cardData1={"","927456328192847097",""};
  ST_cardData_t *cardDataPTR1 =&cardData1;

  ST_terminalData_t termData1={10,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR1 =&termData1;

  ST_transaction_t tr1={cardData1,termData1,APPROVED,0};
  ST_transaction_t *tra1=&tr1;

  printf("Test Case 2: \n");
  printf("Input Data: Invalid PAN \n");
  printf("Expected Result: FRAUD_CARD \n");
  switch (recieveTransactionData(tra1))
  {
  case FRAUD_CARD:
  printf("Actual Result: FRAUD_CARD \n");break;
  case DECLINED_INSUFFECIENT_FUND:
  printf("Actual Result: DECLINED_INSUFFECIENT_FUND \n");break;
  case DECLINED_STOLEN_CARD:
  printf("Actual Result: DECLINED_STOLEN_CARD \n");break;
  case INTERNAL_SERVER_ERROR:
  printf("Actual Result: INTERNAL_SERVER_ERROR \n");break;
  case APPROVED:
  printf("Actual Result: APPROVED \n");break;
  }
  ST_cardData_t cardData2={"","9274563281928470917",""};
  ST_cardData_t *cardDataPTR2 =&cardData2;

  ST_terminalData_t termData2={100000,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR2 =&termData2;

  ST_transaction_t tr2={cardData2,termData2,APPROVED,0};
  ST_transaction_t *tra2=&tr2;

  printf("Test Case 3: \n");
  printf("Input Data: Amount is below funds \n");
  printf("Expected Result: DECLINED_INSUFFECIENT_FUND \n");
  switch (recieveTransactionData(tra2))
  {
  case FRAUD_CARD:
  printf("Actual Result: FRAUD_CARD \n");break;
  case DECLINED_INSUFFECIENT_FUND:
  printf("Actual Result: DECLINED_INSUFFECIENT_FUND \n");break;
  case DECLINED_STOLEN_CARD:
  printf("Actual Result: DECLINED_STOLEN_CARD \n");break;
  case INTERNAL_SERVER_ERROR:
  printf("Actual Result: INTERNAL_SERVER_ERROR \n");break;
  case APPROVED:
  printf("Actual Result: APPROVED \n");break;
  }

  ST_cardData_t cardData3={"","8172630472627182926",""};
  ST_cardData_t *cardDataPTR3 =&cardData3;

  ST_terminalData_t termData3={1000,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR3 =&termData3;

  ST_transaction_t tr3={cardData3,termData3,APPROVED,0};
  ST_transaction_t *tra3=&tr3;

  printf("Test Case 4: \n");
  printf("Input Data: Blocked Account \n");
  printf("Expected Result: DECLINED_STOLEN_CARD \n");
  switch (recieveTransactionData(tra3))
  {
  case FRAUD_CARD:
  printf("Actual Result: FRAUD_CARD \n");break;
  case DECLINED_INSUFFECIENT_FUND:
  printf("Actual Result: DECLINED_INSUFFECIENT_FUND \n");break;
  case DECLINED_STOLEN_CARD:
  printf("Actual Result: DECLINED_STOLEN_CARD \n");break;
  case INTERNAL_SERVER_ERROR:
  printf("Actual Result: INTERNAL_SERVER_ERROR \n");break;
  case APPROVED:
  printf("Actual Result: APPROVED \n");break;
  }

}

void isValidAccountTest(void){
  ST_cardData_t cardData={"","1029384726453283746",""};
  ST_cardData_t *cardDataPTR =&cardData;

  ST_accountsDB_t account;
  ST_accountsDB_t *accountReference= &account;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: isValidAccount \n");

  printf("Test Case 1: \n");
  printf("Input Data: 1029384726453283746 \n");
  printf("Expected Result: SERVER_OK \n");
  switch (isValidAccount(cardDataPTR,accountReference))
  {
  case SERVER_OK:
  printf("Actual Result: SERVER_OK \n");break;
  case ACCOUNT_NOT_FOUND:
  printf("Actual Result: ACCOUNT_NOT_FOUND \n");break;
  }
  ST_cardData_t cardData1={"","10293847264532836",""};
  ST_cardData_t *cardDataPTR1 =&cardData1;

  ST_accountsDB_t account1;
  ST_accountsDB_t *accountReference1= &account1;

 
  printf("Test Case 2: \n");
  printf("Input Data: 10293847264532836 \n");
  printf("Expected Result: ACCOUNT_NOT_FOUND \n");
  switch (isValidAccount(cardDataPTR1,accountReference1))
  {
  case SERVER_OK:
  printf("Actual Result: SERVER_OK \n");break;
  case ACCOUNT_NOT_FOUND:
  printf("Actual Result: ACCOUNT_NOT_FOUND \n");break;
  }
}

void isBlockedAccountTest(void){
  ST_accountsDB_t account=accountsDB[0];
  ST_accountsDB_t *accountReference= &account;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: isBlockedAccount \n");

  printf("Test Case 1: \n");
  printf("Input Data: RUNNING Account \n");
  printf("Expected Result: SERVER_OK \n");
  switch (isBlockedAccount(accountReference))
  {
  case SERVER_OK:
  printf("Actual Result: SERVER_OK \n");break;
  case BLOCKED_ACCOUNT:
  printf("Actual Result: BLOCKED_ACCOUNT \n");break;
  }

  ST_accountsDB_t account1=accountsDB[4];
  ST_accountsDB_t *accountReference1= &account1;

  printf("Test Case 2: \n");
  printf("Input Data: BLOCKED Account \n");
  printf("Expected Result: BLOCKED_ACCOUNT \n");
  switch (isBlockedAccount(accountReference1))
  {
  case SERVER_OK:
  printf("Actual Result: SERVER_OK \n");break;
  case BLOCKED_ACCOUNT:
  printf("Actual Result: BLOCKED_ACCOUNT \n");break;
  }
}

void isAmountAvailableTest(void){
  ST_accountsDB_t account=accountsDB[0];
  ST_accountsDB_t *accountReference= &account;

  ST_terminalData_t termData={10,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR =&termData;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: isAmountAvailable \n");

  printf("Test Case 1: \n");
  printf("Input Data: Available Amount \n");
  printf("Expected Result: SERVER_OK \n");
  switch (isAmountAvailable(termDataPTR,accountReference))
  {
  case SERVER_OK:
  printf("Actual Result: SERVER_OK \n");break;
  case LOW_BALANCE:
  printf("Actual Result: LOW_BALANCE \n");break;
  }

  ST_accountsDB_t account1=accountsDB[0];
  ST_accountsDB_t *accountReference1= &account1;

  ST_terminalData_t termData1={10000,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR1 =&termData1;

  printf("Test Case 2: \n");
  printf("Input Data: Amount not available \n");
  printf("Expected Result: LOW_BALANCE \n");
  switch (isAmountAvailable(termDataPTR1,accountReference1))
  {
  case SERVER_OK:
  printf("Actual Result: SERVER_OK \n");break;
  case LOW_BALANCE:
  printf("Actual Result: LOW_BALANCE \n");break;
  }
}

void saveTransactionTest(void){
  ST_cardData_t cardData={"","9274563281928470917",""};
  ST_cardData_t *cardDataPTR =&cardData;

  ST_terminalData_t termData={10,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR =&termData;

  ST_transaction_t tr={cardData,termData,APPROVED,0};
  ST_transaction_t *tra=&tr;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: saveTransaction \n");

  printf("Test Case 1: \n");
  printf("Input Data: \n");
  printf("Expected Result: SERVER_OK \n");
  switch (saveTransaction(tra))
  {
  case SERVER_OK:
  printf("Actual Result: SERVER_OK \n");break;
  case INTERNAL_SERVER_ERROR:
  printf("Actual Result: INTERNAL_SERVER_ERROR \n");break;
  }
  ST_cardData_t cardData1={"","9274563281928470917",""};
  ST_cardData_t *cardDataPTR1 =&cardData1;

  ST_terminalData_t termData1={10,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR1 =&termData1;

  ST_transaction_t tr1={cardData1,termData1,DECLINED_INSUFFECIENT_FUND,0};
  ST_transaction_t *tra1=&tr1;

 
  printf("Test Case 2: \n");
  printf("Input Data: \n");
  printf("Expected Result: SERVER_OK \n");
  switch (saveTransaction(tra1))
  {
  case SERVER_OK:
  printf("Actual Result: SERVER_OK \n");break;
  case INTERNAL_SERVER_ERROR:
  printf("Actual Result: INTERNAL_SERVER_ERROR \n");break;
  }
}

 