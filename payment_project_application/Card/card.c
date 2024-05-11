#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

//Functions Implementation
//-----------------------------------------------------------------

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    EN_cardError_t ThisFunction_ErrorState = CARD_OK;

    uint8_t CardHolderName[25] = { 0 };

    printf("\n Enter the card holder name: ");
    gets(CardHolderName);

    uint8_t NameLength = strlen(CardHolderName);

    if ((NULL == CardHolderName) || (NameLength < 20) || (NameLength > 24))
    {
        ThisFunction_ErrorState = WRONG_NAME;

    }
    else
    {
        for (uint16_t i = 0; i < NameLength; i++) {
            if (!isalpha(CardHolderName[i]) && CardHolderName[i] != ' ') {
                ThisFunction_ErrorState = WRONG_NAME;
                break;
            }
        }

    }
    if (ThisFunction_ErrorState == CARD_OK) {
       // strcpy(cardData->cardHolderName, CardHolderName);
        strncpy_s(cardData->cardHolderName, sizeof(cardData->cardHolderName), CardHolderName, _TRUNCATE);

    }
    return ThisFunction_ErrorState;
}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    EN_cardError_t ThisFunction_ErrorState = CARD_OK;

    uint8_t cardExpirationDate[25] = { 0 };

    printf("\n Enter the card expiration date in this format(xx/xx): ");
    gets(cardExpirationDate);

    uint8_t DateLength = strlen(cardExpirationDate);

    if ((NULL == cardExpirationDate) || (DateLength < 5) || (DateLength > 5) || (cardExpirationDate[2] != '/'))
    {
        ThisFunction_ErrorState = WRONG_EXP_DATE;
    }
    else
    {
       // strcpy(cardData->cardExpirationDate, cardExpirationDate);
        strcpy_s(cardData->cardExpirationDate, sizeof(cardData->cardExpirationDate), cardExpirationDate);

    }

    return ThisFunction_ErrorState;
}


EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{

    EN_cardError_t ThisFunction_ErrorState = CARD_OK;

    uint8_t cardPAN[20] = { 0 };

    printf("\n Enter the card primary account number in this format(xxxx xxxx xxxx xxxx): ");
    gets(cardPAN);

    uint8_t PANLength = strlen(cardPAN);

    if (PANLength < 16 || PANLength > 19) {
        ThisFunction_ErrorState = WRONG_PAN;
    }
    else {
        // Check each character in the PAN
        for (uint16_t i = 0; i < PANLength; i++) {
            if (i == 4 || i == 9 || i == 14) {
                if (cardPAN[i] != ' ') {
                    ThisFunction_ErrorState = WRONG_PAN;
                    break;
                }
            }
        }
    }

    if (ThisFunction_ErrorState == CARD_OK) {
        //strcpy(cardData->primaryAccountNumber, cardPAN);
        strcpy_s(cardData->primaryAccountNumber, sizeof(cardData->primaryAccountNumber), cardPAN);

    }

    return ThisFunction_ErrorState;
}


//Test Functions
//-----------------------------------------------------------------

//getCardHolderNameTest Function Tests
//---------------------------------------------------------------
void getCardHolderNameTest(void)
{
    printf("Tester Name: Mohamed El-kassas\n");
    printf("Function Name: getCardHolderName\n");

    // Test Case 1: Happy Scenario
    printf("Test Case 1:\n");
    printf("Input Data: Mohamed Ahmed Elkassas\n");
    printf("Expected Result: CARD_OK\n");
    ST_cardData_t cardData1;
    EN_cardError_t result1 = getCardHolderName(&cardData1);
    printf("Actual Result: %s\n", (result1 == WRONG_NAME) ? "WRONG_NAME" : "CARD_OK");
    if (result1 == CARD_OK)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 2: Name Length less than 20
    printf("Test Case 2:\n");
    printf("Input Data: Mohamed\n");
    printf("Expected Result: WRONG_NAME\n");
    ST_cardData_t cardData2;
    EN_cardError_t result2 = getCardHolderName(&cardData2);
    printf("Actual Result: %s\n", (result2 == WRONG_NAME) ? "WRONG_NAME" : "CARD_OK");
    if (result2 == WRONG_NAME)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 3: Name Length more than 24
    printf("Test Case 3:\n");
    printf("Input Data: FSDFDSF DFDSFDSF SDFSDFS DFDS FDSFWER DSF\n");
    printf("Expected Result: WRONG_NAME\n");
    ST_cardData_t cardData3;
    EN_cardError_t result3 = getCardHolderName(&cardData3);
    printf("Actual Result: %s\n", (result3 == WRONG_NAME) ? "WRONG_NAME" : "CARD_OK");
    if (result3 == WRONG_NAME)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 4: Enter numbers
    printf("Test Case 4:\n");
    printf("Input Data: FSDFDSF 56466 SDFFS \n");
    printf("Expected Result: WRONG_NAME\n");
    ST_cardData_t cardData4;
    EN_cardError_t result4 = getCardHolderName(&cardData4);
    printf("Actual Result: %s\n", (result4 == WRONG_NAME) ? "WRONG_NAME" : "CARD_OK");
    if (result4 == WRONG_NAME)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");
}


//getCardExpiryDate Function Tests
//---------------------------------------------------------------
void getCardExpiryDateTest(void)
{
    printf("Tester Name: Mohamed El-kassas\n");
    printf("Function Name: getCardExpiryDate\n");

    // Test Case 1: Happy Scenario
    printf("Test Case 1:\n");
    printf("Input Data: 12/26\n");
    printf("Expected Result: CARD_OK\n");
    ST_cardData_t cardData1;
    EN_cardError_t result1 = getCardExpiryDate(&cardData1);
    printf("Actual Result: %s\n", (result1 == WRONG_EXP_DATE) ? "WRONG_EXP_DATE" : "CARD_OK");
    if (result1 == CARD_OK)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 2: Date Length less than 5
    printf("Test Case 2:\n");
    printf("Input Data: 1/26\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    ST_cardData_t cardData2;
    EN_cardError_t result2 = getCardExpiryDate(&cardData2);
    printf("Actual Result: %s\n", (result2 == WRONG_EXP_DATE) ? "WRONG_EXP_DATE" : "CARD_OK");
    if (result2 == WRONG_EXP_DATE)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 3: Date Length more than 5
    printf("Test Case 3:\n");
    printf("Input Data: 12/2026\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    ST_cardData_t cardData3;
    EN_cardError_t result3 = getCardExpiryDate(&cardData3);
    printf("Actual Result: %s\n", (result3 == WRONG_EXP_DATE) ? "WRONG_EXP_DATE" : "CARD_OK");
    if (result3 == WRONG_EXP_DATE)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 4: "/" is not present
    printf("Test Case 4:\n");
    printf("Input Data: 1226\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    ST_cardData_t cardData4;
    EN_cardError_t result4 = getCardExpiryDate(&cardData4);
    printf("Actual Result: %s\n", (result4 == WRONG_EXP_DATE) ? "WRONG_EXP_DATE" : "CARD_OK");
    if (result4 == WRONG_EXP_DATE)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");
}

//getCardPANTest Function Tests
//---------------------------------------------------------------
void getCardPANTest(void)
{
    printf("Tester Name: Mohamed El-kassas\n");
    printf("Function Name: getCardPAN\n");

    // Test Case 1: Happy Scenario
    printf("Test Case 1:\n");
    printf("Input Data: 1234 5678 9012 3456\n");
    printf("Expected Result: CARD_OK\n");
    ST_cardData_t cardData1;
    EN_cardError_t result1 = getCardPAN(&cardData1);
    printf("Actual Result: %s\n", (result1 == WRONG_PAN) ? "WRONG_PAN" : "CARD_OK");
    if (result1 == CARD_OK)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 2: PAN Length less than 16
    printf("Test Case 2:\n");
    printf("Input Data: 1234 5678 9012 34\n");
    printf("Expected Result: WRONG_PAN\n");
    ST_cardData_t cardData2;
    EN_cardError_t result2 = getCardPAN(&cardData2);
    printf("Actual Result: %s\n", (result2 == WRONG_PAN) ? "WRONG_PAN" : "CARD_OK");
    if (result2 == WRONG_PAN)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 3: PAN Length more than 20
    printf("Test Case 3:\n");
    printf("Input Data: 1234 5678 9012 3456 7890\n");
    printf("Expected Result: WRONG_PAN\n");
    ST_cardData_t cardData3;
    EN_cardError_t result3 = getCardPAN(&cardData3);
    printf("Actual Result: %s\n", (result3 == WRONG_PAN) ? "WRONG_PAN" : "CARD_OK");
    if (result3 == WRONG_PAN)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");

    // Test Case 4: no space added
    printf("Test Case 4:\n");
    printf("Input Data: 1234567890123456\n");
    printf("Expected Result: WRONG_PAN\n");
    ST_cardData_t cardData4;
    EN_cardError_t result4 = getCardPAN(&cardData4);
    printf("Actual Result: %s\n", (result4 == WRONG_PAN) ? "WRONG_PAN" : "CARD_OK");
    if (result4 == WRONG_PAN)
    {
        printf("Result: Passed\n");
    }
    else
    {
        printf("Result: Failed\n");
    }
    printf("\n");


}

