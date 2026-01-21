def get_change():
    while True:
        try:
            change = float(input("Change: "))
            if change > 0:
                return change
        except ValueError:
            pass

change_owed = get_change()
change_owed *= 100

quarters = change_owed // 25
change_owed -= (25 * quarters)

dimes = change_owed // 10
change_owed -= (10 * dimes)

nickels = change_owed // 5
change_owed -= (5 * nickels)

change = quarters + dimes + nickels + change_owed

print(int(change))
