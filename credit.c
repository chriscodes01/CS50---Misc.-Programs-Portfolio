#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card;
    int r;
    int r1 = 0;
    int r2 = 0;
    int count = 0;
    int b;
    int a;
    int as;
    int al;
    int a1;
    int a2;
    int sum;
    int checksum;
    string card_name;
    int card_verify;
    //Prompt for card number.
    do
    {
        card = get_long("Number: ");
    }
    while (card <= 0);

    do
    {
        //Determine card bank institution.
        if (card > 50 && card < 56)
        {
            card_name = "MASTERCARD";
            card_verify = 1;
        }
        if (card == 34 || card == 37)
        {
            card_name = "AMEX";
            card_verify = 1;
        }
        if (card == 4)
        {
            card_name = "VISA";
            card_verify = 1;
        }
        if (card > 0 && card < 3)
        {
            card_verify = 0;
        }
        if (card == 30 || card == 31 || card == 32 || card == 33 || card == 35 || card == 36 || card == 38 || card == 39 || card == 50)
        {
            card_verify = 0;
        }
        if (card >= 56 && card <= 99)
        {
            card_verify = 0;
        }
        //Obtain last digit and every other digit from there.
        r = card % 10;
        //Use this for counting digits.
        if (card > 0)
        {
            count++;
        }
        //printf("Card is: %ld\n", card);
        card = (card - r) / 10;
        //Add the above digits together.
        r1 = r1 + r;
        //printf("r1: %i\n", r1);


        //Determine card bank institution.
        if (card > 50 && card < 56)
        {
            card_name = "MASTERCARD";
            card_verify = 1;
        }
        if (card == 34 || card == 37)
        {
            card_name = "AMEX";
            card_verify = 1;
        }
        if (card == 4)
        {
            card_name = "VISA";
            card_verify = 1;
        }
        if (card > 0 && card < 3)
        {
            card_verify = 0;
        }
        if (card == 30 || card == 31 || card == 32 || card == 33 || card == 35 || card == 36 || card == 38 || card == 39 || card == 50)
        {
            card_verify = 0;
        }
        if (card >= 56 && card <= 99)
        {
            card_verify = 0;
        }
        r = card % 10;
        //Use this for counting digits.
        if (card > 0)
        {
            count++;
        }
        //Obtain second to last digit and every other digit from there.
        card = (card - r) / 10;
        a = r * 2;
        //Obtain two digit numbers. Assign the digits as a1 and a1, then add the two individual digits together. Add to total.
        if (a >= 10)
        {
            al = a;
            a1 = al % 10;
            a2 = (al - a1) / 10;
            r2 = r2 + a1 + a2;
        }
        //Obtain single digit numbers. Assign the digit as. Add it to total.
        if (a < 10)
        {
            as = a;
            r2 = r2 + as;
        }
    }
    while (card > 0);
    //Combine totals to a sum.
    sum = r1 + r2;
    //Determine last digit of sum.
    checksum = sum % 10;
    if (checksum > 0 || card_verify == 0 || count <= 12)
    {
        printf("INVALID\n");
    }
    else
    {
        printf("%s\n", card_name);
    }
}