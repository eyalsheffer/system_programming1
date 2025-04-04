#include "doctest.h"
#include "Graph.hpp"  // Include your Graph header file

namespace graph {

    // Custom function to simulate output (print)
    void customPrint(const char* msg) {
        // Implement your own output logic here, like writing to a file or custom stream
    }

    // Custom assertion function
    void customAssert(bool condition, const char* message) {
        if (!condition) {
            customPrint(message);  // Print custom error message if assertion fails
        }
    }

    TEST_CASE("Test Graph Initialization") {
        Graph g(5);  // Initialize a graph with 5 vertices
        customAssert(g.getVertexCount() == 5, "Error: Vertex count mismatch!");
        customAssert(g.getEdgeCount() == 0, "Error: Edge count should be zero!");
    }

    TEST_CASE("Test Add Edge") {
        Graph g(5);  // Initialize a graph with 5 vertices
        
        // Add some edges
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 3, 7);

        customAssert(g.getEdgeCount() == 3, "Error: Edge count mismatch after adding edges!");
        customAssert(g.getWeight(0, 1) == 10, "Error: Weight mismatch for edge (0, 1)!");
        customAssert(g.getWeight(1, 3) == 7, "Error: Weight mismatch for edge (1, 3)!");
    }

    TEST_CASE("Test Get Neighbors") {
        Graph g(5);
        g.addEdge(0, 1, 1);
        g.addEdge(0, 2, 1);
        g.addEdge(1, 2, 2);
        
        int neighborCount = 0;
        int* neighbors = g.getNeighbors(0, neighborCount);
        
        customAssert(neighborCount == 2, "Error: Neighbor count mismatch for node 0!");
        customAssert(neighbors[0] == 1, "Error: Incorrect neighbor for node 0!");
        customAssert(neighbors[1] == 2, "Error: Incorrect neighbor for node 0!");
        
        delete[] neighbors;  // Clean up dynamically allocated memory
    }

    TEST_CASE("Test Invalid Edge Addition") {
        Graph g(3);
        
        // Try adding an edge with invalid nodes
        g.addEdge(3, 4, 10);  // Invalid node indices
        customAssert(g.getEdgeCount() == 0, "Error: Edge count should be zero after invalid edge addition!");
    }

}
