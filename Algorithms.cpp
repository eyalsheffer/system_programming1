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
    Graph Algorithms::bfs(Graph& g, int start) {
        int vertexCount = g.getVertexCount();
        
        // Validate the graph and start node
        if (vertexCount == 0) {
            throw std::invalid_argument("Graph has no vertices.");
        }
    
        if (start < 0 || start >= vertexCount) {
            throw std::out_of_range("Invalid start vertex.");
        }
        
        // Create a visited array and initialize it to false
        bool* visited = new bool[vertexCount]{false};
        
        // Simulate the queue with a simple array and front, rear pointers
        int* queue = new int[vertexCount];
        int front = 0, rear = 0;
        
        // Create a new graph for the BFS traversal result
        Graph bfsGraph(vertexCount);
        
        // Add the start node to the queue
        queue[rear++] = start;
        visited[start] = true;
        
        while (front < rear) {
            int node = queue[front++];
            std::cout << "Visiting node: " << node << std::endl;
            
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(node, neighborCount);  // Get neighbors of the current node
            
            if (neighbors == nullptr) {
                std::cerr << "Error: Neighbors are null for node " << node << std::endl;
                break;
            }
            
            // Add neighbors to the queue and the new graph
            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    if (rear < vertexCount) {
                        queue[rear++] = neighbor;  // Add the neighbor to the queue
                    } else {
                        std::cerr << "Queue overflow!" << std::endl;
                        break;
                    }
    
                    // Add edge to the new graph
                    bfsGraph.addEdge(node, neighbor, g.getWeight(node, neighbor));
                }
            }
            
            // Cleanup the neighbors array after use
            delete[] neighbors;
        }
        
        // Cleanup dynamically allocated memory for visited and queue arrays
        delete[] visited;
        delete[] queue;
        
        // Return the new graph with the BFS traversal result
        return bfsGraph;
    }
    

    // DFS (Depth-First Search)
    Graph Algorithms::dfs(Graph& g, int start) {
        int vertexCount = g.getVertexCount();
    
        // Validate the graph and start node
        if (vertexCount == 0) {
            throw std::invalid_argument("Graph has no vertices.");
        }
    
        if (start < 0 || start >= vertexCount) {
            throw std::out_of_range("Invalid start vertex.");
        }
        
        // Create a visited array and initialize it to false
        bool* visited = new bool[vertexCount]{false};
        
        // Simulate the stack with a simple array and a top pointer
        int* stack = new int[vertexCount];
        int top = -1;
        
        // Create a new graph for the DFS traversal result
        Graph dfsGraph(vertexCount);
        
        // Push the start node onto the stack
        stack[++top] = start;
        visited[start] = true;
        
        while (top >= 0) {
            int node = stack[top--];  // Pop a node from the stack
            std::cout << "Visiting node: " << node << std::endl;
            
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(node, neighborCount);  // Get neighbors of the current node
            
            if (neighbors == nullptr) {
                std::cerr << "Error: Neighbors are null for node " << node << std::endl;
                break;
            }
            
            // Add neighbors to the stack and the new graph
            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    if (top + 1 < vertexCount) {
                        stack[++top] = neighbor;  // Push the neighbor onto the stack
                    } else {
                        std::cerr << "Stack overflow!" << std::endl;
                        break;
                    }
    
                    // Add edge to the new graph
                    dfsGraph.addEdge(node, neighbor, g.getWeight(node, neighbor));
                }
            }
            
            // Cleanup the neighbors array after use
            delete[] neighbors;
        }
        
        // Cleanup dynamically allocated memory for visited and stack arrays
        delete[] visited;
        delete[] stack;
        
        // Return the new graph with the DFS traversal result
        return dfsGraph;
    }
    
    // Dijkstra's Algorithm (Shortest Path)
    Graph Algorithms::dijkstra(Graph& g, int start) {
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
        
        // Create a new graph for the shortest path results
        Graph dijkstraGraph(vertexCount);
        
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
                    
                    // Add the edge to the new graph (dijkstraGraph) with the updated distance
                    dijkstraGraph.addEdge(node, neighbor, weight);
                }
            }
            
            delete[] neighbors;  // Cleanup
        }
        
        // Output the distances
        std::cout << "Distances from start node " << start << ":" << std::endl;
        for (int i = 0; i < vertexCount; ++i) {
            std::cout << "Node " << i << ": " << (dist[i] == INF ? "INF" : std::to_string(dist[i])) << std::endl;
        }
        
        // Cleanup dynamically allocated memory for dist, visited, pqNode, and pqDist arrays
        delete[] dist;
        delete[] visited;
        delete[] pqNode;
        delete[] pqDist;
        
        // Return the new graph containing the shortest paths
        return dijkstraGraph;
    }
    
    // Prim's Algorithm (Minimum Spanning Tree)
    Graph Algorithms::prim(Graph& g) {
        int vertexCount = g.getVertexCount();
        bool* inMST = new bool[vertexCount]();
        int* key = new int[vertexCount];
        int* parent = new int[vertexCount];
        
        for (int i = 0; i < vertexCount; ++i) {
            key[i] = INF;  // Initialize key values to infinity
            parent[i] = -1;  // Parent of each node is initially -1
        }
        
        key[0] = 0;  // Start with node 0
        
        // Min-heap priority queue manually implemented
        int* pqNode = new int[vertexCount];
        int* pqKey = new int[vertexCount];
        int pqSize = 0;
        
        pqNode[pqSize] = 0;  // Start with node 0
        pqKey[pqSize++] = 0;
        
        // Create a new graph for the Minimum Spanning Tree (MST)
        Graph mstGraph(vertexCount);
        
        while (pqSize > 0) {
            // Find the node with the minimum key
            int minIdx = 0;
            for (int i = 1; i < pqSize; ++i) {
                if (pqKey[i] < pqKey[minIdx]) {
                    minIdx = i;
                }
            }
        
            int u = pqNode[minIdx];
            pqSize--;  // Remove the node from priority queue
        
            // Shift the priority queue to fill the gap
            for (int i = minIdx; i < pqSize; ++i) {
                pqNode[i] = pqNode[i + 1];
                pqKey[i] = pqKey[i + 1];
            }
        
            inMST[u] = true;  // Mark the node as part of the MST
        
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(u, neighborCount);  // Get the neighbors of node u
        
            // Check if neighbors are valid before proceeding
            if (neighbors == nullptr) {
                std::cerr << "Error: No neighbors found for node " << u << std::endl;
                continue;  // Skip to the next iteration if neighbors are not found
            }
        
            for (int i = 0; i < neighborCount; ++i) {
                int v = neighbors[i];
                int weight = g.getWeight(u, v);
        
                if (!inMST[v] && weight < key[v]) {  // If the edge provides a shorter path
                    key[v] = weight;
                    parent[v] = u;
        
                    // Insert the neighbor into the priority queue
                    pqNode[pqSize] = v;
                    pqKey[pqSize++] = key[v];
        
                    // Add the edge to the MST graph (mstGraph)
                    mstGraph.addEdge(u, v, weight);
                }
            }
        
            delete[] neighbors;  // Cleanup the dynamically allocated neighbors array
        }
        
        // Output the minimum spanning tree (MST)
        std::cout << "Edges in the Minimum Spanning Tree:" << std::endl;
        for (int i = 1; i < vertexCount; ++i) {
            if (parent[i] != -1) {
                std::cout << parent[i] << " - " << i << " with weight " << g.getWeight(parent[i], i) << std::endl;
            }
        }
        
        // Cleanup dynamically allocated memory
        delete[] inMST;
        delete[] key;
        delete[] parent;
        delete[] pqNode;
        delete[] pqKey;
        
        // Return the new graph containing the Minimum Spanning Tree (MST)
        return mstGraph;
    }
    // Kruskal's Algorithm (Minimum Spanning Tree using Union-Find)

    
    
    
    Graph Algorithms::kruskal(Graph& graph) {
        int num_vertices = graph.getVertexCount();
        if (num_vertices == 0) {
            throw std::invalid_argument("Graph has no vertices.");
        }
    
        UnionFind uf(num_vertices);
    
        // Get all edges using adjacency list
        // First, we need to count the number of edges
        int num_edges = 0;
        for (int i = 0; i < num_vertices; ++i) {
            int* adj_vertices = graph.getAdjacentVertices(i);
            int j = 0;
            while (adj_vertices[j] != -1) {
                ++num_edges;
                ++j;
            }
            delete[] adj_vertices;
        }
    
        // Create an array to hold the edges
        Edge** edges = new Edge*[num_edges];  // Array of pointers to Edge objects
        int index = 0;
    
        // Fill the edge array with edges from the adjacency list
        for (int i = 0; i < num_vertices; ++i) {
            int* adj_vertices = graph.getAdjacentVertices(i);
            int j = 0;
            while (adj_vertices[j] != -1) {
                int v = adj_vertices[j];
                int weight = graph.getWeight(i, v);
                edges[index++] = new Edge(i, v, weight);  // Create and add edge
                ++j;
            }
            delete[] adj_vertices;
        }
    
        // Sort edges by weight using bubble sort (as std::sort is not allowed)
        for (int i = 0; i < num_edges - 1; ++i) {
            for (int j = 0; j < num_edges - 1 - i; ++j) {
                if (edges[j]->getWeight() > edges[j + 1]->getWeight()) {
                    // Swap pointers, not objects
                    Edge* temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    
        // Create the Minimum Spanning Tree (MST) graph
        Graph mst(num_vertices);
    
        // Add edges to the MST if they don't form a cycle
        for (int i = 0; i < num_edges; ++i) {
            Edge* edge = edges[i];
            int u = edge->getStart();
            int v = edge->getEnd();
    
            if (uf.find(u) != uf.find(v)) {
                mst.addEdge(u, v, edge->getWeight());  // Add edge to MST
                uf.unionSets(u, v);  // Union the sets of u and v to prevent cycle
            }
        }
    
        // Clean up dynamically allocated edges
        for (int i = 0; i < num_edges; ++i) {
            delete edges[i];  // Delete each edge
        }
        delete[] edges;  // Delete the array of pointers
    
        return mst;
    }
} // namespace graph
    
