#include "app.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include <stdio.h>

void appStart(void)
{
    EN_cardError_t errorNumCard;          // Error handling for card module
    EN_terminalError_t errorNumTerminal;  // Error handling for terminal module
    EN_transState_t transactionState;     // Transaction state
    ST_cardData_t cardData;               // Initialize card data structure
    ST_terminalData_t terminalData;       // Initialize terminal data structure

    printf("Starting Payment Application\n");

    /////////////////////////////////////////////// Card Module ///////////////////////////////////////////////////

    // Get card holder name
    errorNumCard = getCardHolderName(&cardData);
    if (errorNumCard != CARD_OK) {
        printf("Error: Failed to get card holder name\n");
        return;
    }

    // Get card expiry date
    errorNumCard = getCardExpiryDate(&cardData);
    if (errorNumCard != CARD_OK) {
        printf("Error: Failed to get card expiry date\n");
        return;
    }

    // Get card PAN
    errorNumCard = getCardPAN(&cardData);
    if (errorNumCard != CARD_OK) {
        printf("Error: Failed to get card PAN\n");
        return;
    }

    // Display card data
    printf("\nCard Holder Name: %s\n", cardData.cardHolderName);
    printf("Card Expiry Date: %s\n", cardData.cardExpirationDate);
    printf("Card PAN: %s\n", cardData.primaryAccountNumber);

    /////////////////////////////////////////////// Terminal Module ///////////////////////////////////////////////////

    // Set a maximum transaction amount
    terminalData.maxTransAmount = 10000;

    // Test getTransactionDate function
    errorNumTerminal = getTransactionDate(&terminalData);
    if (errorNumTerminal != TERMINAL_OK) {
        printf("Error: Failed to get transaction date\n");
        return;
    }
    printf("Transaction Date: %s\n", terminalData.transactionDate);
    printf("\n");

    // Test isCardExpired function
    errorNumTerminal = isCardExpired(&cardData, &terminalData);
    if (errorNumTerminal == EXPIRED_CARD) {
        printf("Error: Card has expired\n");
        return;
    }
    else if (errorNumTerminal != TERMINAL_OK) {
        printf("Error: Failed to check card expiration\n");
        return;
    }

    // Test getTransactionAmount function
    errorNumTerminal = getTransactionAmount(&terminalData);
    if (errorNumTerminal != TERMINAL_OK) {
        printf("Error: Failed to get transaction amount\n");
        return;
    }
    printf("Transaction Amount: %.2f\n", terminalData.transAmount);
    printf("\n");

    // Test isBelowMaxAmount function
    errorNumTerminal = isBelowMaxAmount(&terminalData);
    if (errorNumTerminal != TERMINAL_OK) {
        printf("the transaction Amout is %f\n",terminalData.transAmount);
        printf("the transaction date is %11s\n",terminalData.transactionDate);
        printf("the MAX transaction Amout is %f\n",terminalData.maxTransAmount);
        printf("Invalid Transaction: Transaction amount exceeds maximum amount\n");
        return;
    }
    if(errorNumTerminal == TERMINAL_OK)
    {
    // Create a transaction structure to hold data
    ST_transaction_t transaction;
    ST_accountsDB_t accountReference;

    transaction.cardHolderData = cardData;
    transaction.terminalData = terminalData;

    // Receive transaction data and process
    transactionState = recieveTransactionData(&transaction);




    // Check the transaction state and print appropriate message
    switch (transactionState) {
    case APPROVED:
        printf("Valid Transaction: Money will be transferred successfully \n");
         saveTransaction(&transaction);
         listSavedTransactions();

        printf("\n");
        break;
    case DECLINED_INSUFFICIENT_FUND:
        printf("Transaction Declined: Insufficient Fund\n");
        saveTransaction(&transaction);
         listSavedTransactions();
        break;
    case DECLINED_STOLEN_CARD:
        printf("Transaction Declined: Stolen Card\n");
          saveTransaction(&transaction);
         listSavedTransactions();
        break;
    case FRAUD_CARD:
        printf("Transaction Declined: Fraudlent Card\n");
        break;
    case INTERNAL_SERVER_ERROR:
        printf("Transaction Failed: Internal Server Error\n");
        break;
    default:
        printf("Unknown Transaction State\n");
        break;
    }
    }
}
