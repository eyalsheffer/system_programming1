#include "Algorithms.hpp"
#include "UnionFind.hpp"
#include "Edge.hpp"
#include <iostream>

namespace graph {

    // Define a large number to represent "infinity"
    const int INF = 1000000;  // Custom infinity value

    // Constructor (no data to initialize)
    Algorithms::Algorithms() {}

    // Destructor (no special cleanup needed)
    Algorithms::~Algorithms() {}

    // BFS (Breadth-First Search)
    Graph Algorithms::bfs(Graph& g, int start) {  // Pass graph by reference to avoid copying
        int vertexCount = g.getVertexCount();
    
        // Create a visited array and initialize it to false
        bool visited[vertexCount] = {false};
    
        // Simulate the queue with a simple array and front, rear pointers
        int queue[vertexCount];
        int front = 0, rear = 0;
    
        // Add start node to queue
        queue[rear++] = start;
        visited[start] = true;
    
        while (front < rear) {
            int node = queue[front++];
            std::cout << "Visiting node: " << node << std::endl;
    
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(node, neighborCount);  // Get neighbors of the current node
    
            if (neighbors == nullptr) {
                std::cerr << "Error: Neighbors are null!" << std::endl;
                break;
            }
    
            // Add neighbors to the queue
            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    if (rear < vertexCount) {
                        queue[rear++] = neighbor;  // Add the neighbor to the queue if there's space
                    } else {
                        std::cerr << "Queue overflow!" << std::endl;
                        break;
                    }
                }
            }
    
            // Cleanup the neighbors array after use
            delete[] neighbors;
        }
    
        // No need to return the graph, as we passed it by reference
        return g;  // (Optional) You can omit this if you're not using the modified graph outside
    }

    // DFS (Depth-First Search)
    Graph Algorithms::dfs(Graph& g, int start) {  // Pass graph by reference to avoid copying
        int vertexCount = g.getVertexCount();
        
        // Create a visited array and initialize it to false
        bool visited[vertexCount] = {false};
    
        // Simulate the stack with a simple array and a top pointer
        int stack[vertexCount];
        int top = -1;
    
        // Push the start node onto the stack
        stack[++top] = start;
        visited[start] = true;
    
        while (top >= 0) {
            int node = stack[top--];  // Pop a node from the stack
            std::cout << "Visiting node: " << node << std::endl;
    
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(node, neighborCount);  // Get neighbors of the current node
    
            if (neighbors == nullptr) {
                std::cerr << "Error: Neighbors are null!" << std::endl;
                break;
            }
    
            // Add neighbors to the stack
            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    if (top + 1 < vertexCount) {
                        stack[++top] = neighbor;  // Push the neighbor onto the stack if there's space
                    } else {
                        std::cerr << "Stack overflow!" << std::endl;
                        break;
                    }
                }
            }
    
            // Cleanup the neighbors array after use
            delete[] neighbors;
        }
    
        // No need to return the graph, as we passed it by reference
        return g;
    }
    
    // Dijkstra's Algorithm (Shortest Path)
    Graph Algorithms::dijkstra(Graph& g, int start) {  // Pass graph by reference to avoid copying
        int vertexCount = g.getVertexCount();
        int* dist = new int[vertexCount];
        bool* visited = new bool[vertexCount]();
    
        // Initialize distances with a large number (infinity)
        for (int i = 0; i < vertexCount; ++i) {
            dist[i] = INF;
        }
    
        dist[start] = 0;
    
        // Min-heap priority queue for the shortest path calculation (implemented manually)
        int* pqNode = new int[vertexCount];
        int* pqDist = new int[vertexCount];
        int pqSize = 0;
    
        pqNode[pqSize] = start;
        pqDist[pqSize++] = 0;
    
        while (pqSize > 0) {
            // Find the node with the minimum distance
            int minIdx = 0;
            for (int i = 1; i < pqSize; ++i) {
                if (pqDist[i] < pqDist[minIdx]) {
                    minIdx = i;
                }
            }
    
            int node = pqNode[minIdx];
            int distToNode = pqDist[minIdx];
    
            // Remove the minimum element from the priority queue
            for (int i = minIdx; i < pqSize - 1; ++i) {
                pqNode[i] = pqNode[i + 1];
                pqDist[i] = pqDist[i + 1];
            }
            pqSize--;
    
            if (visited[node]) continue;
            visited[node] = true;
    
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(node, neighborCount);
    
            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];
                int weight = g.getWeight(node, neighbor);
    
                if (distToNode + weight < dist[neighbor]) {
                    dist[neighbor] = distToNode + weight;
    
                    // Insert the neighbor into the priority queue (in sorted order)
                    pqNode[pqSize] = neighbor;
                    pqDist[pqSize++] = dist[neighbor];
                }
            }
    
            delete[] neighbors;  // Cleanup
        }
    
        // Output the distances
        std::cout << "Distances from start node " << start << ":" << std::endl;
        for (int i = 0; i < vertexCount; ++i) {
            std::cout << "Node " << i << ": " << (dist[i] == INF ? "INF" : std::to_string(dist[i])) << std::endl;
        }
    
        delete[] dist;
        delete[] visited;
        delete[] pqNode;
        delete[] pqDist;
    
        // No need to return the graph, as we passed it by reference
        return g;
    }
    
    // Prim's Algorithm (Minimum Spanning Tree)
    Graph Algorithms::prim(Graph& g, int start) {  // Pass graph by reference to avoid copying
        int vertexCount = g.getVertexCount();
        bool* inMST = new bool[vertexCount]();
        int* key = new int[vertexCount];
        int* parent = new int[vertexCount];
    
        for (int i = 0; i < vertexCount; ++i) {
            key[i] = INF;
            parent[i] = -1;
        }
    
        key[start] = 0;
    
        // Min-heap priority queue for Prim's algorithm (implemented manually)
        int* pqNode = new int[vertexCount];
        int* pqKey = new int[vertexCount];
        int pqSize = 0;
    
        pqNode[pqSize] = start;
        pqKey[pqSize++] = 0;
    
        while (pqSize > 0) {
            // Find the node with the minimum key
            int minIdx = 0;
            for (int i = 1; i < pqSize; ++i) {
                if (pqKey[i] < pqKey[minIdx]) {
                    minIdx = i;
                }
            }
    
            int u = pqNode[minIdx];
            pqSize--;
    
            inMST[u] = true;
    
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(u, neighborCount);
    
            for (int i = 0; i < neighborCount; ++i) {
                int v = neighbors[i];
                int weight = g.getWeight(u, v);
    
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
    
                    // Insert the neighbor into the priority queue (in sorted order)
                    pqNode[pqSize] = v;
                    pqKey[pqSize++] = key[v];
                }
            }
    
            delete[] neighbors;  // Cleanup
        }
    
        // Output the minimum spanning tree (MST)
        std::cout << "Edges in the Minimum Spanning Tree:" << std::endl;
        for (int i = 1; i < vertexCount; ++i) {
            if (parent[i] != -1) {
                std::cout << parent[i] << " - " << i << " with weight " << g.getWeight(parent[i], i) << std::endl;
            }
        }
    
        delete[] inMST;
        delete[] key;
        delete[] parent;
        delete[] pqNode;
        delete[] pqKey;
    
        // No need to return the graph, as we passed it by reference
        return g;
    }

    // Kruskal's Algorithm (Minimum Spanning Tree using Union-Find)
    Graph Algorithms::kruskal(Graph& g, int start) {
        int vertexCount = g.getVertexCount();
        int edgeCount = g.getEdgeCount();
    
        // Step 1: Get all edges of the graph
        Edge** edges = g.getEdges();  // Assuming the Graph has a method to return edges
    
        // Step 2: Sort all edges in non-decreasing order of their weight (Bubble sort)
        for (int i = 0; i < edgeCount - 1; i++) {
            for (int j = 0; j < edgeCount - i - 1; j++) {
                if (edges[j]->getWeight() > edges[j + 1]->getWeight()) {
                    // Swap edges
                    Edge* temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    
        // Step 3: Initialize the Union-Find structure for cycle detection
        UnionFind uf(vertexCount);
    
        // Step 4: Prepare to collect edges in the MST
        Edge** mstEdges = new Edge*[vertexCount - 1];  // The MST will have vertexCount-1 edges
        int mstEdgeCount = 0;
    
        // Step 5: Iterate through the sorted edges and add to MST if no cycle is formed
        for (int i = 0; i < edgeCount && mstEdgeCount < vertexCount - 1; i++) {
            int u = edges[i]->getStart();  // Correctly access the start node
            int v = edges[i]->getEnd();    // Correctly access the end node
            //int w = edges[i]->getWeight(); // Get the weight directly
    
            // If adding this edge doesn't form a cycle, include it in the MST
            if (uf.find(u) != uf.find(v)) {
                uf.unionSets(u, v);
                mstEdges[mstEdgeCount++] = edges[i];  // Add edge to MST
            }
        }
    
        // Step 6: Output the MST (or handle the case where it's not a full MST)
        if (mstEdgeCount != vertexCount - 1) {
            std::cerr << "Warning: The graph is disconnected, MST cannot be formed!" << std::endl;
        } else {
            std::cerr << "Edges in the Minimum Spanning Tree:" << std::endl;
            for (int i = 0; i < mstEdgeCount; i++) {
                std::cerr << mstEdges[i]->getStart() << " - " << mstEdges[i]->getEnd() 
                          << " with weight " << mstEdges[i]->getWeight() << std::endl;
            }
        }
    
        // Step 7: Return the MST as a new graph
        Graph mstGraph(vertexCount);  // Create a new graph for the MST
        for (int i = 0; i < mstEdgeCount; i++) {
            int u = mstEdges[i]->getStart();   // Get the start node
            int v = mstEdges[i]->getEnd();     // Get the end node
            int w = mstEdges[i]->getWeight();  // Get the weight of the edge
    
            // Add the edge to the MST graph using the addEdge function
            mstGraph.addEdge(u, v, w);
        }
    
        // Cleanup
        delete[] mstEdges;
        return mstGraph;
    }

} // namespace graph
