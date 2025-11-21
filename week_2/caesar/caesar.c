#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string text);
char rotate(char c, int n);
int alphabetical_index(char c);

int main(int argc, string argv[])
{
    if (argc != 2 || !only_digits(argv[1])) // Checks if there is only 1 argument besides the program name
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int k = atoi(argv[1]); // Converts the string argument to a integer

    string plaintext = get_string("plaintext: "); // Gets a string to cypher

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char ci = rotate(plaintext[i], k); // Rotates the letters one by one printing them in sequence
        printf("%c", ci);
    }
    printf("\n");

    return 0;

}

bool only_digits(string key)
{
    // Checks if the key received is valid
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isdigit(key[i]) || isspace(key[i]))
        {
            return false;
        }
        else
        {
            continue;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    if (!isalpha(c)) // If the letter is a punctuation, it just returns itself
    {
        return c;
    }
    else
    {
        int ci = (alphabetical_index(c) + n) % 26; // Calculates the formula given by the problem set
        if (isupper(c))
        {
            return ci + 'A'; // If it's uppercase, returns the sum of ci + 65
        }
        else
        {
            return ci + 'a'; // Else returns the sum of ci + 97
        }
    }
}

int alphabetical_index(char c)
{
    if (isupper(c))
    {
        return c - 'A'; // Given a downcase letter, it'll subtract 65 from it to give the alphabetic index
    }
    else if (islower(c))
    {
        return c - 'a'; // Given a downcase letter, it'll subtract 97 from it
    }
    else
    {
        return -1; // It'll go to the else statement, but the compiler requires the function to return something at every situation
    }
}
