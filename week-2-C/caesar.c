#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{
    //checking if user gives na arg - key for cipher
    if (argc == 2)
    {
        //checking if key is number
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }    
        }
        //converting key to int
        int k = atoi(argv[1]);
        //prompting for plain text
        string s = get_string("plaintext: ");
        //printing ciphered text char by char
        printf("ciphertext: ");
        for (int j = 0, n = strlen(s); j < n; j++)
        {
            if (islower(s[j]))
            {
                printf("%c", (((s[j] + k) - 97) % 26) + 97);        
            }    
            else if (isupper(s[j]))
            {
                printf("%c", (((s[j] + k) - 65) % 26) + 65);   
            }  
            //if it's not a letter, just print it as it is
            else
            {
                printf("%c", s[j]);    
            }
        }    
        printf("\n");
    }
    //if users gives no or more than 1 key
    else
    {
        printf("Usage: ./caesar key");
        return 1;
    }
}
