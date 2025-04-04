#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#include "Stack.hpp"

// Function to print the graph edges for testing


int main() {
    // Create a simple graph for testing
    graph::Graph g(6); // 6 nodes: 0 to 5
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 1);

    // Print the original graph
    std::cout << "Original Graph:" << std::endl;
    g.printGraph();
    
    // Create an instance of the Algorithms class
    graph::Algorithms algorithms;

    // Test BFS (Breadth-First Search)
    std::cout << "\nRunning BFS from node 0:" << std::endl;
    graph::Graph bfsResult = algorithms.bfs(g, 0);
    bfsResult.printGraph();

    // Test DFS (Depth-First Search)
    std::cout << "\nRunning DFS from node 0:" << std::endl;
    graph::Graph dfsResult = algorithms.dfs(g, 0);
    dfsResult.printGraph();

    // Test Dijkstra's Algorithm (shortest path)
    std::cout << "\nRunning Dijkstra's algorithm from node 0:" << std::endl;
    graph::Graph dijkstraResult = algorithms.dijkstra(g, 0);
    dijkstraResult.printGraph();

    // Test Prim's Algorithm (Minimum Spanning Tree)
    std::cout << "\nRunning Prim's algorithm from node 0:" << std::endl;
    graph::Graph primResult = algorithms.prim(g);
    primResult.printGraph();

    // Test Kruskal's Algorithm (Minimum Spanning Tree)
    std::cout << "\nRunning Kruskal's algorithm:" << std::endl;
    graph::Graph kruskalResult = algorithms.kruskal(g);
    kruskalResult.printGraph();

    
    return 0;
}
