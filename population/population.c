#include <cs50.h>
#include <stdio.h>

int startSize(void);
int endSize(int a);
int years(int a, int b);

int main(void)
{
    // TODO: Prompt for start size
    int start = startSize();
    
    // TODO: Prompt for end size
    int end = endSize(start);
    
    // TODO: Calculate number of years until we reach threshold
    int year = years(start, end);
    
    // TODO: Print number of years
    printf("Years: %i\n", year);
}

int startSize(void)
{
    int i;
    do
    {
        i = get_int("Enter start size:\n");
    }
    while (i<9);
    return i;
}

int endSize(int a)
{
    int i;
    do
    {
        i = get_int("Enter end size:\n");
    }
    while (i<a);
    return i;
}

int years(int a, int b)
{
    int i = a, year = 0;
    do 
    {
        i = i + i/3 - i/4;
        year++;
    }
    while (i < b);
    return year;
}
