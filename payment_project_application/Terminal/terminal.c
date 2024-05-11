#include <stdio.h>
#include <string.h>
#include "terminal.h"
#include "server.h"



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{

    uint8_t transactionDate[11] = { 0 };

    printf("\nEnter transaction date (DD/MM/YYYY) ");
    gets(transactionDate);

    uint8_t TransactionDateLength = strlen(transactionDate);

    if ((NULL == transactionDate) ||
        (TransactionDateLength < 10) ||
        (TransactionDateLength > 10) ||
        (transactionDate[2] != '/' || transactionDate[5] != '/'))
    {
        return WRONG_DATE;
    }
    else
    {
        //strcpy(termData->transactionDate, transactionDate);
        strcpy_s(termData->transactionDate, sizeof(termData->transactionDate), transactionDate);

    }

    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{

    uint8_t cardmonth =
        ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
    uint8_t cardyear =
        ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');

    uint8_t transactionmonth =
        ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
    uint8_t transactionyear =
        ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');

    if ((cardyear < transactionyear) || ((cardyear == transactionyear) && (cardmonth <= transactionmonth)))
    {
        return  EXPIRED_CARD;
    }

    return TERMINAL_OK;
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    printf("Enter transaction amount: ");
    scanf_s("%f", &termData->transAmount);
    getchar();

    if (termData->transAmount <= 0)
    {
        return INVALID_AMOUNT;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
    if (maxAmount <= 0)
    {
        return INVALID_MAX_AMOUNT;
    }
    termData->maxTransAmount = maxAmount;
    return TERMINAL_OK;
}

//************the test cases*****************


void getTransactionDateTest(void)
{
    // Test Case 1
    printf("Test Case 1:\n");
    printf("Input Data: 15/04/2024\n");
    printf("Expected Result: TERMINAL_OK\n");
    ST_terminalData_t termData;
    EN_terminalError_t result1 = getTransactionDate(&termData);
    printf("Actual Result: %s\n", (result1 == WRONG_DATE) ? "WRONG_DATE" : "TERMINAL_OK");
    if (result1 == TERMINAL_OK)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 2
    printf("Test Case 2:\n");
    printf("Input Data: 15-04-2024\n");
    printf("Expected Result: WRONG_DATE\n");
    ST_terminalData_t termData2;
    EN_terminalError_t result2 = getTransactionDate(&termData2);
    printf("Actual Result: %s\n", (result2 == WRONG_DATE) ? "WRONG_DATE" : "TERMINAL_OK");
    if (result2 == WRONG_DATE)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");
}

void isCardExpiredTest(void)
{
    // Test Case 3
    printf("Test Case 3:\n");
    printf("Input Data: 04/02/2024\n");
    printf("Expected Result: TERMINAL_OK\n");
    ST_cardData_t cardData = { "shimaa shehata", "1234567891234567", "06/25" };
    ST_terminalData_t termData = { 100,1000,0 };
    printf("entre transction date : ");
    gets(termData.transactionDate);
    EN_terminalError_t result3 = isCardExpired(&cardData, &termData);
    printf("Actual Result: %s\n", (result3 == EXPIRED_CARD) ? "EXPIRED_CARD" : "TERMINAL_OK");
    if (result3 == TERMINAL_OK)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }

    printf("\n");


    // Test Case 4
    printf("Test Case 4:\n");
    printf("Input Data: 04/02/2026\n");
    printf("Expected Result: TERMINAL_OK\n");
    ST_cardData_t cardData2 = { "shimaa shehata", "1234567891234567", "06/25" };
    ST_terminalData_t termData2 = { 100,1000,0 };
    printf("entre transction date : ");
    gets(termData2.transactionDate);
    EN_terminalError_t result4 = isCardExpired(&cardData2, &termData2);
    printf("Actual Result: %s\n", (result4 == EXPIRED_CARD) ? "EXPIRED_CARD" : "TERMINAL_OK");
    if (result4 == EXPIRED_CARD)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }

    printf("\n");

}
void getTransactionAmounttest(void)
{
    //test case 5
    printf("Test Case 5:\n");
    printf("Input Data: 1000\n");
    printf("Expected Result: TERMINAL_OK\n");
    ST_terminalData_t termData;
    EN_terminalError_t result = getTransactionAmount(&termData);
    printf("Actual Result: %s\n", (result == INVALID_AMOUNT) ? "INVALID_AMOUNT" : "TERMINAL_OK");
    if (result == TERMINAL_OK)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }

    printf("\n");
    //test case 6
    printf("Test Case 6:\n");
    printf("Input Data: -1000\n");
    printf("Expected Result: INVALID_AMOUNT\n");
    ST_terminalData_t termData2;
    EN_terminalError_t result2 = getTransactionAmount(&termData2);
    printf("Actual Result: %s\n", (result2 == INVALID_AMOUNT) ? "INVALID_AMOUNT" : "TERMINAL_OK");
    if (result2 == INVALID_AMOUNT)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }

    printf("\n");

}

void isBelowMaxAmounttest(void)

//test case7
{
    printf("Test Case 7:\n");
    printf("Input Data: 1000 for max amount\n and 500 for transamount\n");
    printf("Expected Result: TERMINAL_OK\n");
    ST_terminalData_t termData;
    termData.maxTransAmount = 1000.0;
    termData.transAmount = 500.0;
    EN_terminalError_t result = isBelowMaxAmount(&termData);
    printf("Actual Result: %s\n", (result == TERMINAL_OK) ? "TERMINAL_OK" : "EXCEED_MAX_AMOUNT");
    if (result == TERMINAL_OK)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }

    //tets case 8

    printf("Test Case 8:\n");
    printf("Input Data: 1000 for max amount\n and 2000 for transamount\n");
    printf("Expected Result: EXCEED_MAX_AMOUNT\n");
    ST_terminalData_t termData1;
    termData1.maxTransAmount = 1000.0;
    termData1.transAmount = 2000.0;
    EN_terminalError_t result1 = isBelowMaxAmount(&termData1);
    printf("Actual Result: %s\n", (result1 == TERMINAL_OK) ? "TERMINAL_OK" : "EXCEED_MAX_AMOUNT");
    if (result1 == EXCEED_MAX_AMOUNT)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");


}



void setMaxAmounttest()
{
    //test case 9
    {


        printf("Test Case 9:\n");
        printf("Input Data: maxAmount = 1000.0\n");
        printf("Expected Result: TERMINAL_OK\n");

        ST_terminalData_t termData;
        termData.maxTransAmount = 0.0;
        EN_terminalError_t result1 = setMaxAmount(&termData, 1000.0);
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: %s\n", (result1 == TERMINAL_OK) ? "TERMINAL_OK" : "INVALID_MAX_AMOUNT");
        if (result1 == TERMINAL_OK)
        {
            printf("Result: Passed\n");
        }
        else
        {
            printf("Result: Failed\n");
        }
        printf("\n");

    }

    //test case 10
    {

        printf("Test Case 10:\n");
        printf("Input Data: maxAmount = 0.0\n");
        printf("Expected Result: INVALID_MAX_AMOUNT\n");
        ST_terminalData_t termData1;
        EN_terminalError_t result2 = setMaxAmount(&termData1, 0.0);
        printf("Actual Result: %s\n", (result2 == INVALID_MAX_AMOUNT) ? "INVALID_MAX_AMOUNT" : "TERMINAL_OK");
        if (result2 == INVALID_MAX_AMOUNT)
        {
            printf("Result: Passed\n");
        }
        else
        {
            printf("Result: Failed\n");
        }
        printf("\n");
    }
}







