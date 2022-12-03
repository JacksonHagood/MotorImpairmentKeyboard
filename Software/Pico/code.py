import board
import digitalio
import time
import usb_hid
import sys
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode as k



KEY_MASK = 0xFF00
SPECIAL_MASK = 0x00FF

CTRL = 0x8000
ALT = 0x4000
SHIFT = 0x2000
WIN = 0x1000
RELEASE = 0x0800

CTRL_PRESS = 73
ALT_PRESS = 74
SHIFT_PRESS = 75
WIN_PRESS = 76


CTRL_ALT_DEL = 0xC033

KEY = 0x00FF
SPECIAL = 0xFF00

WIDTH = 16
HEIGHT = 5

N_1 = 1
N_2 = 2
N_3 = 3
N_4 = 4
N_5 = 5
N_6 = 6
N_7 = 7
N_8 = 8
N_9 = 9

A = ord('a') - 87
B = ord('b') - 87
C = ord('c') - 87
D = ord('d') - 87
E = ord('e') - 87
F = ord('f') - 87
G = ord('g') - 87
H = ord('h') - 87
I = ord('i') - 87
J = ord('j') - 87
K = ord('k') - 87
L = ord('l') - 87
M = ord('m') - 87
N = ord('n') - 87
O = ord('o') - 87
P = ord('p') - 87
Q = ord('q') - 87
R = ord('r') - 87
S = ord('s') - 87
T = ord('t') - 87
U = ord('u') - 87
V = ord('v') - 87
W = ord('w') - 87
X = ord('x') - 87
Y = ord('y') - 87
Z = ord('z') - 87

BACK_TICK = 36
MINUS = 37
EQUALS = 38
OPEN_SQ = 39
CLOSE_SQ = 40
BACK_SLASH = 41
SEMICOLON = 42
APOSTROPHE = 43
COMMA = 44
PERIOD = 45
FWD_SLASH = 46

SPACE = 47
TAB = 48
ENTER = 49
BACKSPACE = 50
DELETE = 51
ESC = 52
CAPS = 53

F1 = 54
F2 = 55
F3 = 56
F4 = 57
F5 = 58
F6 = 59
F7 = 60
F8 = 61
F9 = 62
F10 = 63
F11 = 64
F12 = 65

UP = 66
DOWN = 67
LEFT = 68
RIGHT = 69

M1 = 70
M2 = 71
M3 = 72


EQUALS = 38
SPACE = 47
BACKSPACE = 50

#pressed = {}

keyboard = Keyboard(usb_hid.devices)


#uart0 = UART(0, baudrate=9600, tx=Pin(12), rx=Pin(13))

#interrupt = Pin(15, Pin.OUT, Pin.PULL_DOWN)
interrupt = digitalio.DigitalInOut(board.GP15)
interrupt.direction = digitalio.Direction.OUTPUT


"""
MENA_MAP0 = [
    [[k.V], [k.A], [k.L]],
    [[k.E], [k.R], [k.I]],
    [[k.SEMICOLON], [k.SHIFT, k.ZERO], [k.BACKSPACE]],
    [[k.EQUALS], [k.SHIFT, k.D], [k.SPACE]]
]
"""
MENA_MAP = [
    [CTRL, ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, DELETE, M1],
    [WIN, BACK_TICK, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, MINUS, EQUALS, BACKSPACE, M2],
    [ALT, TAB, Q, W, E, R, T, Y, U, I, O, P, OPEN_SQ, CLOSE_SQ, BACK_SLASH, M3],
    [SPACE, CAPS, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER, UP, CTRL],
    [ALT, SHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, FWD_SLASH, SHIFT, LEFT, DOWN, RIGHT]
]

PRESS_MAP = [
    [CTRL, ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, DELETE, M1],
    [WIN, BACK_TICK, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, MINUS, EQUALS, BACKSPACE, M2],
    [ALT, TAB, Q, W, E, R, T, Y, U, I, O, P, OPEN_SQ, CLOSE_SQ, BACK_SLASH, M3],
    [SPACE, CAPS, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER, UP, CTRL],
    [ALT, SHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, FWD_SLASH, SHIFT, LEFT, DOWN, RIGHT]
]
"""

MENA_MAP = [
    [[k.V], [k.A], [k.L], [k.E]],
    [[k.R], [k.I], [k.SEMICOLON], [k.EIGHT]],
    [[k.S], [k.EQUALS], [k.SHIFT, k.D], [k.SPACE]]
]
"""
R4 = digitalio.DigitalInOut(board.GP17)
R4.direction = digitalio.Direction.INPUT
R4.pull = digitalio.Pull.DOWN

R3 = digitalio.DigitalInOut(board.GP18)
R3.direction = digitalio.Direction.INPUT
R3.pull = digitalio.Pull.DOWN

R2 = digitalio.DigitalInOut(board.GP19)
R2.direction = digitalio.Direction.INPUT
R2.pull = digitalio.Pull.DOWN

R1 = digitalio.DigitalInOut(board.GP20)
R1.direction = digitalio.Direction.INPUT
R1.pull = digitalio.Pull.DOWN

R0 = digitalio.DigitalInOut(board.GP21)
R0.direction = digitalio.Direction.INPUT
R0.pull = digitalio.Pull.DOWN


C3 = digitalio.DigitalInOut(board.GP10)
C3.direction = digitalio.Direction.OUTPUT
C2 = digitalio.DigitalInOut(board.GP11)
C2.direction = digitalio.Direction.OUTPUT
C1 = digitalio.DigitalInOut(board.GP12)
C1.direction = digitalio.Direction.OUTPUT
C0 = digitalio.DigitalInOut(board.GP13)
C0.direction = digitalio.Direction.OUTPUT

cols = [C0, C1, C2, C3]
rows = [R0, R1, R2, R3, R4]



def int_2_mena(num):
    #num = 0x200A
    mena = hex(num)
    
    mena = mena[2:].upper()

    while len(mena) < 4:
        mena = '0' + mena
    sys.stdout.write(mena + "\n")
    #print(mena)
    """
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
        #print(character)
        keyboard.press(lookup[character])
        keyboard.release(lookup[character])

    keyboard.press(k.ENTER)
    keyboard.release(k.ENTER)"""

def power_col(col):
    for i in range(len(cols)):
        if (col % 2 == 1):
            cols[i].value = True
        else:
            cols[i].value = False
        col = col // 2 # <- many tears were had

def power_off_col():
    for i in range(len(cols)):
        cols[i].value = False

prev_mena = -1
hold_count = 0

cont = True
while cont:

    mena = 0x0080
    out = False
    for i in range(WIDTH):
        power_col(i)
        #cols[i].value = True
        press = 0 
        for j in range(HEIGHT):
            
            if (rows[j].value and mena != CTRL_ALT_DEL):
                out = True
                #print("Press")
                
                press = MENA_MAP[j][i]
                #print(mena)
                if (press <= KEY):
                    #print("MASKING", hex(mena))
                    mena &= KEY_MASK
                    #print("MASKED", hex(mena))
                
                #print("Press:", hex(press))
                mena |= press
                
                
                if ((mena & SPECIAL_MASK) != 0x0080):
                    #print("\t" + str(hex(mena)))
                    mena &= 0xFF7F
                    #print("\t" + str(hex(mena)))
                
                
                """
                #uart0.write(bytes(mena_val, 'utf-8'))
                """
                
                
                #sys.stdout.write("a")
                
                """
                for key in c:
                    keyboard.press(key)
                """
                """
                
                keyboard.press(k.ZERO)
                keyboard.release(k.ZERO)
                keyboard.press(k.ZERO)
                keyboard.release(k.ZERO)
                keyboard.press(k.ZERO)
                keyboard.release(k.ZERO)
                keyboard.press(k.A)
                keyboard003a
                003a
                003a
                .release(k.A)
                keyboard.press(k.ENTER)
                keyboard.release(k.ENTER)
                
                
                
                for key i003b
                003b
                n c:
                    keyboard.release(key)
                """
                #time.sleep(0.008)
            
            
            time.sleep(0.0002)
        #power_off_col()
    if (prev_mena != mena):
        prev_mena = mena
        hold_count = 0
    hold_count += 1
    if (out):
        interrupt.value = True
        time.sleep(0.01)
        if (hold_count == 1 or hold_count >= 24 and hold_count % 4 == 0):
            int_2_mena(mena)
            out = False
        interrupt.value = False
        
   