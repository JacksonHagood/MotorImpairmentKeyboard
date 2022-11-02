#include "Node.h"
#include "Trie.h"
#include "new.h"
#include <iostream>
#include <sstream>

// global trie instance
Trie z("dictionary.txt");

// global string buffer
std::string partial = "";

// auto-complete suggestions
std::string suggestions[3] = {"", "", ""};

// input variable
unsigned short input;

LCDList* l;

void sendKeystroke() {
    std::cout << "\n\tKEYSTROKE:  ";

    unsigned char modifier = 0;

    // determine special key presses
    if (input & 0x8000) {
        std::cout << "CTRL + ";
        modifier |= 0b00000001;
    }
    if (input & 0x4000) {
        std::cout << "ALT + ";
        modifier |= 0b00000100;
    }
    if (input & 0x2000) {
        std::cout << "SHIFT + ";
        modifier |= 0b00100000;
    }
    if (input & 0x1000) {
        std::cout << "WIN + ";
        // TODO
    }

    unsigned short key = input & 0x00FF;
    unsigned char character;

    // determine character key
    switch (key) {
        case 0 ... 9:
            std::cout << (key) << '\n';
            character = 0x27 - (10 - key);
            break;
        case 10 ... 35:
            std::cout << (char)(key + 87) << '\n';
            character = 0x4 + key - 10;
            break;
        case 36:
            std::cout << "`\n";
            character = 0x32;
            break;
        case 37:
            std::cout << "-\n";
            character = 0x2D;
            break;
        case 38:
            std::cout << "=\n";
            character = 0x2E;
            break;
        case 39:
            std::cout << "[\n";
            character = 0x2F;
            break;
        case 40:
            std::cout << "]\n";
            character = 0x30;
            break;
        case 41:
            std::cout << "\\\n";
            character = 0x31;
            break;
        case 42:
            std::cout << ";\n";
            character = 0x33;
            break;
        case 43:
            std::cout << "\'\n";
            character = 0x34;
            break;
        case 44:
            std::cout << "<\n";
            character = 0x36;
            break;
        case 45:
            std::cout << ">\n";
            character = 0x37;
            break;
        case 46:
            std::cout << "/\n";
            character = 0x38;
            break;
        case 47:
            std::cout << "SPACE\n";
            character = 0x2C;
            break;
        case 48:
            std::cout << "TAB\n";
            character = 0x2B;
            break;
        case 49:
            std::cout << "ENTER\n";
            character = 0x28;
            break;
        case 50:
            std::cout << "BACKSPACE\n";
            character = 0x2A;
            break;
        case 51:
            std::cout << "DELETE\n";
            character = 0x4C;
            break;
        case 52:
            std::cout << "ESCAPE\n";
            character = 0x29;
            break;
        case 53:
            std::cout << "CAPSLOCK\n";
            character = 0x39;
            break;
        case 54 ... 65:
            std::cout << 'F' << key - 53 << '\n';
            character = 0x3A + key - 54;
            break;
        case 66:
            std::cout << "UP\n";
            character = 0x52;
            break;
        case 67:
            std::cout << "DOWN\n";
            character = 0x51;
            break;
        case 68:
            std::cout << "LEFT\n";
            character = 0x50;
            break;
        case 69:
            std::cout << "RIGHT\n";
            character = 0x4F;
            break;
        case 70:
            std::cout << "M1\n";
            character = 0xF0;
            break;
        case 71:
            std::cout << "M2\n";
            character = 0xF1;
            break;
        case 72:
            std::cout << "M3\n";
            character = 0xF2;
            break;
        default:
            std::cout << "INVALID_KEY\n";
            return;
    }

    if (character >= 0xF0) {
        // case 1: send auto-complete result
        for (char c : suggestions[character - 0xF0]) {
            std::ostringstream keystroke;
            keystroke << "sudo echo -ne \"\\0\\0\\" << 'x' << std::hex << (int) (c - 97 + 0x4) << std::dec << "\\0\\0\\0\\0\\0\" > /dev/hidg0";
            
            std::cout << "\tSENDING: " << keystroke.str() << '\n';

            system(keystroke.str().c_str());
            system("sudo echo -ne \"\\0\\0\\0\\0\\0\\0\\0\\0\" > /dev/hidg0");
        }
    } else {
        // case 2: send keystroke
        std::ostringstream keystroke;
        keystroke << "sudo echo -ne \"\\";

        if (modifier == 0) {
            keystroke << "0\\0\\";
        } else {
            keystroke << 'x' << std::hex << (int) modifier << std::dec << "\\0\\";
        }

        keystroke << 'x' << std::hex << (int) character << std::dec << "\\0\\0\\0\\0\\0\" > /dev/hidg0";

        std::cout << "\tSENDING: " << keystroke.str() << '\n';

        system(keystroke.str().c_str());

        system("sudo echo -ne \"\\0\\0\\0\\0\\0\\0\\0\\0\" > /dev/hidg0");
    }
    
}

void updateSuggestions(LCDList l) {
    unsigned short key = input & 0x00FF;

    if (key >= 10 && key <= 35 && !(input & 0xF000)) {
        // case 1: if  alphabetic key is pressed that is not a shortcut, update suggestions
        partial += (char)(key + 87);
        suggestions[0] = "", suggestions[1] = "", suggestions[2] = "";

        z.getCandidates(partial, suggestions);
    } else {
        // case 2: otherwise, reset suggestions
        partial = "";
        suggestions[0] = "", suggestions[1] = "", suggestions[2] = "";
    }

    std::cout << "\n\tPARTIAL:    " << partial << '\n';

    std::string completeSuggestions[3] = {"", "", ""};
    for (unsigned int i = 0; i < 3; i++) {
        if (suggestions[i] == "") {
            std::cout << "\tPRIORITY " << i << ": \033[31mNONE\033[0m\n";
        } else {
            std::cout << "\tPRIORITY " << i << ": \033[33m" << partial << "\033[0m\033[32m" << suggestions[i] << "\033[0m\n";
            completeSuggestions[i] = partial + suggestions[i];
        }
    }

    std::cout << '\n';

    // TODO: update LCDs with suggestions over GPIO

    l.suggest(completeSuggestions);
}

void interrupt (void) {
    // TODO: get input from interrupt signal (MENA)
    input = 0x000A;

    // send keystroke over USB
    sendKeystroke();

    // update auto-complete suggestions
    updateSuggestions(*l);
}

int main() {
    //create vector of i2c addresses
    std::vector<int> addrs{0x26,0x25};

    l = new LCDList(addrs);
    l->clear();

    // initialize standard in for hex
    std::cin >> std::hex;

    wiringPiSetup();
    wiringPiSetupGpio();

    // enable interrupts for pin 40 (GPIO 21)
    wiringPiISR(21, INT_EDGE_RISING, &interrupt);

    // loop forever
    while (true);
}