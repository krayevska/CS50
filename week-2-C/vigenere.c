#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int shift(char c);

int main(int argc, string argv[])
{
    // checking if user gives na arg - keyword for cipher
    if (argc == 2)
    {
        //checking if key consist of letters
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            //if not
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            } 
        }
        // if it is, getting user input - plain text                
        string s = get_string("plaintext: ");
        
        // getting length of key
        int key_len = strlen(argv[1]);
        int i = 0;
        int j = 0;
        int l = strlen(s);
        printf("ciphertext: ");
        // looping through plaintext word 
        while (i < l)
        {
            int key = shift(argv[1][j]);
            // if it is a letter in plain text - use current key letter to shift 
            if (isalpha(s[i]))
            {
                if (islower(s[i]))
                {
                    printf("%c", (((s[i] + key) - 97) % 26) + 97);        
                }    
                else if (isupper(s[i]))
                {
                    printf("%c", (((s[i] + key) - 65) % 26) + 65);   
                } 
            
                if (j == (key_len - 1))
                {
                    j = 0;
                }
                else
                {
                    j++;     
                }
                    
            }    
            // if it's not a letter, just print it as it is
            else
            {
                printf("%c", s[i]);    
            }
            // increment index in plain text
            i++;
            // increment index in key, if it is last letter go to first again
        }   
        // end of word, so go to next line
        printf("\n");
    }
    //if users gives no or more than 1 key
    else
    {
        printf("Usage: ./caesar key");
        return 1;
    }
}
// function that get a letter from key and return number for shifting
int shift(char c)
{
    char current = toupper(c);
    int shift = current - 65; 
    return shift;
}
