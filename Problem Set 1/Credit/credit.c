#include <cs50.h>
#include <stdio.h>

bool check_luhn(long number);
void check_card_type(long number);

int main(void)
{
    long card_number = get_long("Number: ");
    
    if (check_luhn(card_number))
    {
        check_card_type(card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool check_luhn(long number)
{
    int sum = 0;
    int digit_count = 0;
    
    while (number > 0)
    {
        int digit = number % 10;

        if (digit_count % 2 == 0)
        {
            sum += digit;
        }
        else
        {
            int double_digit = digit * 2;
            sum += (double_digit / 10) + (double_digit % 10);
        }
        
        number /= 10;
        digit_count++;
    }

    return (sum % 10 == 0);
}

void check_card_type(long number)
{
    int length = 0;
    long first_two_digits = number;
    
    while (first_two_digits >= 100)
    {
        first_two_digits /= 10;
    }

    long first_digit = first_two_digits / 10;
    
    while (number > 0)
    {
        number /= 10;
        length++;
    }
    
    if ((length == 15) && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if ((length == 16) && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && (first_digit == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
