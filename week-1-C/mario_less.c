#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // getting user input - height of tower 
    int h;
    do
    {
        h = get_int("What is the height of your tower?");
    }
    while (h < 1 || h > 8);
    // iteretion down over rows, i - number of rows
    for (int i = 0; i < h; i++)
    {
        // iteretion to make one row. h - row length, i in this loop is number of #
        for (int j = 0; j < h; j++)
        {
            // print " " or # depends on indexes of both loops and height of tower
            if (j < h - i - 1) 
            {
                printf(" "); 
            }
            else 
            {
                printf("#");
            }
        }
        // ends the line
        printf("\n");          
    }
}
