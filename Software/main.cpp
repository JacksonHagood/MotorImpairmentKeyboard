# include "Node.h"
# include "Trie.h"
# include <iostream>

// 16 bit MENA: MENA Encoding Not ASCII
// first 4 bits for special keys and last 8 bits for key press (4 bits unused)

// Special keys
// bit | key
// 0   | ALT
// 1   | CTRL
// 2   | SHIFT
// 3   | WIN

// Key Presses
// char    | key
// 0 - 9   | 0 - 9 
// 10 - 35 | a - z
// 36      | `
// 37      | -
// 38      | =
// 39      | [
// 40      | ]
// 41      | \ 
// 42      | ;
// 43      | '
// 44      | <
// 45      | >
// 46      | /
// 47      | space
// 48      | tab
// 49      | enter
// 50      | backspace
// 51      | delete
// 52      | esc
// 53      | caps
// 54 - 65 | F1 - F12
// 66      | UP
// 67      | DOWN
// 68      | LEFT
// 69      | RIGHT
// 70      | M1
// 71      | M2
// 72      | M3

int main() {
    unsigned short input;

    const unsigned short ctrl = 0x8000;
    const unsigned short alt = 0x4000;
    const unsigned short shift = 0x2000;
    const unsigned short win = 0x1000;

    const unsigned short key = 0x00FF;

    std::cin >> std::hex;

    while (true) {
        std::cin >> input;

        // extract special keys
        {
            if (input & ctrl) {
                std::cout << "CTRL\n";
            }

            if (input & alt) {
                std::cout << "ALT\n";
            }

            if (input & shift) {
                std::cout << "SHIFT\n";
            }

            if (input & win) {
                std::cout << "WIN\n";
            }
        }

        // extract character
        {
            short code = input & key;

            // TODO
        }
    }
}