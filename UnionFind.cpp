#include "UnionFind.hpp"
#include <iostream>

// Constructor: Initialize the UnionFind with 'n' elements
UnionFind::UnionFind(int n) {
    size = n;
    parent = new int[n];  // Array to store the parent of each element
    rank = new int[n];    // Array to store the rank (or size) of each tree

    // Initially, each element is its own parent, and rank is 0
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Destructor: Clean up dynamically allocated memory
UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

// Find the root of the set containing 'x', with path compression
int UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // Path compression
    }
    return parent[x];
}

// Union by rank: Merge two sets containing 'x' and 'y'
void UnionFind::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    // If they are already in the same set, do nothing
    if (rootX == rootY) {
        return;
    }

    // Union by rank: Attach the smaller tree under the root of the larger tree
    if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;  // Increment the rank if the ranks are equal
    }
}

// Check if 'x' and 'y' are in the same set
bool UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}
