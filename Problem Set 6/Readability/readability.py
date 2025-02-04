from cs50 import get_string
import re


def main():
    # Get input from the user
    text = get_string("Text: ")

    # Count the number of letters, words, and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Compute the Coleman-Liau index
    index = round(0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8)

    # Determine the readability level
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    """Count the number of letters (only alphabetic characters)"""
    return sum(1 for char in text if char.isalpha())


def count_words(text):
    """Count the number of words (each space-separated sequence is considered a word)"""
    return len(text.split())


def count_sentences(text):
    """Count the number of sentences (ends with '.', '!', or '?')"""
    return len(re.findall(r'[.!?]', text))


if __name__ == "__main__":
    main()
