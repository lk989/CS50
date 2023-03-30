#include <stdio.h> 
#include <cs50.h>

void draw_pyramid(int a);
int get_height();

int main(void)
{
    int height = get_height();
    draw_pyramid(height);
}

int get_height()
{
    int height;
    do 
    {
        height = get_int("Height: \n");
    }
    while (height < 1 || height > 8);
    return height;
}

void draw_pyramid(int a)
{
    // a loop for each raw
    for (int i = 0; i < a; i++)
    {
        // a loop for spaces in the right
        for (int space = i + 1; space < a; ++space)
        {
            printf(" ");
        }
        // a loop for bricks in the right
        for (int brick = i; brick >= 0; brick--)
        {
            printf("#");
        }
        // print the space inbetween
        printf("  ");
        // a loop for bricks on the left
        for (int brick = i; brick >= 0; brick--)
        {
            printf("#");
        }
        // new line after each raw
        printf("\n");
    }
}
