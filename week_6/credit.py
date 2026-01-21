card = int(input("Number: "))
copy = card
position_counter = 1
digit_count = 0
total_sum = 0

while card > 0:
    digit_count += 1
    digit = card % 10

    if position_counter % 2 == 1:
        total_sum += digit
    else:
        digit *= 2

        if digit >= 10:
            total_sum += digit % 10
            total_sum += digit // 10
        else:
            total_sum += digit

    card = card // 10
    position_counter += 1

if total_sum % 10 == 0:
    while copy > 100:
        copy //= 10
    if (copy == 37 or copy == 34) and digit_count == 15:
        print("AMEX")
    elif (digit_count == 13 or digit_count == 16) and (copy >= 40 and copy <= 49):
        print("VISA")
    elif (copy >= 51 and copy <= 55) and digit_count == 16:
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")
