/**
 * credit.c
 *
 * Exit32Studio - J. Bobula
 * contact@exit32studio.com
 *
 * Checks credit card number for type of card and validity
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main (void)
{
    //Get credit card number
    printf ("Enter credit card number: ");
    string userEntry = GetString();
    
    //Determine the card type based on the number of digits (default to INVALID)
    string cardType = "INVALID";
    int length = strlen(userEntry);
    
    //Convert string into array of ints (also account for ASCII value vs int value)
    int cardNumber [length];
    for (int i = 0; i < length; i++)
    {
        cardNumber[i] = userEntry[i] - '0';
    }
    //Check card type and validity
    switch (length)
    {
        case 13:
            cardType = "VISA";
            break;
        case 15:
            cardType = "AMEX";
            break;
        case 16:
            cardType = "MASTERCARD / VISA";
            break;
        default:
            //Print invalid and drop out if card doesn't have the right number of characters
            printf("%s\n", cardType);
            return 0;
    }
    
    printf("Card type: ");
    printf("%s\n", cardType);
    
    return 0;
}


