# ifndef _TRIE_H
# define _TRIE_H

# include "Node.h"

# include <vector>
# include <string>
# include <iostream>
# include <fstream>

/* Trie Class Design:
    Trie can be thought of having 26 roots, one for each alphabetic character. Trie is constructed
    using a dictionary file. This constructor creates nodes as needed and sets priority (dictionary
    must be in priority order).

    To find candidates, Trie is first traversed to find the final known node (or see if no such
    word exists). Then, candidates are found using the priority arrays present in each of the
    nodes.
*/

class Trie {
    private:
        Node* root[26];
        
    public:
        // TODO: copy constructor
        Trie(const Trie& other) {
            // TODO: implement
        }

        // copy assignment operator
        Trie& operator=(const Trie& other) {
            // TODO: implement

            return *this;
        }

        // destructor
        ~Trie() {
            // TODO: traverse tree and delete nodes
        }

        // constructor with file name
        Trie(const std::string fileName) {
            // initialize 26 root nodes
            for (unsigned int i = 0; i < 26; i++) {
                root[i] = new Node(i + 'a');
            }

            // open dictionary file
            std::ifstream input(fileName);
            std::string word;

            // iterate through dictionary
            while (input >> word) {
                Node* currNode = root[word.at(0) - 'a'];

                // iterate through characters
                for (unsigned int i = 1; i < word.size(); i++) {
                    if (currNode->getNode(word.at(i)) == nullptr) {
                        // insert node if none exists
                        Node* newNode = new Node(word.at(i));
                        currNode->addNode(newNode);
                    }

                    if (currNode->getPriority(3) == 27) {
                        currNode->addPriority(word.at(i) - 'a');
                    }

                    currNode = currNode->getNode(word.at(i));
                }
                
                currNode->setTerminal();

                if (currNode->getPriority(3) == 27) {
                    currNode->addPriority(26);
                }
            }
        }

        // TODO: gets a candidate of priority i for the partial word
        int getCandidates(std::string partial, std::string candidates[3]) {
            Node* currNode = root[partial.at(0) - 'a'];

            for (unsigned int i = 1; i < partial.size(); i++) {
                // avoid dereferencing nullptr (no such word exists)
                if (currNode->getNode(partial.at(i)) == nullptr) {
                    return 0;
                }

                // iterate through nodes to get final character node
                currNode = currNode->getNode(partial.at(i));
            }

            // TODO: use currNode to determine three auto-complete candidates using priority arrays in nodes

            Node* root = currNode;
            unsigned char found = 0;

            for (unsigned char i = 0; i < 4; i++) {
                if (root->getPriority(i) == 27) {
                    return 0;
                }

                currNode = root;
                unsigned char currPriority = i;
                unsigned char nextPriority;
                std::string candidate = "";

                while (true) {
                    nextPriority = currNode->getPriority(currPriority) / 28;

                    if (currNode->getPriority(currPriority) == 26) {
                        break;
                    }

                    currNode = currNode->getNode(currNode->getPriority(currPriority));
                    currPriority = nextPriority;
                    candidate += currNode->getChar();
                }

                if (candidate != "") {
                    candidates[found++] = candidate;
                }
            }

            return 1;
        }
};

# endif