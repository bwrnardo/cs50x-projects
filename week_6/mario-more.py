
def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                return height
        except ValueError:
            pass


height = get_height()


for i in range(height):
    for _ in range(height - i - 1):
        print(" ", end="")

    for _ in range(i + 1):
        print("#", end="")

    print("  ", end="")

    for _ in range(i + 1):
        print("#", end="")

    print()
