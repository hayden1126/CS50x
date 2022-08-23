import cs50
import re

text = cs50.get_string("Text: ")

word_count = len(text.split())
letter_count = len(re.findall("[a-zA-Z]", text))
sentence_count = len(re.findall("[a-zA-Z]([.?!])", text))
L = letter_count * 100 / word_count
S = sentence_count * 100 / word_count
index = 0.0588 * L - 0.296 * S - 15.8
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")