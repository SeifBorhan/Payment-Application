#include "./terminal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include<stdbool.h>
#include <ctype.h>



EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
  char transactionDate[40];
  printf("Please enter the transaction date in the format of DD/MM/YYYY: ");
  fflush(stdin);
  scanf("%[^\n]s\n", transactionDate);
  for(int i=0;i<strlen(transactionDate);i++){ 
    if(i!=2 && i!=5){
    if(isdigit(transactionDate[i])==0){
      return WRONG_DATE;
    }
  }
  }
  if(strlen(transactionDate)==10 && transactionDate[2]=='/' && transactionDate[5]=='/'){
      strcpy((*termData).transactionDate,transactionDate); 
      return TERMINAL_OK;
  }
  return WRONG_DATE;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){

//Case that the Year of Expiry is greater than the year of Transaction.
if((*cardData).cardExpirationDate[4]>(*termData).transactionDate[9]){
    return TERMINAL_OK;
}

//Case that both Years are equal but different decades.
if((*cardData).cardExpirationDate[4]==(*termData).transactionDate[9] && (*cardData).cardExpirationDate[3]>(*termData).transactionDate[8]){
    return TERMINAL_OK;
}

//Case that both years and decades are equal but different months.
if((*cardData).cardExpirationDate[4]==(*termData).transactionDate[9] && (*cardData).cardExpirationDate[3]==(*termData).transactionDate[8] && (*cardData).cardExpirationDate[0]>(*termData).transactionDate[3]){
  return TERMINAL_OK;
}

//Case that both years and decades are equal but different months #2.
if((*cardData).cardExpirationDate[4]==(*termData).transactionDate[9] && (*cardData).cardExpirationDate[3]==(*termData).transactionDate[8] && (*cardData).cardExpirationDate[0]==(*termData).transactionDate[3] && (*cardData).cardExpirationDate[1]>(*termData).transactionDate[4]){
  return TERMINAL_OK;
}
return EXPIRED_CARD;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
  printf("Please enter the amount: ");
  fflush(stdin);
  scanf("%f", &termData->transAmount);
  if(((*termData).transAmount)>0.0){
    return TERMINAL_OK;
  }
  return INVALID_AMOUNT;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
  if((*termData).maxTransAmount>=(*termData).transAmount){
    return TERMINAL_OK;
  }
  return EXCEED_MAX_AMOUNT;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
  if(maxAmount>0.0){
    (*termData).maxTransAmount=maxAmount;
    return TERMINAL_OK;
  }
  return INVALID_MAX_AMOUNT;
}


void getTransactionDateTest(void){
  ST_terminalData_t termData={0,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR =&termData;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: getTransactionDate \n");


  printf("Test Case 1: \n");
  printf("Input Data: 01/02/2021 \n");
  printf("Expected Result: TERMINAL_OK \n");
  switch (getTransactionDate(termDataPTR))
  {
    case WRONG_DATE:
      printf("Actual Result: WRONG_DATE \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }

  printf("Test Case 2: \n");
  printf("Input Data: 1/02/2021 \n");
  printf("Expected Result: WRONG_DATE \n");
  switch (getTransactionDate(termDataPTR))
  {
    case WRONG_DATE:
      printf("Actual Result: WRONG_DATE \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
  
  printf("Test Case 3: \n");
  printf("Input Data: 01/2/2021 \n");
  printf("Expected Result: WRONG_DATE \n");
  switch (getTransactionDate(termDataPTR))
  {
    case WRONG_DATE:
      printf("Actual Result: WRONG_DATE \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }

  printf("Test Case 4: \n");
  printf("Input Data: 01?02?2021 \n");
  printf("Expected Result: WRONG_DATE \n");
  switch (getTransactionDate(termDataPTR))
  {
    case WRONG_DATE:
      printf("Actual Result: WRONG_DATE \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }

  printf("Test Case 5: \n");
  printf("Input Data: 01/02/202 \n");
  printf("Expected Result: WRONG_DATE \n");
  switch (getTransactionDate(termDataPTR))
  {
    case WRONG_DATE:
      printf("Actual Result: WRONG_DATE \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }

  printf("Test Case 6: \n");
  printf("Input Data: \n");
  printf("Expected Result: WRONG_DATE \n");
  switch (getTransactionDate(termDataPTR))
  {
    case WRONG_DATE:
      printf("Actual Result: WRONG_DATE \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
}

void isCardExpriedTest(void){
  ST_terminalData_t termData={0,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR =&termData;

  ST_cardData_t cardData={"","","12/01"};
  ST_cardData_t *cardDataPTR =&cardData;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: isCardExpired \n");


  printf("Test Case 1: \n");
  printf("Input Data: 12/01 & 01/11/2001 \n");
  printf("Expected Result: TERMINAL_OK \n");
  switch (isCardExpired(cardDataPTR,termDataPTR))
  {
    case EXPIRED_CARD:
      printf("Actual Result: EXPIRED_CARD \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }

  ST_terminalData_t termData2={0,0,"01/02/2021"};
  ST_terminalData_t *termDataPTR2 =&termData2;

  ST_cardData_t cardData2={"","","12/20"};
  ST_cardData_t *cardDataPTR2 =&cardData2;

  printf("Test Case 2: \n");
  printf("Input Data: 12/20 & 01/02/2021 \n");
  printf("Expected Result: EXPIRED_CARD \n");
  switch (isCardExpired(cardDataPTR2,termDataPTR2))
  {
    case EXPIRED_CARD:
      printf("Actual Result: EXPIRED_CARD \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }

  ST_terminalData_t termData3={0,0,"01/12/2001"};
  ST_terminalData_t *termDataPTR3 =&termData3;

  ST_cardData_t cardData3={"","","09/01"};
  ST_cardData_t *cardDataPTR3 =&cardData3;
  
  printf("Test Case 3: \n");
  printf("Input Data: 09/01 & 01/12/2001 \n");
  printf("Expected Result: EXPIRED_CARD \n");
  switch (isCardExpired(cardDataPTR3,termDataPTR3))
  {
    case EXPIRED_CARD:
      printf("Actual Result: EXPIRED_CARD \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
}

void getTransactionAmountTest(void){
  ST_terminalData_t termData={0,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR =&termData;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: getTransactionAmountTest \n");


  printf("Test Case 1: \n");
  printf("Input Data: 20 \n");
  printf("Expected Result: TERMINAL_OK \n");
  switch (getTransactionAmount(termDataPTR))
  {
    case INVALID_AMOUNT:
      printf("Actual Result: INVALID_AMOUNT \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }

  printf("Test Case 2: \n");
  printf("Input Data: 0 \n");
  printf("Expected Result: INVALID_AMOUNT \n");
  switch (getTransactionAmount(termDataPTR))
  {
    case INVALID_AMOUNT:
      printf("Actual Result: INVALID_AMOUNT \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
  
  printf("Test Case 3: \n");
  printf("Input Data: -10 \n");
  printf("Expected Result: INVALID_AMOUNT \n");
  switch (getTransactionAmount(termDataPTR))
  {
    case INVALID_AMOUNT:
      printf("Actual Result: INVALID_AMOUNT \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
}

void isBelowMaxAmountTest(void){
ST_terminalData_t termData={20,100,"01/11/2001"};
ST_terminalData_t *termDataPTR =&termData;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: isBelowMaxAmountTest \n");


  printf("Test Case 1: \n");
  printf("Input Data: 20 & Max=100 \n");
  printf("Expected Result: TERMINAL_OK \n");
  switch (isBelowMaxAmount(termDataPTR))
  {
    case EXCEED_MAX_AMOUNT:
      printf("Actual Result: EXCEED_MAX_AMOUNT \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
ST_terminalData_t termData2={100,100,"01/11/2001"};
ST_terminalData_t *termDataPTR2 =&termData2;
  printf("Test Case 2: \n");
  printf("Input Data: 100 & Max=100 \n");
  printf("Expected Result: TERMINAL_OK \n");
  switch (isBelowMaxAmount(termDataPTR2))
  {
    case EXCEED_MAX_AMOUNT:
      printf("Actual Result: EXCEED_MAX_AMOUNT \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
  ST_terminalData_t termData3={1000,100,"01/11/2001"};
ST_terminalData_t *termDataPTR3 =&termData3;
  printf("Test Case 3: \n");
  printf("Input Data: 1000 & Max=100 \n");
  printf("Expected Result: EXCEED_MAX_AMOUNT \n");
  switch (isBelowMaxAmount(termDataPTR3))
  {
    case EXCEED_MAX_AMOUNT:
      printf("Actual Result: EXCEED_MAX_AMOUNT \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
}

void setMaxAmountTest(void){
ST_terminalData_t termData={0,0,"01/11/2001"};
  ST_terminalData_t *termDataPTR =&termData;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: setMaxAmountTest \n");


  printf("Test Case 1: \n");
  printf("Input Data: 20 \n");
  printf("Expected Result: TERMINAL_OK \n");
  switch (setMaxAmount(termDataPTR,20))
  {
    case INVALID_MAX_AMOUNT:
      printf("Actual Result: INVALID_MAX_AMOUNT \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }

  printf("Test Case 2: \n");
  printf("Input Data: 0 \n");
  printf("Expected Result: INVALID_MAX_AMOUNT \n");
  switch (setMaxAmount(termDataPTR,0))
  {
    case INVALID_MAX_AMOUNT:
      printf("Actual Result: INVALID_MAX_AMOUNT \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
  
  printf("Test Case 3: \n");
  printf("Input Data: -10 \n");
  printf("Expected Result: INVALID_MAX_AMOUNT \n");
  switch (setMaxAmount(termDataPTR,-10))
  {
    case INVALID_MAX_AMOUNT:
      printf("Actual Result: INVALID_MAX_AMOUNT \n");break;
    case TERMINAL_OK:
      printf("Actual Result: TERMINAL_OK \n");break;
  }
}


