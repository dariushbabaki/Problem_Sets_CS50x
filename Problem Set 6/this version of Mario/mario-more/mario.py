from cs50 import get_int

# Prompt user for height (must be between 1 and 8)
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# Print the two half-pyramids
for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i + "  " + "#" * i)
