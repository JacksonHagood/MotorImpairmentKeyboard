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

    TODO: UPDATE
        priority[i] = 26 -> Terminal Priority
        priority[i] = 27 -> No priority
        priority[i] = otherwise ->

        Array of priorities keeps track of what following characters are highest in priority (high to
        low) each item in priorities[] corresponds to the index in children[] (node of priority 0 ->
        children[priorities[0]]). There is one exception to this, where p[i] is 26, indicating what the
        priority, i, of the node being terminal (end of some word) is. Also, if p[i] is 27 then there
        are no more results
*/

class Node {
    private:
        char character; // character of node
        bool isTerminal; // bool for whether node can be terminal
        Node* children[26]; // array of pointers to subsequent nodes
        unsigned char priority[4]; // array of priority values

    public:
        // constructor with character
        Node(const char c) : character(c), isTerminal(false) {
            for (unsigned char i = 0; i < 26; i++) {
                children[i] = nullptr;
            }

            for (unsigned int i = 0; i < 4; i++) {
                priority[i] = 27;
            }
        }

        // adds node to children array
        void addNode(Node* n) {
            // update array with new node
            children[n->character - 'a'] = n;
        }

        // sets terminal to true
        void setTerminal() {
            isTerminal = true;
        }

        // adds item to priority array
        void addPriority(unsigned char n) {
            unsigned char count = 0;

            for (unsigned char i = 0; i < 4; i++) {
                if (priority[i] == 27) {
                    priority[i] = n + count * 28;
                    return;
                } else if (priority[i] == n) {
                    count++;
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

        Node* getNode(unsigned char i) const {
            return children[i];
        }

        // priority array at i
        unsigned char getPriority(unsigned char i) const {
            return priority[i];         
        }
};

# endif