#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"  // Including the Graph class to use it in the algorithms

namespace graph {

    class Algorithms {
    private:
        // No data members needed for the Algorithms class

    public:
        // Constructor
        Algorithms();

        // Destructor
        ~Algorithms();

        // Graph Algorithms
        Graph bfs(Graph& g, int start);
        Graph dfs(Graph& g, int start);
        Graph dijkstra(Graph& g, int start);
        Graph prim(Graph& g);
        Graph kruskal(Graph& g);
    };

} // namespace graph

#endif // ALGORITHMS_HPP
