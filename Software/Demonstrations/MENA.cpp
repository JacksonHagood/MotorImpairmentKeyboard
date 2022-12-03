# include "Node.h"
# include "Trie.h"
# include <iostream>

int main() {
    unsigned short input;

    const unsigned short ctrl = 0x8000;
    const unsigned short alt = 0x4000;
    const unsigned short shift = 0x2000;
    const unsigned short win = 0x1000;

    const unsigned short key = 0x00FF;

    std::cin >> std::hex;

    while (true) {
        std::cout << "ENTER MENA KEYSTROKE: ";
        std::cin >> input;

        std::cout << "KEYSTROKE: ";

        // extract special keys
        {
            if (input & ctrl) {
                std::cout << "CTRL + ";
            }

            if (input & alt) {
                std::cout << "ALT + ";
            }

            if (input & shift) {
                std::cout << "SHIFT + ";
            }

            if (input & win) {
                std::cout << "WIN + ";
            }
        }

        // extract character
        {
            short code = input & key;

            switch (input & key) {
                case 0 ... 9:
                    std::cout << code;
                    break;
                case 10 ... 35:
                    std::cout << (char) ((code + 55));
                    break;
                case 36:
                    std::cout << '`';
                    break;
                case 37:
                    std::cout << '-';
                    break;
                case 38:
                    std::cout << '=';
                    break;
                case 39:
                    std::cout << '[';
                    break;
                case 40:
                    std::cout << ']';
                    break;
                case 41:
                    std::cout << '\\';
                    break;
                case 42:
                    std::cout << ';';
                    break;
                case 43:
                    std::cout << '\'';
                    break;
                case 44:
                    std::cout << '<';
                    break;
                case 45:
                    std::cout << '>';
                    break;
                case 46:
                    std::cout << '/';
                    break;
                case 47:
                    std::cout << "SPACE";
                    break;
                case 48:
                    std::cout << "TAB";
                    break;
                case 49:
                    std::cout << "ENTER";
                    break;
                case 50:
                    std::cout << "BACKSPACE";
                    break;
                case 51:
                    std::cout << "DELETE";
                    break;
                case 52:
                    std::cout << "ESCAPE";
                    break;
                case 53:
                    std::cout << "CAPSLOCK";
                    break;
                case 54 ... 65:
                    std::cout << 'F' << code - 53;
                    break;
                case 66:
                    std::cout << "UP";
                    break;
                case 67:
                    std::cout << "DOWN";
                    break;
                case 68:
                    std::cout << "LEFT";
                    break;
                case 69:
                    std::cout << "RIGHT";
                    break;
                case 70:
                    std::cout << "M1";
                    break;
                case 71:
                    std::cout << "M2";
                    break;
                case 72:
                    std::cout << "M3";
                    break;
                default:
                    std::cout << "INVALID_KEY";
            }

            std::cout << "\n\n";
        }
    }
}