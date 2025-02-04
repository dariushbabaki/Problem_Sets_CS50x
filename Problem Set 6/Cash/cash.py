from cs50 import get_float


def main():
    # Prompt the user for a valid non-negative input
    while True:
        try:
            change = get_float("Change owed: ")
            if change >= 0:
                break
        except:
            continue  # If input is invalid (e.g., "foo"), re-prompt

    # Convert dollars to cents
    cents = round(change * 100)

    # Calculate the minimum number of coins
    coins = 0
    for coin in [25, 10, 5, 1]:
        coins += cents // coin  # Number of coins for this denomination
        cents %= coin  # Remaining amount

    # Print the minimum number of coins needed
    print(coins)


if __name__ == "__main__":
    main()
