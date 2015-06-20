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
#include <math.h>

/**
 * Checks if the passed credit card number (as an array of ints) is valid.
 */
bool cardNumberIsValid (int cardNumber[], int length);

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
        //Visa always start with 4
        case 13:
            cardType = (cardNumber[0] == 4) ? "VISA" : "INVALID";
            break;
        //AMEX always start with 34 or 37
        case 15:
            if (cardNumber[0] == 3)
            {
                if ((cardNumber[1] == 4) || (cardNumber[1] == 7))
                {
                    cardType = "AMEX";
                }
            }
            break;
         
         //Mastercard starts with 51, 52, 53, 54, 55
         //Visa starts with 4
        case 16:
            if ((cardNumber[0] == 5) && (cardNumber[1] > 0) && (cardNumber[1] < 6))
            {
                cardType = "MASTERCARD";
            }
            else if (cardNumber[0] == 4)
            {
                cardType = "VISA";
            }
            break;
        default:
            //Print invalid and drop out if card doesn't have the right number of characters
            printf("%s\n", cardType);
            return 0;
    }
    
    //Determine if the credit card has a valid number
    if (cardNumberIsValid(cardNumber, length))
    {
        printf("Card type: ");
        printf("%s\n", cardType);
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

bool cardNumberIsValid (int cardNumber[], int length)
{
    //Convert length to 0 indexed number
    int indexLength = length - 1;
    //Work through the credit card number array
    //Even numbers are to be summed
    //Odd numbers are to be multiplied by 2 and then their digits summed
    int numberSum = 0;
    for (int i = indexLength; i >=0; i--)
    {
        if ((indexLength - i) % 2 == 0)
        {
            //Must be even
            numberSum += cardNumber[i];
        }
        else
        {
            //Must be odd
            int temporaryNumber = cardNumber[i] * 2;
            numberSum += ((temporaryNumber / 10) + (temporaryNumber % 10));
        }
    }

    //If last digit is 0, then return TRUE.  Otherwise return FALSE
    if (numberSum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
