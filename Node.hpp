#ifndef NODE_HPP
#define NODE_HPP

class Node {
public:
    int data;  // The data held by the node
    Node* next;  // Pointer to the next node in the list

    // Constructor to initialize node with data
    Node(int val);

    // Destructor (for completeness, though it doesn't need to do much here)
    ~Node();
};

#endif
