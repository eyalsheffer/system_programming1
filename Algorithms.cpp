#include "Algorithms.hpp"
#include <iostream>

namespace graph {

    // Define a large number to represent "infinity"
    const int INF = 1000000;  // Custom infinity value

    // Constructor (no data to initialize)
    Algorithms::Algorithms() {}

    // Destructor (no special cleanup needed)
    Algorithms::~Algorithms() {}

    // BFS (Breadth-First Search)
    Graph Algorithms::bfs(Graph g, int start) {
        int vertexCount = g.getVertexCount();
        bool* visited = new bool[vertexCount]();  // Initialize visited array to false
        int* queue = new int[vertexCount];         // Array to simulate queue
        int front = 0, rear = 0;                  // Front and rear of the queue
        queue[rear++] = start;
        visited[start] = true;

        while (front < rear) {
            int node = queue[front++];
            std::cout << "Visiting node: " << node << std::endl;

            int neighborCount = 0;
            int* neighbors = g.getNeighbors(node, neighborCount);

            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue[rear++] = neighbor;  // Add neighbor to the queue
                }
            }

            delete[] neighbors;  // Cleanup
        }

        delete[] visited;
        delete[] queue;
        return g;
    }

    // DFS (Depth-First Search)
    Graph Algorithms::dfs(Graph g, int start) {
        int vertexCount = g.getVertexCount();
        bool* visited = new bool[vertexCount]();  // Initialize visited array to false
        int* stack = new int[vertexCount];         // Array to simulate stack
        int top = -1;                             // Top of the stack
        stack[++top] = start;
        visited[start] = true;

        while (top >= 0) {
            int node = stack[top--];
            std::cout << "Visiting node: " << node << std::endl;

            int neighborCount = 0;
            int* neighbors = g.getNeighbors(node, neighborCount);

            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    stack[++top] = neighbor;  // Add neighbor to the stack
                }
            }

            delete[] neighbors;  // Cleanup
        }

        delete[] visited;
        delete[] stack;
        return g;
    }

    // Dijkstra's Algorithm (Shortest path algorithm)
    Graph Algorithms::dijkstra(Graph g, int start) {
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
        return g;
    }

    // Prim's Algorithm (Minimum Spanning Tree using Greedy approach)
    Graph Algorithms::prim(Graph g, int start) {
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
        return g;
    }

    // Kruskal's Algorithm (Minimum Spanning Tree using Union-Find)
    Graph Algorithms::kruskal(Graph g, int start) {
        // Kruskal's algorithm needs to return the MST
        // Assuming we have a Union-Find structure implemented elsewhere
        // You can implement Kruskal's algorithm using your UnionFind class here

        // Here is a placeholder:
        std::cout << "Kruskal's Algorithm is yet to be implemented." << std::endl;

        return g;
    }

} // namespace graph
