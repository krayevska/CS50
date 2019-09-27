#include <cs50.h>
#include <stdio.h>
// getting tower height 0 < h < 9
int main(void)
{
    int h;
    do
    {
        h = get_int("What is the height of your piramid?");
    }
    while (h < 1 || h > 8);
    // if tower height 0 < h < 9, iteration down over rows, i - number of rows
    for (int i = 0; i < h; i++)
    {
        // iteretion to make first half of one row 
        for (int j = 0; j < h; j++)
        {
            if (j < h - i - 1) 
            {
                printf(" "); 
            }
            else 
            {
                printf("#");
            }
        }
        // add gap
        printf("  ");
           
        //iteretion to make second half of one row 
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");    
        }
        
        // end of line
        printf("\n");
    }
}