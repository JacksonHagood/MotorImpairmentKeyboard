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
            // add 26 root nodes
            for (unsigned int i = 0; i < 26; i++) {
                root[i] = new Node(i + 'a');
            }

            // open dictionary
            std::ifstream input(fileName);
            std::string word;

            // iterate through dictionary
            while (input >> word) {
                Node* currNode = root[word.at(0) - 'a'];

                for (unsigned int i = 1; i < word.size(); i++) {
                    if (currNode->getNode(word.at(i)) == nullptr) {
                        // insert node
                        Node* newNode = new Node(word.at(i));
                        currNode->addNode(newNode);
                    }

                    // iterate
                    currNode = currNode->getNode(word.at(i));
                }
                
                currNode->setTerminal();

            }
        }

        // TODO: copy constructor
        Trie(const Trie& other) {

        }

        // TODO: copy assignment operator
        Trie& operator=(const Trie& other) {
            return *this;
        }

        // TODO: destructor
        ~Trie() {

        }

        // TODO: gets a candidate of priority i for the partial word
        std::string getCandidate(std::string partial, unsigned int i) {
            return "";
        }
};

# endif