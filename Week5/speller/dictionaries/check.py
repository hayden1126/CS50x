

# with open("large","r") as file:
#     data = file.read().split("\n")
#     count = 0
#     for word in data:
#         if len(word) < 1:
#             continue
#         if len(word) > 25:
#             print(word)

count = 0
n = 4 # number of characters in word: strlen(word)
char_count = 0 # on which character: i
e = f = 0
let = "abcdefghijklmnopqrstuvwxyz?"
dict = {}
index = 0
hash_loc = [0, 26, 728, 19682, 531440, 14348906]
for a in range(26):
    for b in range(27):
        for c in range(27):
            for d in range(27):
#                 for e in range(27):
#                     for f in range(27):
# + e * pow(27, n - 5) + e * pow(27, n - 6)
                        dict[f"{let[a]}{let[b]}{let[c]}{let[d]}"] = count
                        count += 1
                        # if (a * pow(27, n - 1) + b * pow(27, n - 2) + c * pow(27, n - 3) + d * pow(27, n - 4)) != (count - 1):
                        #     print(False)
            # print(f"{c[i]}: {i}  {c[j]}: {j} {c[k]}: {k}--> {count - 1}   i * 27^2 + j * 27^1 + k = {i * 27 * 27 + j * 27 + k}")

print(f"Number of combinations: {count}")
# print(ord("z".upper()) - ord("A"))
# print("?".isalpha())
test = "aaa?cefas"
letter_index = 0
for x in range(4):
    letter = test[x]
    if letter.isalpha():
        temp = ord(letter.upper()) - ord("A")
    else:
        temp = 26
    # print(temp, n - letter_index - 1, letter_index, n)
    index += (temp * pow(27, n - letter_index - 1))
    letter_index += 1
print(dict[test[:4]], index)

'''
some C stuff for if the load worked using tries not hash tables
        // JUST FOUND OUT THESE ARE FOR TRIES NOT HASH TABLES
        // Set Temp node to be node with first letter
        node *temp_letter_table = &table[hash(word[0])];
        // For each letter starting from 2nd letter (if word is 2+ length), go into correct node in table
        for (int i = 1; i < strlen(word) && i < 6; i++)
        {
            temp_letter_table = *temp_letter_table[hash(word[i])];
        }
        // Set the correct node of that word to be true
        if (temp_letter_table->word == NULL)
        temp_letter_table->word = word;
        temp_letter_table->next = next;
'''

# log: just found out the table[N] hash table only all possibilities of words/combinations with only 6+ characters but not any 5- charactered combinations
'''
Considering 6 characters require 26 x 27^5
then 5 would be 26 x 27^4
so basically the total needed to cover all possible combinations with all lengths from 1 - 6 (6 + words will be stored at 6) is:
(26) + (26 x 27) + (26 x 27^2) + (26 x 27^3) + (26 x 27^4) + (26 x 27^5)


'''
# print((27**5 + 27**4 + 27**3 + 27**2 + 27**1 + 27**0) * 26)
# print(27**5 * 26)

# prev = 0
# for i in range(6):
#     prev += 27**i * 26
#     print(prev, end = ", ")
# print()