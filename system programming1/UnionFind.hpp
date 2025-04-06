#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

class UnionFind {
private:
    int* parent;   // Array to hold the parent of each element
    int* rank;     // Array to hold the rank (or size) of each tree
    int size;      // Number of elements

public:
    // Constructor to initialize the UnionFind with 'n' elements
    UnionFind(int n);

    // Destructor to clean up the allocated memory
    ~UnionFind();

    // Find the root of the element with path compression
    int find(int x);

    // Union by rank: Join two sets
    void unionSets(int x, int y);

    // Check if two elements are in the same set
    bool connected(int x, int y);
};

#endif
