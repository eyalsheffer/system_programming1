
#include "doctest.h"
#include "Graph.hpp"

namespace graph {

    TEST_CASE("Test Graph Initialization") {
        Graph g(5);  
        CHECK(g.getVertexCount() == 5);  
        CHECK(g.getEdgeCount() == 0);  
    }

    TEST_CASE("Test Add Edge") {
        Graph g(5);  
        
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 3, 7);

        CHECK(g.getEdgeCount() == 3);  
        CHECK(g.getWeight(0, 1) == 10);  
        CHECK(g.getWeight(1, 3) == 7); 
    }

    TEST_CASE("Test Get Neighbors") {
        Graph g(5);
        g.addEdge(0, 1, 1);
        g.addEdge(0, 2, 1);
        g.addEdge(1, 2, 2);
        
        int neighborCount = 0;
        int* neighbors = g.getNeighbors(0, neighborCount);       
        CHECK(neighborCount == 2);  
        CHECK((neighbors[0] == 1 || neighbors[1] == 1));  
        CHECK((neighbors[0] == 2 || neighbors[1] == 2));  
        delete[] neighbors;  
    }

    TEST_CASE("Test Invalid Edge Addition") {
        Graph g(3);
        g.addEdge(3, 4, 10);  
        CHECK(g.getEdgeCount() == 0);  
    }

}
