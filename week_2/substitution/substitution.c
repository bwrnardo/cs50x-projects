#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_letters(string text);
bool has_duplicates(string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    string key = argv[1];
    int n = strlen(key);

    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    if (!only_letters(key))
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }

    if (has_duplicates(key))
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        key[i] = toupper(key[i]);
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        char c = plaintext[i];
        if (isalpha(c))
        {
            int index = toupper(c) - 'A';

            char mapped_char = key[index];

            if (islower(c))
            {
                printf("%c", tolower(mapped_char));
            }
            else
            {
                printf("%c", mapped_char);
            }
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
    return 0;
}

bool only_letters(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }
    return true;
}

bool has_duplicates(string key)
{
    int n = strlen(key);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                return true;
            }
        }
    }
    return false;
}
