#include <math.h>
#include <stdbool.h>
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float change;
    int cents;
    int result = 0;
    
    // get user input and convert it to int (to cents)
    do
    {
        change = get_float("What is the change?");
        cents = round(change * 100);
    }
    while (cents < 1);
    
    // if input is valid, find the biggest coin which fits and sbstrct, counting cois  
    while (cents > 0)
    {
        while (cents - 25 > -1)
        {
            cents -= 25;
            result += 1;
        }   
        while (cents - 10 > -1)
        {
            cents -= 10;
            result += 1;
        }
        while (cents - 5 > -1)
        {
            cents -= 5;
            result += 1;
        }
        while (cents - 1 > -1)
        {
            cents -= 1;
            result += 1;
        }
    }  
    printf("%i\n", result);
}
