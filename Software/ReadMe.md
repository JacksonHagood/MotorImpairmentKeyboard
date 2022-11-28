# Software

## Usage

Use the Makefile to create one of three programs. Driver program is for actual development. Other
programs demonstrate specific features.

## Prerequisites
Install Wiring

### Driver Program Commands
- Compile: make driver
- Execute: ./driver

### Auto-complete Test Program Commands
- Compile: make test
- Execute: ./test

### MENA Test Program Commands
- Compile: make MENA
- Execute: ./MENA

### clean
- Clean: make clean

## MENA

MENA uses 2 byte hex numbers (unsigned short). First 4 bits for defining special keys. Remaining
bits for the character keys

### Special keys:
| bit | key   |
|-----|-------|
| 0   | ALT   |
| 1   | CTRL  |
| 2   | SHIFT |
| 3   | WIN   |

### Character keys:
| char    | key         |
|---------|-------------|
| 0 - 9   | 0 - 9       |
| 10 - 35 | a - z       |
| 36      | `           |
| 37      | -           |
| 38      | =           |
| 39      | [           |
| 40      | ]           |
| 41      | \           |
| 42      | ;           |
| 43      | '           |
| 44      | <           |
| 45      | >           |
| 46      | /           |
| 47      | SPACE       |
| 48      | TAB         |
| 49      | ENTER       |
| 50      | BACKSPACE   |
| 51      | DELETE      |
| 52      | ESC         |
| 53      | CAPS        |
| 54 - 65 | F1 - F12    |
| 66      | UP          |
| 67      | DOWN        |
| 68      | LEFT        |
| 69      | RIGHT       |
| 70      | M1          |
| 71      | M2          |
| 72      | M3          |
| other   | INVALID_KEY |

### Examples:
- 0x100A: WIN + a
- 0xFFFF: CTRL + ALT + SHIFT + WIN + INVALID_KEY
- 0x2002: SHIFT + 2
- 0x000F: f