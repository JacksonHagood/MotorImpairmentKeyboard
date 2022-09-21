# ifndef _NODE_H
# define _NODE_H

/* Node Class Design:

    Each node represents a character, c (technically redundant, but kept for simplicity). Each node
    has the capacity to be a terminal node, meaning it is the final character in some word

    An array of pointers to other nodes keeps track of what characters can follow the current node.
    a[] is ordered alphabetically (a[0] -> 'a', a[25] -> 'z') with a size of 26

    Array of priorities keeps track of what following characters are highest in priority (high to
    low) each item in p[] corresponds to the index in a[] (priority 1 -> a[p[0]]). There is one
    exception to this where p[i] is 26, indicating the priority (i) of the node being terminal (end
    of the word).
*/

class Node {
    private:
        char character; // character of node
        bool isTerminal; // bool for terminal node
        Node* array[26]; // array of pointers to nodes
        unsigned char priority[27]; // array of priority

    public:
        // constructor with character
        Node(const char c) : character(c), isTerminal(false) {
            // initialize pointer array to nullptr
            for (unsigned int i = 0; i < 26; i++) {
                array[i] = nullptr;
            }

            // initialize priority array
            for (unsigned int i = 0; i < 27; i++) {
                priority[i] = i;
            }
        }

        // 
        void addNode(Node* n) {
            // update array with new node
            array[n->character - 'a'] = n;

            // move priority of new node to front
            char curr = priority[0];
            char prev = priority[0];

            if (priority[0] != n->character - 'a') {
                for (unsigned int i = 1; i < 27; i++) {
                    if (priority[i] == n->character - 'a') {
                        priority[0] = priority[i];
                        priority[i] = prev;
                        break;
                    } else {
                        curr = priority[i];
                        priority[i] = prev;
                        prev = curr;
                    }
                }
            }
        }

        // returns char of node
        char getChar() {
            return character;
        }

        // returns node where char is located a[char - 'a']
        Node* getNode(char c) {
            return array[c - 'a'];
        }

        // returns node corresponding to given priority
        Node* getPriority(unsigned char i) {
            if (priority[i] == 27) {
                // p[i] == 26 -> node being terminal is priority i
                return nullptr;
            } else {
                return array[priority[i]];
            }            
        }
};

# endif