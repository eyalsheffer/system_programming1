
#include "doctest.h"
#include "Edge.hpp"
#include "PriorityQueue.hpp"
#include "Stack.hpp"
#include "UnionFind.hpp"

TEST_CASE("Edge class functionality") {
    Edge e1(1, 2, 10);
    
    CHECK(e1.getStart() == 1);
    CHECK(e1.getEnd() == 2);
    CHECK(e1.getWeight() == 10);
    
    Edge e2 = e1; // Copy constructor
    CHECK(e2.getStart() == 1);
    CHECK(e2.getEnd() == 2);
    CHECK(e2.getWeight() == 10);
    
    Edge e3(3, 4, 5);
    e3 = e1; // Assignment operator
    CHECK(e3.getStart() == 1);
    CHECK(e3.getEnd() == 2);
    CHECK(e3.getWeight() == 10);
}

TEST_CASE("PriorityQueue class functionality") {
    PriorityQueue pq(10);
    
    CHECK(pq.isEmpty() == true);
    
    pq.push(1, 5);
    pq.push(2, 3);
    pq.push(3, 8);
    
    CHECK(pq.top() == 2);  // Highest priority
    pq.pop();
    CHECK(pq.top() == 1);
    pq.pop();
    CHECK(pq.top() == 3);
    
    pq.pop();
    CHECK(pq.isEmpty() == true);
}

TEST_CASE("Stack class functionality") {
    Stack s(3);
    
    CHECK(s.isEmpty() == true);
    
    s.push(10);
    s.push(20);
    CHECK(s.returnTop() == 20);
    
    CHECK(s.pop() == 20);
    CHECK(s.returnTop() == 10);
    
    s.push(30);
    CHECK(s.pop() == 30);
    CHECK(s.pop() == 10);
    
    CHECK(s.isEmpty() == true);
}

TEST_CASE("UnionFind class functionality") {
    UnionFind uf(5);
    
    CHECK(uf.connected(0, 1) == false);
    
    uf.unionSets(0, 1);
    CHECK(uf.connected(0, 1) == true);
    
    uf.unionSets(1, 2);
    CHECK(uf.connected(0, 2) == true);
    
    uf.unionSets(3, 4);
    CHECK(uf.connected(3, 4) == true);
    
    CHECK(uf.connected(0, 3) == false);
}
