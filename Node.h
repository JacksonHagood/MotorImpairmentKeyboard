# ifndef _NODE_H
# define _NODE_H

/* Node Class Design:
    Node for characters inside Trie data structure. Each node takes ~110 bytes of memory (assuming
    Node* is 4 bytes).

    Each node represents a character (technically redundant with current implementation, but kept
    for simplicity). Each node has the capacity to be a terminal node (also technically redundant),
    meaning it is the final character in some word. Each node has children for when words terminate
    later on.

    An array of 26 pointers to other nodes keeps track of what characters can follow the current
    node. children[] is ordered alphabetically (children[0] -> node for 'a'), meaning the index for
    some character, c, can be found with c - 'a'. If children[c - 'a'] == nullptr, then no child
    exists for character c.

    priority array keeps track of the top 4 children (3 + 1 if itself is one of them). The values of
    the priority array correspond to indeces in the children array. That is, if priority[i] = 1,
    then children[1] is of priority i. If priority[i] is 26, then i is the priority of the node
    being terminal. If priority[i] is 27, then there is no child for priority i.
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
            // initialize children array
            for (unsigned char i = 0; i < 26; i++) {
                children[i] = nullptr;
            }

            // initialize priority array
            for (unsigned int i = 0; i < 4; i++) {
                priority[i] = 27;
            }
        }

        // adds node to children array
        void addNode(Node* n) {
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
                    // wherever priority[i] is available, set value (priority[i] % 28 = index in
                    // children, priority[i] / 28 is the number of times that index already appears)
                    priority[i] = n + count * 28;
                    return;
                } else if (priority[i] % 28 == n) {
                    // count how many times index n is already present
                    count++;
                }
            }
        }

        // returns char of node
        char getChar() const {
            return character;
        }

        // returns child for character
        Node* getNode(char c) const {
            return children[c - 'a'];
        }

        // returns child for index
        Node* getNode(unsigned char i) const {
            return children[i];
        }

        // returns priority i
        unsigned char getPriority(unsigned char i) const {
            return priority[i];         
        }
};

# endif