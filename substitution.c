#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//Declare global variables.
string ptext;
char ci;

//Prototype.
bool only_alpha(string s);
bool has_26(string s);
bool has_repeat_chars(string s);
char substitution(char c, string s);
int main(int argc, string argv[])
{
    int i;
    int len;
    //Check valid key. If false, print how-to-use.
    if (argc != 2 || !only_alpha(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Check key length. If false, print error message.
    else if (!has_26(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    //Check if key has each letter exactly one. If false, print error message.
    else if (has_repeat_chars(argv[1]))
    {
        printf("Key must contain each letter exactly once.\n");
        return 1;
    }
    //Prompt for plaintext.
    ptext = get_string("plaintext: ");
    //Setup ciphertext bucket.
    printf("ciphertext: ");
    //Substitution function.
    for (i = 0, len = strlen(ptext); i < len; i++)
    {
        substitution(ptext[i], argv[1]);
        //Print ctext chars in bucket.
        printf("%c", ci);
    }
    printf("\n");
}

bool only_alpha(string s)
{
    int i;
    int len;
    for (i = 0, len = strlen(s); i < len; i ++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}

bool has_26(string s)
{
    int len = strlen(s);
    if (len != 26)
    {
        return false;
    }
    return true;
}

bool has_repeat_chars(string s)
{
    int i;
    int j;
    int len;
    for (i = 0, len = strlen(s); i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (toupper(s[i]) == toupper(s[j]))
            {
                return true;
            }
        }
    }
    return false;
}

char substitution(char c, string s)
{
    int sub;
    //Upper.
    if (isupper(c))
    {
        sub = c - 65;
        ci = toupper(s[sub]);
        return ci;
    }
    //Lower.
    if (islower(c))
    {
        sub = c - 97;
        ci = tolower(s[sub]);
        return ci;
    }
    //Non-alpha.
    ci = c;
    return ci;
}