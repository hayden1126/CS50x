# TODO
while True:
    card = input("Number: ")
    if card.isnumeric() and int(card) >= 0:
        break

sum = 0
for i in range(len(card)):
    digit = int(card[i])
    if len(card) % 2 == 0:
        if i % 2 == 0:
            digit = digit * 2
            if digit > 9:
                sum += int(str(digit)[0]) + int(str(digit)[1])
            else:
                sum += digit
        else:
            sum += digit
    else:
        if i % 2 == 1:
            digit = digit * 2
            if digit > 9:
                sum += int(str(digit)[0]) + int(str(digit)[1])
            else:
                sum += digit
        else:
            sum += digit

if sum % 10 != 0:
    print("INVALID")
else:
    length = len(card)
    if length == 15 and card[:2] in ["34", "37"]:
        print("AMEX")
    elif length == 16 and card[:2] in ["51", "52", "53", "54", "55"]:
        print("MASTERCARD")
    elif (length == 13 or length == 16) and card.startswith("4"):
        print("VISA")
    else:
        print("INVALID")