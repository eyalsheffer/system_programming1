
#include "doctest.h"
#include "Graph.hpp"

namespace graph {

    TEST_CASE("Test Graph Initialization") {
        Graph g(5);  // Initialize a graph with 5 vertices
        CHECK(g.getVertexCount() == 5);  // Use doctest CHECK for assertions
        CHECK(g.getEdgeCount() == 0);  // No edges yet
    }

    TEST_CASE("Test Add Edge") {
        Graph g(5);  // Initialize a graph with 5 vertices
        
        // Add some edges
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 3, 7);

        CHECK(g.getEdgeCount() == 3);  // After adding 3 edges
        CHECK(g.getWeight(0, 1) == 10);  // Check weight for edge (0, 1)
        CHECK(g.getWeight(1, 3) == 7);  // Check weight for edge (1, 3)
    }

    TEST_CASE("Test Get Neighbors") {
        Graph g(5);
        g.addEdge(0, 1, 1);
        g.addEdge(0, 2, 1);
        g.addEdge(1, 2, 2);
        
        int neighborCount = 0;
        int* neighbors = g.getNeighbors(0, neighborCount);       
        CHECK(neighborCount == 2);  // Check neighbor count for node 0
        CHECK((neighbors[0] == 1 || neighbors[1] == 1));  // Check for neighbor 1
        CHECK((neighbors[0] == 2 || neighbors[1] == 2));  // Check for neighbor 2
        
        delete[] neighbors;  // Clean up dynamically allocated memory
    }

    TEST_CASE("Test Invalid Edge Addition") {
        Graph g(3);
        
        // Try adding an edge with invalid nodes
        g.addEdge(3, 4, 10);  // Invalid node indices
        CHECK(g.getEdgeCount() == 0);  // Edge count should remain 0
    }

}
