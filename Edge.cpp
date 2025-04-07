#include "Edge.hpp"
#include <iostream>

Edge::Edge() : start(0), end(0), weight(0), next(nullptr) {}

Edge::Edge(int s, int e, int w) : start(s), end(e), weight(w), next(nullptr) {}


Edge::Edge(const Edge& other) : start(other.start), end(other.end), weight(other.weight), next(nullptr) {
    if (other.next) {
        next = new Edge(*other.next);  
    }
}


Edge& Edge::operator=(const Edge& other) {
    if (this == &other) {
        return *this; 
    }
    delete next;
    start = other.start;
    end = other.end;
    weight = other.weight;
    next = (other.next) ? new Edge(*other.next) : nullptr; 
    return *this;
}

Edge::~Edge() {
    delete next; 
}

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

void Edge::print() const {
    std::cout << "Edge from " << start << " to " << end << " with weight " << weight;
    if (next) {
        std::cout << " -> Next: " << next->getEnd();
    }
    std::cout << std::endl;
}
