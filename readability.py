from cs50 import get_string

def main():
    # Declare variables (don't need to specify type)
    # letters = 0
    # words = 0
    # sentences = 0

    # Prompt user for text
    text = get_string("Text: ")

    # Calculate number of letters, words, and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    print(str(letters) + " " + str(words) + " " + str(sentences))

    # Coleman-Liau formula
    L = letters / words * 100
    S = sentences / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    # Print reading level
    if (index >= 1 and index < 16):
        print(f"Grade {int(round(index))}")
    elif (index < 1):
        print("Before Grade 1")
    else:
        print("Grade 16+")

def count_letters(text):
    letters = 0
    for i in text:
        # if string.isalpha(text(i)):
        if i.isalpha():
            letters += 1
    return letters

def count_words(text):
    words = 1
    for i in text:
        # if string.isspace(text(i)):
        if i.isspace():
            words += 1
    return words

def count_sentences(text):
    sentences = 0
    for i in text:
        if (i == "." or i == "!" or i == "?"):
            sentences += 1
    return sentences

if __name__ == "__main__":
    main()