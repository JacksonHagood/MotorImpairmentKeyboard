# include "Node.h"
# include "Trie.h"
# include <iostream>

int main() {
    // simple test program for Trie
    Trie z("dictionary.txt");

    std::string partial = "he";
    std::cout << "PARTIAL: " << partial << '\n';

    std::string results[3] = {"", "", ""};
    z.getCandidates(partial, results);

    for (unsigned int i = 0; i < 3; i++) {
        std::cout << "PRIORITY " << i << ": " << results[i] << '\n';
    }
}