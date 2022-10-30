#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        //Prompt user for height.
        h = get_int("What is the height of the pyramid?: ");
    }
    while (h < 1 || h > 8);
    //For rows...
    for (int hashr = 0; hashr < h; hashr++)
    {
        //Print dots or spaces
        for (int dot = 0; dot < h - hashr - 1; dot++)
        {
            printf(" ");
        }
        //Print left hashes
        for (int hashc = 0; hashc <= hashr; hashc++)
        {
            printf("#");
        }
        //Print two spaces
        printf("  ");
        //Print right hashes
        for (int z = 0; z <= hashr; z++)
        {
            printf("#");
        }
        //Move to next row
        printf("\n");
    }
}