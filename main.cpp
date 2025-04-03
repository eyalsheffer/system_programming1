#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#include "Stack.hpp"

// Function to print the graph edges for testing
void printGraph(const graph::Graph& g) {
    for (int i = 0; i < g.getSize(); ++i) {
        std::cout << "Node " << i << ": ";
        for (const auto& edge : g.getAdjacencyList(i)) {
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        std::cout << std::endl;
    }
}

int main() {
   

    return 0;
}
