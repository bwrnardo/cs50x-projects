def count_letters(text):
    # Return the number of letters in text
    letters = 0
    for i in range(len(text)):
        if text[i].isalpha():
            letters += 1
    return letters


def count_words(text):
    # Return the number of words in text
    words = text.split()
    return len(words)


def count_sentences(text):
    # Return the number of sentences in text
    sentences = 0
    for i in range(len(text)):
        if text[i] in ['!', '?', '.']:
            sentences += 1
    return sentences


def main():
    # Prompt the user for some text
    text = input("Text: ")

    # Count the number of letters, words and sentences in the text
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Compute the Coleman-Liau index
    L = (letters / words) * 100
    S = (sentences / words) * 100
    grade = round(0.0588 * L - 0.296 * S - 15.8)

    # Print the grade level
    if grade in range(1, 16):
        print(f"Grade {grade}")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Before Grade 1")


main()
