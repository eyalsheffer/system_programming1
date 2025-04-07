#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"

namespace graph {
    Graph createTestGraph() {
        Graph g(6);
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 20);
        g.addEdge(1, 2, 30);
        g.addEdge(2, 3, 40);
        g.addEdge(3, 4, 50);
        g.addEdge(4, 0, 60);
        return g;
    }

    TEST_CASE("Test BFS") {
        Graph g = createTestGraph();
        Algorithms algorithms;
        Graph result = algorithms.bfs(g, 0);
        result.printGraph();
        CHECK(result.getVertexCount() == 6);
        
    }

    TEST_CASE("Test DFS") {
        Graph g = createTestGraph();
        Algorithms algorithms;
        Graph result = algorithms.dfs(g, 0);
        result.printGraph();
        CHECK(result.getVertexCount() == 6);
    }

    TEST_CASE("Test Dijkstra") {
        Graph g = createTestGraph();
        Algorithms algorithms;
        Graph result = algorithms.dijkstra(g, 0);
        result.printGraph();
        CHECK(result.getVertexCount() == 6);
    }

    TEST_CASE("Test Prim's algorithm") {
        Graph g = createTestGraph();
        Algorithms algorithms;
        Graph result = algorithms.prim(g);
        result.printGraph();
        CHECK(result.getVertexCount() == 6);
    }

    TEST_CASE("Test Kruskal's algorithm") {
        Graph g = createTestGraph();
        Algorithms algorithms;
        Graph result = algorithms.kruskal(g);
        result.printGraph();
        CHECK(result.getVertexCount() == 6);
    }



    TEST_CASE("Test disconnected graph") {
        Graph g(5);
        Algorithms algorithms;

        Graph result = algorithms.dfs(g, 0);
        CHECK(result.getVertexCount() == 5);

    }

    TEST_CASE("Test graph with a cycle") {
        Graph g(3);
        g.addEdge(0, 1, 10);
        g.addEdge(1, 2, 20);
        g.addEdge(2, 0, 30);
        
        Algorithms algorithms;

        Graph result = algorithms.dfs(g, 0);
        CHECK(result.getVertexCount() == 3);

        Graph kruskalResult = algorithms.kruskal(g);
        CHECK(kruskalResult.getVertexCount() == 3);
    }
}
