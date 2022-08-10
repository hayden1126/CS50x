#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool check_sum(long int card_int, int len);
string check_type(long int card_int, int len);

int main(void)
{
    long int card_number = get_long("Number: ");
    int length = log10(card_number) + 1;
    printf("Length: %i\n", length);
    bool check = check_sum(card_number, length);
    if (check)
    {
        printf("%s", check_type(card_number, length));
    }
    else
    {
        printf("INVALID\n");
    }
}



bool check_sum(long int card_int, int len)
{
    // long int card_int = card_num;
    int sum = 0;

    // for loop to get 10^i
    for (int i = 1; i <= len; i++)
    {
        if (i % 2 == 0)
        {
            long int a = pow(10, i);
            int add = 2 * round((card_int % a) / (a / 10));
            sum += add % 10 + (add % 100) / 10;
        }
        else
        {
            long int b = pow(10, i);
            int add = round((card_int % b) / (b / 10));
            sum += add;
        }
    }
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string check_type(long int card_int, int len)
{
    int first_digit = card_int / (long) pow(10, len - 1);
    int digits = card_int / (long) pow(10, len - 2);
    if ((digits == 34 || digits == 37) && len == 15)
    {
        return "AMEX\n";
    }
    else if ((digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55) && len == 16)
    {
        return "MASTERCARD\n";
    }
    else if ((len == 13 || len == 16) && first_digit == 4)
    {
        return "VISA\n";
    }
    else
    {
        return "INVALID\n";
    }
}