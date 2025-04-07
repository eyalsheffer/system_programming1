#include "Graph.hpp"
#include "Edge.hpp"

namespace graph {

    Graph::Graph(int vertexCount) : vertexCount(vertexCount), edgeCount(0) {
        adjacencyList = new Edge*[vertexCount];
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

    Graph::~Graph() {
        for (int i = 0; i < vertexCount; ++i) {
            Edge* current = adjacencyList[i];
            while (current) {
                Edge* nextEdge = current->getNext();
                delete current;  
                current = nextEdge;
            }
        }
        delete[] adjacencyList; 
    }
    
    void Graph::addEdge(int start, int end, int weight) {
        if (start >= vertexCount || end >= vertexCount || start < 0 || end < 0) {
            std::cerr << "Invalid node index!" << std::endl;
            return;
        }
        Edge* forwardEdge = new Edge(start, end, weight);
        forwardEdge->setNext(adjacencyList[start]);
        adjacencyList[start] = forwardEdge;
        Edge* reverseEdge = new Edge(end, start, weight);
        reverseEdge->setNext(adjacencyList[end]);
        adjacencyList[end] = reverseEdge;
        ++edgeCount;
    }

    int Graph::getWeight(int start, int end) const {
        if (start >= vertexCount || end >= vertexCount || start < 0 || end < 0) {
            std::cerr << "Invalid node index!" << std::endl;
            return -1;
        }
        Edge* current = adjacencyList[start];
        while (current) {
            if (current->getEnd() == end) {
                return current->getWeight();
            }
            current = current->getNext();
        }
    
        return -1;
    }
    int* Graph::getNeighbors(int node, int& neighborCount) const {
        if (node >= vertexCount || node < 0) {
            std::cerr << "Invalid node index!" << std::endl;
            neighborCount = 0;
            return nullptr;
        }
        if (adjacencyList[node] == nullptr) {
            neighborCount = 0;
            return nullptr;
        }
        neighborCount = 0;
        Edge* current = adjacencyList[node];
        while (current != nullptr) {
            ++neighborCount;
            current = current->getNext();
        }
    
        int* neighbors = new int[neighborCount];
        if (neighbors == nullptr) {
            std::cerr << "Memory allocation failed for neighbors array" << std::endl;
            neighborCount = 0;
            return nullptr;
        }
    
        current = adjacencyList[node];
        int idx = 0;
        while (current != nullptr) {
            neighbors[idx++] = current->getEnd();
            current = current->getNext();
        }
        return neighbors;
    }
    int Graph::getVertexCount() const{
        return vertexCount;
    }
    int* Graph::getAdjacentVertices(int node) const {
        Edge* current = adjacencyList[node];

        int* adj_array = new int[vertexCount];
        int index = 0;

        while (current != nullptr) {
            adj_array[index++] = current->getEnd();
            current = current->getNext();
        }

        adj_array[index] = -1; 
        return adj_array; 
    }
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

} 
