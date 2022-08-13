#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

bool check_key(string key);

int main(int argc, string argv[])
{
    printf("%d", argc);
    string key = argv[1];
    printf("%s\n", key);

    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    if (!check_key(key))
    {
        return 1;
    }

    string plain = get_string("plaintext: ");

    // key[text[i]] - 97 || 65    // Depending on lower/upper

    printf("ciphertext: ");

    for (int n = 0; n < strlen(plain); n++)
    {
        char letter = plain[n];
        if (isupper(letter))
        {
            printf("%c", toupper(key[letter - 65]));
        }
        else if (islower(letter))
        {
            printf("%c", tolower(key[(int) letter - 97]));
        }
        else
        {
            printf("%c", letter);
        }
    }
    printf("\n");
}

bool check_key(string k)
{
    if (strlen(k) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    int check[26] = { 0 };

    // Loops through each character in key
    for (int i = 0; i < strlen(k); i++)
    {
        char current_letter = k[i];
        short current_index = tolower(current_letter) - 97;

        if (! isalpha(current_letter))
        {
            printf("Letters must be alphabetical.\n");
            return false;
        }
        else if (check[current_index])
        {
            printf("Letters repeated in key.\n");
            return false;
        }

        check[current_index] = 1;
    }
    return true;
}