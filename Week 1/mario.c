#include <cs50.h>
#include <stdio.h>

int height;
void construct_stairs(int h);
int main(void)
{
    do
    {
        height = get_int("Height: ");
    }
    while
    (height < 1 || height > 8);

    construct_stairs(height);

}

void construct_stairs(int h)
{
    // for each row
    for (int i = 1; i <= h; i++)
    {
        // prints space
        for (int j = 1; j <= h - i; j++)
        {
            printf(" ");
        }

        // prints blocks
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // prints 2 spaces
        printf("  ");

        // prints remaining blocks
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}