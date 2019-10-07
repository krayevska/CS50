#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <ctype.h>
#include <string.h>

void check(string pass, string salt, string hash);

const int ALPHA[52] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,                        81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 97, 98, 99, 100, 101,                          102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,                        115, 116, 117, 118, 119, 120, 121, 122};

int main(int argc, string argv[])
{
    // cheking if user provide 1 argument
    if (argc != 2)
    {
        printf("Error, there should be only one argument.");
        return 1; 
    }
    else
    {
        //getting salt - first and second char of hash
        char salt[3] = {argv[1][0], argv[1][1], '\0'};
        
        // checking all 1 char passwords
        for (int i = 0; i < 52; i++)
        {
            char current[] = {(char)ALPHA[i], '\0'};
            check(current, salt, argv[1]);
        }
        
        // checking all 2 char passwords
        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j < 52; j++)
            {
                char current[] = {(char)ALPHA[i], (char)ALPHA[j], '\0'};
                check(current, salt, argv[1]);
            }    
        }
        
        // checking all 3 char passwords
        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j < 52; j++)
            {
                for (int k = 0; k < 52; k++)
                {    
                    char current[] = {(char)ALPHA[i], (char)ALPHA[j], (char)ALPHA[k], '\0'};
                    check(current, salt, argv[1]);
                }    
            }    
        }  
        
        // checking all 4 char passwords
        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j < 52; j++)
            {
                for (int k = 0; k < 52; k++)
                {   
                    for (int ii = 0; ii < 52; ii++)
                    {
                        char current[] = {(char)ALPHA[i], (char)ALPHA[j], (char)ALPHA[k], (char)ALPHA[ii], '\0'};
                        check(current, salt, argv[1]);
                    }    
                }    
            }  
        }
        
        // checking all 5 char passwords
        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j < 52; j++)
            {
                for (int k = 0; k < 52; k++)
                {   
                    for (int ii = 0; ii < 52; ii++)
                    {
                        for (int jj = 0; jj < 52; jj++)
                        {    
                            char current[] = {(char)ALPHA[i], (char)ALPHA[j], (char)ALPHA[k], (char)ALPHA[ii], (char)ALPHA[jj], '\0'};
                            check(current, salt, argv[1]);
                        }    
                    }    
                }    
            }  
        }
    }
}

// cheking if recived hash == input hash. if it is - print pass
void check(string pass, string salt, string hash)
{
    string result = crypt(pass, salt);
    if (strcmp(result, hash) == 0)
    {
        printf("%s\n", pass);
    }
}
