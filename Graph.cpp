#include "Graph.hpp"
#include "Edge.hpp"

namespace graph {

    // Constructor: Initializes the graph with the given number of vertices
    Graph::Graph(int vertexCount) : vertexCount(vertexCount), edgeCount(0) {
        adjacencyList = new Edge*[vertexCount];

        // Initialize each adjacency list as nullptr (empty list for each vertex)
        for (int i = 0; i < vertexCount; ++i) {
            adjacencyList[i] = nullptr;
        }
    }
    Graph::Graph(int vertexCount, int edgeCount) : vertexCount(vertexCount), edgeCount(edgeCount) {
        adjacencyList = new Edge*[vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            adjacencyList[i] = nullptr;
        }
    }

    // Destructor: Cleans up the dynamically allocated memory
    Graph::~Graph() {
        for (int i = 0; i < vertexCount; ++i) {
            Edge* current = adjacencyList[i];
            while (current) {
                Edge* nextEdge = current->getNext();
                // We don't delete the nextEdge here since it is being managed elsewhere
                current = nextEdge;
            }
        }
        delete[] adjacencyList; 
    }

    // Adds an edge from 'start' to 'end' with the given 'weight'
    void Graph::addEdge(int start, int end, int weight) {
        if (start >= vertexCount || end >= vertexCount || start < 0 || end < 0) {
            std::cerr << "Invalid node index!" << std::endl;
            return;
        }
    
        // Create a new edge for the adjacency list of the start node
        Edge* forwardEdge = new Edge(start, end, weight);  // Pass start, end, and weight
        forwardEdge->setNext(adjacencyList[start]);
        adjacencyList[start] = forwardEdge;
    
        // Since this is an undirected graph, add the reverse edge as well
        Edge* reverseEdge = new Edge(end, start, weight);  // Reverse edge with swapped start and end
        reverseEdge->setNext(adjacencyList[end]);
        adjacencyList[end] = reverseEdge;
    
        ++edgeCount;
    }

    // Retrieves the weight of an edge between two nodes
    int Graph::getWeight(int start, int end) const {
        if (start >= vertexCount || end >= vertexCount || start < 0 || end < 0) {
            std::cerr << "Invalid node index!" << std::endl;
            return -1;
        }
    
        // Traverse the adjacency list to find the edge
        Edge* current = adjacencyList[start];
        while (current) {
            if (current->getEnd() == end) { // Use getter function for encapsulation
                return current->getWeight();
            }
            current = current->getNext();
        }
    
        return -1;
    }

    // Retrieves the neighbors of a node
    int* Graph::getNeighbors(int node, int& neighborCount) const {
        if (node >= vertexCount || node < 0) {
            std::cerr << "Invalid node index!" << std::endl;
            return nullptr;
        }

        // Count the number of neighbors
        neighborCount = 0;
        Edge* current = adjacencyList[node];
        while (current != nullptr) {
            ++neighborCount;
            current = current->getNext();
        }

        // Allocate space for the neighbors
        int* neighbors = new int[neighborCount];
        current = adjacencyList[node];
        int idx = 0;
        while (current != nullptr) {
            neighbors[idx++] = current->getEnd();
            current = current->getNext();
        }

        return neighbors;
    }

    // Returns the number of vertices
    int Graph::getVertexCount() const {
        return vertexCount;
    }

    // Returns the number of edges
    int Graph::getEdgeCount() const {
        return edgeCount;
    }

    // Retrieves all edges of the graph (used in Kruskal's algorithm)
    Edge** Graph::getEdges() const {
        // Calculate the total number of edges in the graph (you might need to modify this logic)
        int totalEdges = 0;
        for (int i = 0; i < vertexCount; ++i) {
            Edge* current = adjacencyList[i];
            while (current) {
                totalEdges++;
                current = current->getNext();
            }
        }
    
        // Create an array of pointers to hold all edges
        Edge** edges = new Edge*[totalEdges];
        int index = 0;
    
        // Fill the edges array with all edges in the graph
        for (int i = 0; i < vertexCount; ++i) {
            Edge* current = adjacencyList[i];
            while (current) {
                edges[index++] = current;
                current = current->getNext();
            }
        }
    
        return edges;
    }

    // Prints the graph (all edges with weights)
    void Graph::printGraph() const {
        for (int i = 0; i < vertexCount; ++i) {
            Edge* current = adjacencyList[i];
            std::cout << "Node " << i << ": ";
            while (current != nullptr) {
                std::cout << "(" << current->getEnd() << ", " << current->getWeight() << ") ";
                current = current->getNext();
            }
            std::cout << std::endl;
        }
    }

} // namespace graph
