#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"  

namespace graph {

    class Algorithms {
    private:
  
    public:
        Algorithms();
        ~Algorithms();

        Graph bfs(Graph& g, int start);
        Graph dfs(Graph& g, int start);
        Graph dijkstra(Graph& g, int start);
        Graph prim(Graph& g);
        Graph kruskal(Graph& g);
    };

} 

#endif 
