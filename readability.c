#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Declare variables.
float letters;
float words = 1;
float sentences;

//Prototype functions.
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int main(void)
{
    //Prompt user for text.
    string text = get_string("Text: ");
    //printf("%s\n", text);
    //Calculate number of letters, words, and sentences.
    count_letters(text);
    //printf("%f letters\n", letters);
    count_words(text);
    //printf("%f words\n", words);
    count_sentences(text);
    //printf("%f sentences\n", sentences);
    //Coleman-Liau formula.
    float L = letters / words * 100;
    //printf("L is %f\n", L);
    float S = sentences / words * 100;
    //printf("S is %f\n", S);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    //printf("Index is %f\n", index);
    //Display reading level.
    if (index >= 1 && index < 16)
    {
        printf("Grade %i\n", (int) round(index));
    }
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
}

//Function definitions for counting letters, words, and sentences.
int count_letters(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if isalpha(text[i])
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if isspace(text[i])
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}