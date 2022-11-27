num = 0x200A
mena = hex(a)

mena = mena[2:].upper()

while len(mena) < 4:
    mena = '0' + mena

print(mena)

lookup = {
    "0": k.ZERO,
    "1": k.ONE,
    "2": k.TWO,
    "3": k.THREE,
    "4": k.FOUR,
    "5": k.FIVE,
    "6": k.SIX,
    "7": k.SEVEN,
    "8": k.EIGHT,
    "9": k.NINE,
    "A": k.A,
    "B": k.B,
    "C": k.C,
    "D": k.D,
    "E": k.E,
    "F": k.F
}

for character in mena:
    print(character)
    keyboard.press(lookup[character])
    keyboard.release(lookup[character])

keyboard.press(k.ENTER)
keyboard.release(k.ENTER)
