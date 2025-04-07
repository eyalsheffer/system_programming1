#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "Edge.hpp"

namespace graph {

    class Graph {
    private:

        Edge** adjacencyList;  
        int vertexCount;       
        int edgeCount;         

    public:

        Graph(int vertexCount);
        Graph(int vertexCount, int edgeCounter); 
        ~Graph();

        void addEdge(int start, int end, int weight);
        int getWeight(int start, int end) const;
        int* getNeighbors(int node, int& neighborCount) const;
        int getVertexCount() const;
        int getEdgeCount() const;
        Edge** getEdges() const;
        int* getAdjacentVertices(int node) const;
        void printGraph() const;
    };

} 

#endif 
