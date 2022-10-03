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
            std::cout << "PRIORITY " << i << ": " << partial << results[i] << '\n';
        }

        std::cout << '\n';
    }

}