#include "./card.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
  char holderName[40]; 
  printf("Please enter the name presented on the card: ");
  fflush(stdin); //Flushes the input buffer.
  scanf("%[^\n]s\n",  holderName); 
  for(int i=0;i<strlen(holderName);i++){ //Checks if the input is based entirely on alphabets.
    if(isalpha(holderName[i])==0 && isspace(holderName[i])==0){
      return WRONG_NAME;
    }
  }
  if(strlen(holderName)>=20 && strlen(holderName)<=24){ 
    strcpy((*cardData).cardHolderName,holderName); 
    return CARD_OK;
  }
  return WRONG_NAME;
}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
  char expiryDate[40]; 
  printf("Please enter the expiry date presented on the card in the format of MM/YY: ");
  fflush(stdin); //Flushes the input buffer.
  scanf("%[^\n]s\n", expiryDate); 
  for(int i=0;i<strlen(expiryDate);i++){ //Checks if the input is based entirely on digits and /.
    if(i!=2){
    if(isdigit(expiryDate[i])==0){
      return WRONG_EXP_DATE;
    }
  }
  }
  if(strlen(expiryDate)==5 && expiryDate[2]=='/'){ 
      strcpy((*cardData).cardExpirationDate,expiryDate); 
      return CARD_OK;
  }
  return WRONG_EXP_DATE;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
  char pan[40]; 
  printf("Please enter the Primary Account Number (PAN) presented on the card: ");
  fflush(stdin); //Flushes the input buffer.
  scanf("%[^\n]s\n", pan); 
  for(int i=0;i<strlen(pan);i++){ //Checks if the input is based entirely on digits.
    if(isdigit(pan[i])==0){
      return WRONG_PAN;
    }

  }
  if(strlen(pan)<=19 && strlen(pan)>=16){
  strcpy((*cardData).primaryAccountNumber,pan);
  return CARD_OK; 
  }
  return WRONG_PAN;
}

void getCardHolderNameTest(void){
  ST_cardData_t test={"","",""};
  ST_cardData_t *testPTR=&test;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: getCardHolderName \n");


  printf("Test Case 1: \n");
  printf("Input Data: Seif BorhanEldin Safwat \n");
  printf("Expected Result: CARD_OK \n");
  switch (getCardHolderName(testPTR))
  {
    case WRONG_NAME:
      printf("Actual Result: WRONG_NAME \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 2: \n");
  printf("Input Data: Seif Borhan1ldin Safwat \n");
  printf("Expected Result: WRONG_NAME \n");
  switch (getCardHolderName(testPTR))
  {
    case WRONG_NAME:
      printf("Actual Result: WRONG_NAME \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }
  
  printf("Test Case 3: \n");
  printf("Input Data: Seif BorhanEldin \n");
  printf("Expected Result: WRONG_NAME \n");
  switch (getCardHolderName(testPTR))
  {
    case WRONG_NAME:
      printf("Actual Result: WRONG_NAME \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 4: \n");
  printf("Input Data: Seif BorhanEldin Safwat Khattab \n");
  printf("Expected Result: WRONG_NAME \n");
  switch (getCardHolderName(testPTR))
  {
    case WRONG_NAME:
      printf("Actual Result: WRONG_NAME \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 5: \n");
  printf("Input Data: \n");
  printf("Expected Result: WRONG_NAME \n");
  switch (getCardHolderName(testPTR))
  {
    case WRONG_NAME:
      printf("Actual Result: WRONG_NAME \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

}

void getCardExpiryDateTest (void){
  ST_cardData_t test={"","",""};
  ST_cardData_t *testPTR=&test;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: getCardExpiryDate \n");


  printf("Test Case 1: \n");
  printf("Input Data: 02/12 \n");
  printf("Expected Result: CARD_OK \n");
  switch (getCardExpiryDate(testPTR))
  {
    case WRONG_EXP_DATE:
      printf("Actual Result: WRONG_EXP_DATE \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 2: \n");
  printf("Input Data: 3/12 \n");
  printf("Expected Result: WRONG_EXP_DATE \n");
  switch (getCardExpiryDate(testPTR))
  {
    case WRONG_EXP_DATE:
      printf("Actual Result: WRONG_EXP_DATE \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }
  
  printf("Test Case 3: \n");
  printf("Input Data: 03/1 \n");
  printf("Expected Result: WRONG_EXP_DATE \n");
  switch (getCardExpiryDate(testPTR))
  {
    case WRONG_EXP_DATE:
      printf("Actual Result: WRONG_EXP_DATE \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 4: \n");
  printf("Input Data: ab/12 \n");
  printf("Expected Result: WRONG_EXP_DATE \n");
  switch (getCardExpiryDate(testPTR))
  {
    case WRONG_EXP_DATE:
      printf("Actual Result: WRONG_EXP_DATE \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 5: \n");
  printf("Input Data: 03?12\n");
  printf("Expected Result: WRONG_EXP_DATE \n");
  switch (getCardExpiryDate(testPTR))
  {
    case WRONG_EXP_DATE:
      printf("Actual Result: WRONG_EXP_DATE \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 5: \n");
  printf("Input Data: \n");
  printf("Expected Result: WRONG_EXP_DATE \n");
  switch (getCardExpiryDate(testPTR))
  {
    case WRONG_EXP_DATE:
      printf("Actual Result: WRONG_EXP_DATE \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 5: \n");
  printf("Input Data: 03/122 \n");
  printf("Expected Result: WRONG_EXP_DATE \n");
  switch (getCardExpiryDate(testPTR))
  {
    case WRONG_EXP_DATE:
      printf("Actual Result: WRONG_EXP_DATE \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }
}

void getCardPANTest (void){
  ST_cardData_t test={"","",""};
  ST_cardData_t *testPTR=&test;

  printf("Tester Name: Seif BorhanEldin Safwat Khattab Omar\n");
  printf("Function Name: getCardPan \n");


  printf("Test Case 1: \n");
  printf("Input Data: 1234567891123456789 \n");
  printf("Expected Result: CARD_OK \n");
  switch (getCardPAN(testPTR))
  {
    case WRONG_PAN:
      printf("Actual Result: WRONG_PAN \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 2: \n");
  printf("Input Data: a12345678901234567 \n");
  printf("Expected Result: WRONG_PAN \n");
  switch (getCardPAN(testPTR))
  {
    case WRONG_PAN:
      printf("Actual Result: WRONG_PAN \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }
  
  printf("Test Case 3: \n");
  printf("Input Data: 1234124 \n");
  printf("Expected Result: WRONG_PAN \n");
  switch (getCardPAN(testPTR))
  {
    case WRONG_PAN:
      printf("Actual Result: WRONG_PAN \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 4: \n");
  printf("Input Data: 21341242351523542423 \n");
  printf("Expected Result: WRONG_PAN \n");
  switch (getCardPAN(testPTR))
  {
    case WRONG_PAN:
      printf("Actual Result: WRONG_PAN \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }


  printf("Test Case 5: \n");
  printf("Input Data: \n");
  printf("Expected Result: WRONG_PAN \n");
  switch (getCardPAN(testPTR))
  {
    case WRONG_PAN:
      printf("Actual Result: WRONG_PAN \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }

  printf("Test Case 5: \n");
  printf("Input Data: 03/12342425234232 \n");
  printf("Expected Result: WRONG_PAN \n");
  switch (getCardPAN(testPTR))
  {
    case WRONG_PAN:
      printf("Actual Result: WRONG_PAN \n");break;
    case CARD_OK:
      printf("Actual Result: CARD_OK \n");break;
  }
}
 
 



