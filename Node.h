# ifndef _NODE_H
# define _NODE_H

/* Node Class Design:
    Node for characters inside Trie data structure. Each node takes ~125 bytes of memory.

    Each node represents a character (technically redundant with current implementation, but kept
    for simplicity). Each node has the capacity to be a terminal node, meaning it is the final
    character in some word. Each node can also have children for when words terminate later on.

    An array of 26 pointers to other nodes keeps track of what characters can follow the current
    node. children[] is ordered alphabetically (children[0] -> node for 'a'), meaning the index for
    some character, c, can be found with c - 'a'. If children[c - 'a'] == nullptr, then no child
    exists for character c.

    Array of priorities keeps track of what following characters are highest in priority (high to
    low) each item in priorities[] corresponds to the index in children[] (node of priority 0 ->
    children[priorities[0]]). There is one exception to this, where p[i] is 26, indicating what the
    priority, i, of the node being terminal (end of some word) is.
*/

class Node {
    private:
        char character; // character of node
        bool isTerminal; // bool for whether node can be terminal
        Node* children[26]; // array of pointers to subsequent nodes
        unsigned char priority[27]; // array of priority refering to array

    public:
        // constructor with character
        Node(const char c) : character(c), isTerminal(false) {
            // initialize pointer array to nullptr
            for (unsigned int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }

            // initialize priority array
            for (unsigned int i = 0; i < 27; i++) {
                priority[i] = i;
            }
        }

        // adds node to children array
        void addNode(Node* n) {
            // update array with new node
            children[n->character - 'a'] = n;

            // move priority of new node to front
            char curr = priority[0];
            char prev = priority[0];

            // TODO: improve efficiency of setting priority of inserted node
            // move new character to priority 0
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
        char getChar() const {
            return character;
        }

        // returns node where char is located a[char - 'a']
        Node* getNode(char c) const {
            return children[c - 'a'];
        }

        // returns node corresponding to given priority
        Node* getPriority(unsigned char i) const {
            if (priority[i] == 27) {
                // if priority i is node being terminal, return pointer to current node
                return (Node*) this;
            } else {
                // otherwise, return pointer to other node (could be nullptr)
                return children[priority[i]];
            }            
        }
};

# endif