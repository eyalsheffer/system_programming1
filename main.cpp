#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#include "Stack.hpp"

int main() {
    graph::Graph g(6); 
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 1);

    std::cout << "Original Graph:" << std::endl;
    g.printGraph();
    graph::Algorithms algorithms;

    std::cout << "\nRunning BFS from node 0:" << std::endl;
    graph::Graph bfsResult = algorithms.bfs(g, 0);
    bfsResult.printGraph();

    std::cout << "\nRunning DFS from node 0:" << std::endl;
    graph::Graph dfsResult = algorithms.dfs(g, 0);
    dfsResult.printGraph();

    std::cout << "\nRunning Dijkstra's algorithm from node 0:" << std::endl;
    graph::Graph dijkstraResult = algorithms.dijkstra(g, 0);
    dijkstraResult.printGraph();

    std::cout << "\nRunning Prim's algorithm from node 0:" << std::endl;
    graph::Graph primResult = algorithms.prim(g);
    primResult.printGraph();

    std::cout << "\nRunning Kruskal's algorithm:" << std::endl;
    graph::Graph kruskalResult = algorithms.kruskal(g);
    kruskalResult.printGraph();

    
    return 0;
}
