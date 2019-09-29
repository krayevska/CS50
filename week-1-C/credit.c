#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    string name;
    long long number = get_long("Please enter your card number\n");
    // getting number of digits in card number
    int number_lengh = (int)(log10(number) + 1);
    // creating arrey with length of number_lengh
    int arrayOfNum[number_lengh];
    string answer = "";
    
    // excluding numbers with wrong length
    if (number_lengh != 13 && number_lengh != 15 && number_lengh != 16)
    {
        printf("INVALID\n");
    }
    // if length is correct
    else
    {
        // filling array with separate digits from input
        int count = 0;
        while (number != 0)
        {
            arrayOfNum[count] = number % 10;
            number /= 10;
            count++;
        }
     
        // getting sum according to Luhn’s algorithm
        int sum2 = 0;
        for (int i = 0; i < number_lengh; i++)
        {
            if (i == 0 || i % 2 == 0)
            {
                sum2 += arrayOfNum[i];    
            }
            else 
            {
                int current = arrayOfNum[i] * 2;
                if (current > 9)
                {
                    sum2 = sum2 + current % 10 + (current - current % 10) / 10;
                }
                else 
                {
                    sum2 += current;
                }
            }
        }
        
        int two_first_dig = arrayOfNum[number_lengh - 1] * 10 + arrayOfNum[number_lengh - 2];
        // cheking type of card
        if (two_first_dig == 34 || two_first_dig == 37)
        {
            answer = "AMEX";    
        }
        else if (two_first_dig > 50 && two_first_dig < 56)
        {
            answer = "MASTERCARD"; 
        }
        else if (arrayOfNum[number_lengh - 1] == 4)
        {
            answer = "VISA"; 
        }
        else
        {
            answer = "INVALID";
        }
    
        // printing result
        if (sum2 % 10 == 0)
        {
            printf("%s\n", answer);    
        }
        else
        {
            printf("INVALID\n");
        }
    }    
}
