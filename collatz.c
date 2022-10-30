#include <stdio.h>
#include <cs50.h>

int collatz(int n);
int main(void)
{
    int start = get_int("Start: ");
    collatz(start);
}

int collatz(int n)
{
    if (n == 1)
    {
        printf("n: %i\n", n);
        return 0;
    }
    else if (n % 2 == 0)
    {
        printf("n: %i\n", n);
        return 1 + collatz(n / 2);
    }
    else
    {
        printf("n: %i\n", n);
        return 1 + collatz(3 * n + 1);
    }
}