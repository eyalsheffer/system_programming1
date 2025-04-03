#include "Graph.hpp"
#include <iostream>

// Define a large number to represent "infinity"
const int INF = 1000000;  // We don't use <climits>, so we define it here

namespace graph {

    Graph::Graph(int vertexCount) {
        this->vertexCount = vertexCount;
        this->edgeCount = 0;

        // Create an array of adjacency list heads (initially set to nullptr)
        adjacencyList = new Edge*[vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            adjacencyList[i] = nullptr;
        }
    }

    Graph::~Graph() {
        for (int i = 0; i < vertexCount; ++i) {
            Edge* current = adjacencyList[i];
            while (current != nullptr) {
                Edge* temp = current;
                current = current->next;
                delete temp;  // Delete each edge in the adjacency list
            }
        }
        delete[] adjacencyList;  // Delete the array of adjacency lists
    }

    void Graph::addEdge(int start, int end, int weight) {
        if (start >= 0 && start < vertexCount && end >= 0 && end < vertexCount) {
            // Create a new edge from start to end
            Edge* newEdge = new Edge(end, weight);
            newEdge->next = adjacencyList[start];  // Insert at the beginning of the adjacency list
            adjacencyList[start] = newEdge;

            // Since the graph is undirected, add the reverse edge as well
            newEdge = new Edge(start, weight);
            newEdge->next = adjacencyList[end];
            adjacencyList[end] = newEdge;

            edgeCount++;
        }
    }

    int Graph::getWeight(int start, int end) const {
        if (start >= 0 && start < vertexCount && end >= 0 && end < vertexCount) {
            Edge* current = adjacencyList[start];
            while (current != nullptr) {
                if (current->end == end) {
                    return current->weight;
                }
                current = current->next;
            }
        }
        return -1;  // No edge exists
    }

    int* Graph::getNeighbors(int node, int& neighborCount) const {
        int* neighbors = new int[vertexCount];  // Array to store neighbors of the node
        neighborCount = 0;

        Edge* current = adjacencyList[node];
        while (current != nullptr) {
            neighbors[neighborCount++] = current->end;
            current = current->next;
        }

        return neighbors;
    }

    int Graph::getVertexCount() const {
        return vertexCount;
    }

    int Graph::getEdgeCount() const {
        return edgeCount;
    }

    Graph::Edge* Graph::getEdges() const {
        Edge* edges = new Edge[edgeCount];
        int idx = 0;
        
        for (int i = 0; i < vertexCount; ++i) {
            Edge* current = adjacencyList[i];
            while (current != nullptr) {
                if (i < current->end) {  // Avoid duplicates for undirected graphs
                    edges[idx].end = current->end;
                    edges[idx].weight = current->weight;
                    edges[idx].next = nullptr;
                    ++idx;
                }
                current = current->next;
            }
        }
        return edges;
    }

} // namespace graph
