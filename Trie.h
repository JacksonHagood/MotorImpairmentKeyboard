# ifndef _TRIE_H
# define _TRIE_H

# include "Node.h"
# include <string>
# include <fstream>

/* Trie Class Design:
    Trie can be thought of having 26 roots, one for each alphabetic character.
*/

class Trie {
    private:
        Node* root[26];
        
    public:
        // constructor with file name
        Trie(const std::string fileName) {
            // TODO: reads file with fstream and constructs Trie nodes
        }

        // gets a candidate of priority i for the partial word
        std::string getCandidate(std::string partial, unsigned int i) {
            // TODO: gets candidate using nodes for the partial word of priority i
            return "";
        }
};

# endif