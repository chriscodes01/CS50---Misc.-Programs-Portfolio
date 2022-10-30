#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//Declare variables.
char ci;

bool only_digits(string s);
char rotate(char c, int n);
int main(int argc, string argv[])
{
    string ptext;
    string ctext;
    int i;
    int len;
    int key;
    //Instruct how to use program if command-line argument is incorrect.
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Convert argv[1] from string to int using atoi.
    key = atoi(argv[1]);

    //Prompt user for plaintext (ptext). Print ciphertext bucket.
    ptext = get_string("plaintext: ");
    printf("ciphertext: ");

    //For each char in ptext, do rotate function. Print right after ciphertext bucket.
    for (i = 0, len = strlen(ptext); i < len; i++)
    {
        rotate(ptext[i], key);
        printf("%c", ci);
    }
    //Next line.
    printf("\n");
}

//Check if valid key (only digits).
bool only_digits(string s)
{
    int i;
    int len;
    for (i = 0, len = strlen(s); i < len; i++)
    {
        //If not digit, return false.
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    //Otherwise, return true.
    return true;
}

//Rotate function.
char rotate(char c, int n)
{
    //If upper...
    if (isupper(c))
    {
        c = c - 65;
        ci = (c + n) % 26;
        ci = ci + 65;
    }
    //If lower...
    else if (islower(c))
    {
        c = c - 97;
        ci = (c + n) % 26;
        ci = ci + 97;
    }
    //If not alpha char...
    else
    {
        ci = c;
    }
    //Return to calling.
    return (char) ci;
}