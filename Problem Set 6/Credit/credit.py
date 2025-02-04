from cs50 import get_string


def main():
    # Prompt the user for a credit card number
    card_number = get_string("Number: ")

    # Validate the card number using Luhn’s Algorithm
    if not is_valid(card_number):
        print("INVALID")
        return

    # Determine the card type
    card_type = get_card_type(card_number)
    print(card_type)


def is_valid(number):
    """Check if the card number is valid using Luhn’s Algorithm"""
    total = 0
    length = len(number)

    # Ensure all characters are digits
    if not number.isdigit():
        return False

    # Iterate over digits, processing every other one from right to left
    for i in range(length):
        digit = int(number[length - 1 - i])  # Start from the last digit

        # Double every second digit from the right
        if i % 2 == 1:
            digit *= 2
            if digit > 9:
                digit -= 9  # Sum the digits of the product

        total += digit

    # Valid if total sum is a multiple of 10
    return total % 10 == 0


def get_card_type(number):
    """Determine the type of credit card"""
    length = len(number)
    first_two_digits = int(number[:2])
    first_digit = int(number[0])

    # American Express: 15 digits, starts with 34 or 37
    if length == 15 and (first_two_digits == 34 or first_two_digits == 37):
        return "AMEX"

    # MasterCard: 16 digits, starts with 51–55
    if length == 16 and 51 <= first_two_digits <= 55:
        return "MASTERCARD"

    # Visa: 13 or 16 digits, starts with 4
    if (length == 13 or length == 16) and first_digit == 4:
        return "VISA"

    # Otherwise, it's invalid
    return "INVALID"


if __name__ == "__main__":
    main()
