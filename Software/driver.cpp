# include "Node.h"
# include "Trie.h"
# include <iostream>

// global trie instance
Trie z("dictionary.txt");

// global string buffer
std::string partial = "";

// auto-complete suggestions
std::string suggestions[3] = {"", "", ""};

// input variable
unsigned short input;

void sendKeystroke() {
    std::cout << "\n\tKEYSTROKE:  ";

    // determine special key presses
    if (input & 0x8000) {
        std::cout << "CTRL + ";
    }
    if (input & 0x4000) {
        std::cout << "ALT + ";
    }
    if (input & 0x2000) {
        std::cout << "SHIFT + ";
    }
    if (input & 0x1000) {
        std::cout << "WIN + ";
    }

    unsigned short key = input & 0x00FF;

    // determine character key
    switch (key) {
        case 0 ... 9:
            std::cout << (input & key) << '\n';
            break;
        case 10 ... 35:
            std::cout << (char) (key + 87) << '\n';
            break;
        case 36:
            std::cout << "`\n";
            break;
        case 37:
            std::cout << "-\n";
            break;
        case 38:
            std::cout << "=\n";
            break;
        case 39:
            std::cout << "[\n";
            break;
        case 40:
            std::cout << "]\n";
            break;
        case 41:
            std::cout << "\\\n";
            break;
        case 42:
            std::cout << ";\n";
            break;
        case 43:
            std::cout << "\'\n";
            break;
        case 44:
            std::cout << "<\n";
            break;
        case 45:
            std::cout << ">\n";
            break;
        case 46:
            std::cout << "/\n";
            break;
        case 47:
            std::cout << "SPACE\n";
            break;
        case 48:
            std::cout << "TAB\n";
            break;
        case 49:
            std::cout << "ENTER\n";
            break;
        case 50:
            std::cout << "BACKSPACE\n";
            break;
        case 51:
            std::cout << "DELETE\n";
            break;
        case 52:
            std::cout << "ESCAPE\n";
            break;
        case 53:
            std::cout << "CAPSLOCK\n";
            break;
        case 54 ... 65:
            std::cout << 'F' << key - 53 << '\n';
            break;
        case 66:
            std::cout << "UP\n";
            break;
        case 67:
            std::cout << "DOWN\n";
            break;
        case 68:
            std::cout << "LEFT\n";
            break;
        case 69:
            std::cout << "RIGHT\n";
            break;
        case 70:
            std::cout << "M1\n";
            break;
        case 71:
            std::cout << "M2\n";
            break;
        case 72:
            std::cout << "M3\n";
            break;
        default:
            std::cout << "INVALID_KEY\n";
    }

    // TODO: send decoded keystroke over USB
    // TODO: send suggestion if M1, M2, or M3 is pressed
}

void updateSuggestions() {
    unsigned short key = input & 0x00FF;

    if (key >= 10 && key <= 35 && !(input & 0xF000)) {
        // case 1:if  alphabetic key is pressed that is not a shortcut, update suggestions
        partial += (char) (key + 87);
        suggestions[0] = "", suggestions[1] = "", suggestions[2] = "";

        z.getCandidates(partial, suggestions);
    } else {
        // case 2: otherwise, reset suggestions
        partial = "";
        suggestions[0] = "", suggestions[1] = "", suggestions[2] = "";
    }

    std::cout << "\n\tPARTIAL:    " << partial << '\n';

    for (unsigned int i = 0; i < 3; i++) {
        if (suggestions[i] == "") {
            std::cout << "\tPRIORITY " << i << ": \033[31mNONE\033[0m\n";
        } else {
            std::cout << "\tPRIORITY " << i << ": \033[33m" << partial << "\033[0m\033[32m" << suggestions[i] << "\033[0m\n";
        }
    }

    std::cout << '\n';

    // TODO: update LCDs with suggestions over GPIO
}

int main() {
    // initialize standard in for hex
    std::cin >> std::hex;
    
    // loop forever
    while (true) {
        // TODO: change to polling over GPIO
        std::cout << "ENTER MENA KEYSTROKE: ";
        std::cin >> input;

        // send keystroke over USB
        sendKeystroke();

        // update auto-complete suggestions
        updateSuggestions();        
    }
}