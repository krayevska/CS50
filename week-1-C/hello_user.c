#include <stdio.h>
#include <cs50.h>

// main function is getting user's name as input and saying hello to user as output
int main(void)
{
    string s = get_string("What is your name?\n");
    printf("hello, %s\n", s);
}