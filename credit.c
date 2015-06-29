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
#include <math.h>

/**
 * Checks if the passed credit card number (as an array of ints) is valid.
 */
bool cardNumberIsValid (int cardNumber[], int length);

/**
 * returns the length of a long long number.
 * note that this method returns a value that is ALREADY ZERO INDEXED
 */
int lengthOfNumber(long long number);

int main (void)
{
    //Get credit card number
    printf ("Enter credit card number: ");
    long long userEntry = GetLongLong();
    
    //Determine the card type based on the number of digits (default to INVALID)
    string cardType = "INVALID";
    int length = lengthOfNumber(userEntry);
    
    //Convert the long long into an array of ints
    int cardNumber [length];

    for (int i = 0; i <= length; i++)
    {
        //Grab the last digit and then shift one place
        cardNumber[i] = userEntry % 10;
        userEntry /= 10;
    }
    
    //Check card type and validity
    switch (length)
    {   
        //Visa always start with 4
        case 12:
            cardType = (cardNumber[12] == 4) ? "VISA" : "INVALID";
            break;
        //AMEX always start with 34 or 37
        case 14:
            if (cardNumber[14] == 3)
            {
                if ((cardNumber[13] == 4) || (cardNumber[13] == 7))
                {
                    cardType = "AMEX";
                }
            }
            break;
         
         //Mastercard starts with 51, 52, 53, 54, 55
         //Visa starts with 4
        case 15:
            if ((cardNumber[15] == 5) && (cardNumber[14] > 0) && (cardNumber[14] < 6))
            {
                cardType = "MASTERCARD";
            }
            else if (cardNumber[15] == 4)
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
    //Work through the credit card number array
    //Even numbers are to be summed (zero index)
    //Odd numbers are to be multiplied by 2 and then their digits summed
    int numberSum = 0;
    for (int i = 0; i <= length; i++)
    {
        if (i % 2 == 0)
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

int lengthOfNumber(long long number)
{
    int i = 0;
    while (number)
    {
        //Right shift the number one digit
        number /= 10;
        i++;
    }
    return i - 1;
}

