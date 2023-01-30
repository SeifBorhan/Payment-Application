#include "./app.h"
#include "../Card/card.h"
#include "../Server/server.h"
#include "../Terminal/terminal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


void appStart(void){
  ST_cardData_t cardData;
  ST_cardData_t *cardDataPTR = &cardData;

  if(getCardHolderName(cardDataPTR)==WRONG_NAME){
    printf("Invalid Name! \n");
    return;
  }
  if(getCardExpiryDate(cardDataPTR)==WRONG_EXP_DATE){
    printf("Invalid Expiry Date! \n");
    return;
  }
  if(getCardPAN(cardDataPTR)==WRONG_PAN){
    printf("Invalid Primary Account Number! \n");
    return;
  }

  ST_terminalData_t termData;
  ST_terminalData_t *termDataPTR = &termData;
  setMaxAmount(termDataPTR,8000);

  if(getTransactionDate(termDataPTR)==WRONG_DATE){
    printf("Invalid Transaction Date! \n");
    return;
  }

  if(isCardExpired(cardDataPTR,termDataPTR)==EXPIRED_CARD){
    printf("Declined, Unfortunately your card has expired! \n");
    return;
  }
  if(getTransactionAmount(termDataPTR)==INVALID_AMOUNT){
    printf("Invalid Amount Entered! \n");
    return;
  }

  if(isBelowMaxAmount(termDataPTR)==EXCEED_MAX_AMOUNT){
    printf("Declined, Amount is exceeding the limit! \n");
    return;
  }


  ST_transaction_t transactionData = {cardData,termData,APPROVED,0};
  ST_transaction_t *transactionDataPTR = &transactionData;

  switch(recieveTransactionData(transactionDataPTR)){
    case FRAUD_CARD:
    printf("Declined, Invalid Account! \n");return;break;
    case DECLINED_INSUFFECIENT_FUND:
    printf("Declined, Insufficient Funds! \n");return;break;
    case DECLINED_STOLEN_CARD:
    printf("Declined, Card is Blocked! \n");return;break;
    case APPROVED:
    printf("Approved \n");
  }

  
}
