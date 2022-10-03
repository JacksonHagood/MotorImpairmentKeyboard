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
    must be in priority order). Current dictionary requires 23965 nodes (~2.5 MB).

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
                // start at root
                Node* currNode = root[word.at(0) - 'a'];

                // iterate through characters
                for (unsigned int i = 1; i < word.size(); i++) {
                    if (currNode->getNode(word.at(i)) == nullptr) {
                        // insert node if none exists
                        Node* newNode = new Node(word.at(i));
                        currNode->addNode(newNode);
                    }

                    // if there is an empty spot in the priority array,
                    if (currNode->getPriority(3) == 27) {
                        // add character to priority array
                        currNode->addPriority(word.at(i) - 'a');
                    }

                    // iterate
                    currNode = currNode->getNode(word.at(i));
                }
                
                // set final node to terminal
                currNode->setTerminal();

                // if there is an empty spot in the priority array,
                if (currNode->getPriority(3) == 27) {
                    // add terminal to priority array
                    currNode->addPriority(26);
                }
            }
        }

        // gets three candidates for the partial word
        int getCandidates(std::string partial, std::string candidates[3]) {
            // start at root
            Node* currNode = root[partial.at(0) - 'a'];

            // iterate through known nodes
            for (unsigned int i = 1; i < partial.size(); i++) {
                // avoid dereferencing nullptr (no such word exists)
                if (currNode->getNode(partial.at(i)) == nullptr) {
                    return 0;
                }

                // iterate
                currNode = currNode->getNode(partial.at(i));
            }

            // set root to last known node
            Node* root = currNode;

            // counter for number of found candidates
            unsigned char found = 0;

            // iterate a maximum of four times (3 candidates + 1 if isTerminal root)
            for (unsigned char i = 0; i < 4 && found < 3; i++) {
                // if no more priorities exist, terminate
                if (root->getPriority(i) == 27) {
                    return 0;
                }

                // set to to root
                currNode = root;

                // current priority and next priority iterators
                unsigned char currPriority = i;
                unsigned char nextPriority;

                // candidate string
                std::string candidate = "";

                // iterate until terminal node
                while (currNode->getPriority(currPriority) != 26) {
                    // obtain next priority from node
                    nextPriority = currNode->getPriority(currPriority) / 28;

                    // iterate using priority
                    currNode = currNode->getNode((unsigned char) (currNode->getPriority(currPriority) % 28));
                    
                    // set current priority
                    currPriority = nextPriority;

                    // add to candidate
                    candidate += currNode->getChar();
                }

                // if candidate found, add to candidate array
                if (candidate != "") {
                    candidates[found++] = candidate;
                }
            }

            return 1;
        }
};

# endif