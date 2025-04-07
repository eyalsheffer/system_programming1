#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"

using namespace graph;

TEST_CASE("Graph basic operations") {
    Graph g(4); 

    SUBCASE("Vertex and edge count") {
        CHECK(g.getVertexCount() == 4);
        CHECK(g.getEdgeCount() == 0);

        g.addEdge(0, 1, 10);
        CHECK(g.getEdgeCount() == 1); 
    }

    SUBCASE("Adding and getting edge weight") {
        g.addEdge(1, 2, 5);
        CHECK(g.getWeight(1, 2) == 5);
        CHECK(g.getWeight(2, 1) == 5);
        CHECK(g.getWeight(0, 3) == -1); 
    }

    SUBCASE("Neighbors retrieval") {
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 20);

        int count = 0;
        int* neighbors = g.getNeighbors(0, count);
        CHECK(count == 2);
        CHECK((neighbors[0] == 1 || neighbors[1] == 1));
        CHECK((neighbors[0] == 2 || neighbors[1] == 2));
        delete[] neighbors;
    }

    SUBCASE("getAdjacentVertices includes -1 end") {
        g.addEdge(2, 3, 7);
        int* adj = g.getAdjacentVertices(2);
        int found = 0;
        for (int i = 0; adj[i] != -1; ++i) {
            if (adj[i] == 3) found = 1;
        }
        CHECK(found == 1);
        delete[] adj;
    }

    SUBCASE("Edge list returns non-null") {
        g.addEdge(1, 3, 4);
        Edge** edges = g.getEdges();
        CHECK(edges != nullptr);
        delete[] edges;
    }
}
