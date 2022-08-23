# TODO
while True:
    height = input("Height: ")
    if height.isnumeric() and int(height) > 0 and int(height) < 9:
        break
height = int(height)
for i in range(1, height + 1):
    print(f"{' ' * (height - i)}{'#' * i}  {'#' * i}")