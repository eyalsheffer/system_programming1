#include "Edge.hpp"
#include <iostream>

// Default constructor initializes edge with default values
Edge::Edge() : start(0), end(0), weight(0), next(nullptr) {}

// Parameterized constructor
Edge::Edge(int s, int e, int w) : start(s), end(e), weight(w), next(nullptr) {}

// Copy constructor (deep copy)
Edge::Edge(const Edge& other) : start(other.start), end(other.end), weight(other.weight), next(nullptr) {
    if (other.next) {
        next = new Edge(*other.next);  // Deep copy of the next edge
    }
}

// Copy assignment operator (deep copy)
Edge& Edge::operator=(const Edge& other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }

    // Delete existing next edge to avoid memory leaks
    delete next;

    // Copy values
    start = other.start;
    end = other.end;
    weight = other.weight;
    next = (other.next) ? new Edge(*other.next) : nullptr; // Deep copy

    return *this;
}

// Destructor to free dynamically allocated memory
Edge::~Edge() {
    delete next; // Recursively deletes next edges
}

// Getter functions
int Edge::getStart() const {
    return start;
}

int Edge::getEnd() const {
    return end;
}

int Edge::getWeight() const {
    return weight;
}

Edge* Edge::getNext() const {
    return next;
}

// Setter functions
void Edge::setStart(int s) {
    start = s;
}

void Edge::setEnd(int e) {
    end = e;
}

void Edge::setWeight(int w) {
    weight = w;
}

void Edge::setNext(Edge* nextEdge) {
    next = nextEdge;
}

// Print function to display edge information
void Edge::print() const {
    std::cout << "Edge from " << start << " to " << end << " with weight " << weight;
    if (next) {
        std::cout << " -> Next: " << next->getEnd();
    }
    std::cout << std::endl;
}
