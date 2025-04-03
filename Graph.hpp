#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace graph {

    class Graph {
    private:
        // Defining the Edge structure inside Graph
        struct Edge {
            int end;
            int weight;
            Edge* next;  // Pointer to the next edge in the adjacency list

            // Default constructor for creating an edge with default values
            Edge() : end(-1), weight(0), next(nullptr) {}

            // Parameterized constructor for creating an edge
            Edge(int e, int w) : end(e), weight(w), next(nullptr) {}
        };

        Edge** adjacencyList;  // Array of adjacency list heads (raw pointers to Edge)
        int vertexCount;       // Number of vertices in the graph
        int edgeCount;         // Number of edges in the graph

    public:
        // Constructor
        Graph(int vertexCount);

        // Destructor
        ~Graph();

        // Adds an edge to the graph
        void addEdge(int start, int end, int weight);

        // Retrieves the weight of an edge between two nodes
        int getWeight(int start, int end) const;

        // Retrieves the neighbors of a node
        int* getNeighbors(int node, int& neighborCount) const;

        // Returns the number of vertices
        int getVertexCount() const;

        // Returns the number of edges
        int getEdgeCount() const;

        // Retrieves all edges of the graph (used in Kruskal's algorithm)
        Edge* getEdges() const;
    };

} // namespace graph

#endif // GRAPH_HPP
