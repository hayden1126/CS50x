#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

float get_index(float letter, float word, float sentence);

int main(void)
{
    string paragraph = get_string("Text: ");
    int letters_count = 0;
    int words_count = 1;
    int sentences_count = 0;

    for (int i = 0; i < strlen(paragraph); i++)
    {
        char letter = paragraph[i];
        char prev_letter = paragraph[i - 1];
        if (isalpha(letter))
        {
            letters_count++;
        }
        if (letter == ' ' && prev_letter != ' ')
        {
            words_count++;
        }
        if ((letter == '.' || letter == '!' || letter == '?') && isalpha(prev_letter))
        {
            sentences_count++;
        }
    }
    float index = get_index(letters_count, words_count, sentences_count);

    if (index < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16.0)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

float get_index(float letter, float word, float sentence)
{
    float in = 0.0588 * letter / (word / 100) - 0.296 * sentence / (word / 100) - 15.8;
    return in;
}