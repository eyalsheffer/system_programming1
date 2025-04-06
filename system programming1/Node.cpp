#include "Node.hpp"

// Constructor to initialize the node with a value
Node::Node(int val) : data(val), next(nullptr) {}

// Destructor (doesn't need to do anything special for this simple structure)
Node::~Node() {}
