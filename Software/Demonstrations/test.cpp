# include "Node.h"
# include "Trie.h"
# include <iostream>

int main() {
    // simple test program for Trie
    Trie z("dictionary.txt");

    while (true) {
        std::string partial;

        std::cout << "ENTER PARTIAL WORD: ";
        std::cin >> partial;

        std::string results[3] = {"", "", ""};
        z.getCandidates(partial, results);

        std::cout << "PARTIAL: " << partial << '\n';

        for (unsigned int i = 0; i < 3; i++) {
            if (results[i] == "") {
                std::cout << "PRIORITY " << i << ": \033[31mNONE\033[0m\n";
            } else {
                std::cout << "PRIORITY " << i << ": \033[33m" << partial << "\033[0m\033[32m" << results[i] << "\033[0m\n";
            }
        }

        std::cout << '\n';
    }

}