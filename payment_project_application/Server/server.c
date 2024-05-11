#include <string.h>
#include <stdio.h>
#include "Server.h"
#include "terminal.h"
ST_accountsDB_t accountsDB[255] = {
    { 2000.0, RUNNING, "2610 2005 3786 4434" },
    { 2000.0, BLOCKED, "9536 9515 9336 5605" },
    { 4000.0, RUNNING, "4903 4780 7924 5246" },
    { 4000.0, BLOCKED, "8751 8762 4708 1216" },
    { 6000.0, RUNNING, "4719 8024 5597 9296" },
    { 6000.0, BLOCKED, "6907 9407 2688 4180" },
    { 8000.0, RUNNING, "6263 5659 9780 7508" },
    { 8000.0, BLOCKED, "3358 0659 6348 3406" },
    { 10000.0, RUNNING, "4068 9751 5131 3987" },
    { 10000.0, BLOCKED, "2652 6238 7344 4840" }
};
ST_transaction_t transactions[255] = { 0 };
int32_t lastSequenceNumber = -1;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    if (transData == NULL)
    {
        return INTERNAL_SERVER_ERROR;
    }

    //EN_serverError_t cardValidationResult = isValidAccount(&(transData->cardHolderData), accountsDB);
    else if (isValidAccount(&(transData->cardHolderData), accountsDB) != SERVER_OK)
    {
        return FRAUD_CARD;
    }


   else if (isBlockedAccount(&accountsDB) == BLOCKED_ACCOUNT)
    {
        EN_serverError_t saveResult1 = saveTransaction(transData);
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    else if (isAmountAvailable(&transData->terminalData, accountsDB) == LOW_BALANCE)
    {
        EN_serverError_t saveResult1 = saveTransaction(transData);
        transData->transState = DECLINED_INSUFFICIENT_FUND;
        return DECLINED_INSUFFICIENT_FUND;
    }


    //EN_serverError_t saveResult = saveTransaction(transData);
   else if (saveTransaction(transData) != SERVER_OK)
    {
        return INTERNAL_SERVER_ERROR;
    }

    transData->transState = APPROVED;
    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
    for (int i = 0; i < 255; ++i) {
        if (strcmp((char*)accountRefrence[i].primaryAccountNumber, (char*)cardData->primaryAccountNumber) == 0) {
            *accountRefrence = accountRefrence[i];
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountReference) {
    if (accountReference->state == BLOCKED) {
        return BLOCKED_ACCOUNT;
    }
    return SERVER_OK;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountReference)
{
    if (termData->transAmount > accountReference->balance)
    {
        return LOW_BALANCE;
    }
    int newblanace= accountReference->balance-termData->transAmount;
    printf("the new balance is %d\n", newblanace);

    return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    lastSequenceNumber++;
    transData->transactionSequenceNumber = lastSequenceNumber;
    transactions[lastSequenceNumber] = *transData;
    //listSavedTransactions();
    return SERVER_OK;
}
void listSavedTransactions() {
    printf("Listing all saved transactions:\n");

    for (int i = 1; i <= lastSequenceNumber; ++i) {

        printf("#########################\n");
        printf("Transaction Sequence Number: %d\n", transactions[i].transactionSequenceNumber);
        printf("Transaction Date: %s\n", transactions[i].terminalData.transactionDate);
        printf("Transaction Amount: %.2f\n", transactions[i].terminalData.transAmount);
         printf("Transaction State: %d\n", transactions[i].transState);
         if(transactions[i].transState==0)
        printf("Transaction State: APPROVED\n");
        if(transactions[i].transState==1)
        printf("Transaction State: DECLINED_INSUFFICIENT_FUND\n");
        if(transactions[i].transState==2)
        printf("Transaction State: DECLINED_STOLEN_CARD\n");
        printf("Terminal Max Amount: %.2f\n", transactions[i].terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n", transactions[i].cardHolderData.cardHolderName);
        printf("PAN: %s\n", transactions[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transactions[i].cardHolderData.cardExpirationDate);
        printf("#########################\n");
    }
}
//***********test cases******************************************************************


void test_recieveTransactionData(void)
{

    // test case 1 (happy senario the result is approved)
    {
        printf("Test Case 1:\n");
        printf("input data : John Doe, 2610 2005 3786 4434 , 06/25 for card holder data \n and (04/24,100 ) for terminal data\n");
        printf("Expected Result: APPROVED\n");
        ST_transaction_t transaction =
        {
            { "John Doe", "2610 2005 3786 4434", "06/25" },  // Card holder data
            {1000,100, "04/24" },   // Terminal data
        };

        EN_transState_t result = recieveTransactionData(&transaction);
            printf("Actual Result: %s\n", (result == APPROVED) ? "APPROVED" : "error");

        if (result == APPROVED)
        {
            printf("Result: Test Passed\n");
        }
        else
        {
            printf("Result: Test Failed\n");
        }
    }

    //test case 2 (sad senario result is declined insufficient fund)
    {
        printf("Test Case 2:\n");
        printf("input data : John Doe, 1234567890123456 , 06/25 for card holder data \n and (04/24,100 ) for terminal data\n");
        printf("Expected Result: FRAUD_CARD\n");
        ST_transaction_t transaction1 =
        {
            { "John Doe", "1234567890123456", "06/25" },  // Card holder data
            { 1000,100, "04/24" },  // Terminal data
        };

        EN_transState_t result1 = recieveTransactionData(&transaction1);
        printf("Actual Result: %s\n", (result1 == APPROVED) ? "APPROVED" : "FRAUD_CARD");

        if (result1 == FRAUD_CARD)
        {
            printf("Result: Test Passed\n");
        }
        else
        {
            printf("Result: Test Failed\n");
        }
    }

}


void test_isValidAccount(void)
{

    //  test case 3 (happy senario the result is SERVER_OK)
    {
        printf("Test Case 3:\n");
         printf("input data : \n(salma yasser ,2610200537864434,06/25) for card data\n (2000,runnung) for account \n");
        printf("Expected Result: SERVER_OK\n");
        ST_cardData_t cardData = { "salma yasser","2610200537864434", "06/25" };
        ST_accountsDB_t account = { 2000.0, RUNNING, "2610200537864434" };
        EN_serverError_t result = isValidAccount(&cardData, &account);
        printf("Actual Result: %s\n", (result == SERVER_OK) ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
        if (result == SERVER_OK) printf("Result: Test Passed\n");
        else printf("Result: Test Failed\n");

    }

    //test case 4 (sad senario result is ACCOUNT_NOT_FOUND)
    {
        printf("Test Case 4:\n");
        printf("input data : \n(salma yasser ,2610200537864434,06/25) for card data\n (2000,runnung) for account \n");
        printf("Expected Result: ACCOUNT_NOT_FOUND\n");
        ST_cardData_t cardData1 = { "salma yasser","1239567890123456", "06/25" };
        ST_accountsDB_t account1 = { 2000.0, RUNNING, "2610 2005 3786 4434" };
        EN_serverError_t result1 = isValidAccount(&cardData1, &account1);
        printf("Actual Result: %s\n", (result1 == SERVER_OK) ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
        if (result1 == ACCOUNT_NOT_FOUND)
        {
            printf("Result: Test Passed\n");
        }
        else
        {
            printf("Result: Test Failed\n");
        }
    }


}

void test_isBlockedAccount(void)
{
    //  test case 5 (happy senario the result is Account is not blocked)
    {
        printf("Test Case 5:\n");
        printf("input data :{ 2000.0, RUNNING, 2610 2005 3786 4434 }\n");
        printf("Expected Result: SERVER_OK\n");
        ST_accountsDB_t account = { 2000.0, RUNNING, "2610 2005 3786 4434" };

        EN_serverError_t result = isBlockedAccount(&account);
        printf("Actual Result: %s\n", (result == SERVER_OK) ? "SERVER_OK" : "BLOCKED_ACCOUNT");
        if (result == SERVER_OK)
        {
            printf("Result: Test Passed\n");
        }
        else
        {
            printf("Result: Test Failed\n");
        }
    }

    //test case 6 (sad senario result is Account is blocked)
    {
        printf("Test Case 6:\n");
        printf("input data :{ 2000.0, BLOCKED, 9536 9515 9336 5605 }\n");
        printf("Expected Result: BLOCKED_ACCOUNT\n");
        ST_accountsDB_t account1 = { 2000.0, BLOCKED, "9536 9515 9336 5605" };
        EN_serverError_t result1 = isBlockedAccount(&account1);
         printf("Actual Result: %s\n", (result1 == SERVER_OK) ? "SERVER_OK" : "BLOCKED_ACCOUNT");
        if (result1 == BLOCKED_ACCOUNT)
        {
            printf("Result: Test Passed\n");
        }
        else
        {
            printf("Result: Test Failed\n");
        }
    }


}

void test_isAmountAvailable(void)
{


    //  test case 7 (happy senario the result is Sufficient balance)
    {
        printf("Test Case 7:\n");
        printf("input data :\n { 1000,100, 04/24 } for term data\n and { 2000.0, RUNNING, 2610200537864434} for account \n");
        printf("Expected Result: SERVER_OK\n");
        ST_terminalData_t termData = { 1000,100, "04/24" };
        ST_accountsDB_t account = { 2000.0, RUNNING, "2610200537864434" };
        EN_serverError_t result = isAmountAvailable(&termData, &account);
       printf("Actual Result: %s\n", (result == SERVER_OK) ? "SERVER_OK" : "LOW_BALANCE");
        if (result == SERVER_OK)
        {
            printf("Result: Test Passed\n");
        }
        else
        {
            printf("Result: Test Failed\n");
        }
    }
    //test case 8 (sad senario result isInsufficient balance)
    {
        printf("Test Case 8:\n");
        printf("input data :\n { 5000,100, 04/24 } for term data\n and { 2000.0, RUNNING, 2610200537864434} for account \n");
        printf("Expected Result: LOW_BALANCE\n");
        ST_terminalData_t termData1 = { 1000,100, "04/24" };
        ST_accountsDB_t account1 = { 100, RUNNING, "2610200537864434" };
        EN_serverError_t result1 = isAmountAvailable(&termData1, &account1);
       printf("Actual Result: %s\n", (result1 == SERVER_OK) ? "SERVER_OK" : "LOW_BALANCE");
        if (result1 == LOW_BALANCE)
        {
            printf("Result: Test Passed\n");
        }
        else
        {
            printf("Result: Test Failed\n");
        }
    }
}


void testSaveTransaction(void)
{
    // test case 9

        printf("Test Case 9:\n");
        printf("input data : John Doe, 9536951593365605 , 06/25 for card holder data \n and (04/24,100 ) for terminal data\n");
        printf("Expected Result: SERVER_OK\n");
        ST_transaction_t transaction =
        {
        .cardHolderData = {"John Doe", "2610200537864434", "06/25"},
        .terminalData = {1000,100, "04/24" }
        };

      EN_serverError_t result = saveTransaction(&transaction);
       printf("Actual Result: %s\n\n", (result == SERVER_OK) ? "SERVER_OK" : "Error");
       if (result == SERVER_OK)
        {
            printf("Result: Test Passed\n");
        }
        else
        {
            printf("Result: Test Failed\n");
        }

}

//Testing that listsavedtransaction is print the saved trensaction
void listSavedTransactionstest(void) {
    printf("Test Case 10:\n");
    printf("Input Data: One sample transaction added to the transactions array.\n");
    printf("Expected Result: Information about the added transaction should be printed.\n");
    printf("Actual Result:\n");
;

    // Initialize a sample transaction

    ST_transaction_t transaction1 = {

        .cardHolderData = {
            .cardHolderName = "John Doe",
            .primaryAccountNumber = "2610200537864434",
            .cardExpirationDate = "04/24"
        },
        .terminalData = {
            .transactionDate = "04/2024",
            .transAmount = 500.0,
            .maxTransAmount = 1000.0
        },

        .transactionSequenceNumber = 0
    };
       transactions[1] = transaction1;
    lastSequenceNumber = 1;


    listSavedTransactions();
}


