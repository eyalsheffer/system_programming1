#include "Algorithms.hpp"
#include "Graph.hpp"
#include "UnionFind.hpp"
#include "PriorityQueue.hpp"
#include "Edge.hpp"
#include <iostream>

namespace graph {
    const int INF = 1000000;  
    Algorithms::Algorithms() {}
    Algorithms::~Algorithms() {}

    Graph Algorithms::bfs(Graph& g, int start) {
        int vertixCount = g.getVertexCount();

        if (vertixCount == 0) {
            throw std::invalid_argument("Graph has no vertices.");
        }
    
        if (start < 0 || start >= vertixCount) {
            throw std::out_of_range("Invalid start vertex.");
        }
    
        bool* visited = new bool[vertixCount]{false};  
        int* parent = new int[vertixCount]{-1};       
        int* queue = new int[vertixCount];            
        int front = 0, rear = 0;                    
        Graph bfsGraph(vertixCount);                   
    
        queue[rear++] = start;
        visited[start] = true;
    
        while (front < rear) {
            int current = queue[front++];  
    
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(current, neighborCount);  
    
            if (neighbors == nullptr) {
                std::cerr << "Error: Neighbors are null for node " << current << std::endl;
                break;
            }
    
            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];
    
                if (neighbor >= 0 && neighbor < vertixCount && !visited[neighbor]) {
                    visited[neighbor] = true;               
                    parent[neighbor] = current;           
                    if (rear < vertixCount) {
                        queue[rear++] = neighbor;         
                        bfsGraph.addDirectedEdge(current, neighbor, g.getWeight(current, neighbor));  // Add the edge
                    } else {
                        std::cerr << "Queue overflow!" << std::endl;
                    }
                }
            }
    
            delete[] neighbors;  
        }
    

        delete[] visited;
        delete[] parent;
        delete[] queue;
    
        return bfsGraph;  
    }
    Graph Algorithms::dfs(Graph& g, int start) {
        int vertexCount = g.getVertexCount();
        if (vertexCount == 0) {
            throw std::invalid_argument("Graph has no vertices.");
        }
    
        if (start < 0 || start >= vertexCount) {
            throw std::out_of_range("Invalid start vertex.");
        }
    
        bool* visited = new bool[vertexCount]{false};
        int* parent = new int[vertexCount];
        int* stack = new int[vertexCount];
        int top = -1;
    
        for (int i = 0; i < vertexCount; ++i) {
            parent[i] = -1;
        }
    
        Graph dfsTree(vertexCount);
        stack[++top] = start;
    
        while (top >= 0) {
            int node = stack[top--];
    
            if (visited[node]) continue;
    
            visited[node] = true;
            std::cout << "Visiting node: " << node << std::endl;
    
            if (parent[node] != -1) {
                int weight = g.getWeight(parent[node], node);
                if (weight != -1) {
                    dfsTree.addEdge(parent[node], node, weight);
                }
            }
    
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(node, neighborCount);
            if (neighbors == nullptr) {
                std::cerr << "Error: Neighbors are null for node " << node << std::endl;
                delete[] visited;
                delete[] stack;
                delete[] parent;
                return dfsTree;
            }
    
            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];
    
                if (neighbor == parent[node]) continue;
    
                if (!visited[neighbor]) {
                    parent[neighbor] = node;
                    stack[++top] = neighbor;
                }
            }
    
            delete[] neighbors;
        }
    
        delete[] visited;
        delete[] stack;
        delete[] parent;
        return dfsTree;
    }
    

    Graph Algorithms::dijkstra(Graph& g, int start) {
        int vertexCount = g.getVertexCount();
        int* dist = new int[vertexCount];
        bool* visited = new bool[vertexCount]();
        for (int i = 0; i < vertexCount; ++i) {
            dist[i] = INF;
        }
        
        dist[start] = 0;
        int* pqNode = new int[vertexCount];
        int* pqDist = new int[vertexCount];
        int pqSize = 0;
        pqNode[pqSize] = start;
        pqDist[pqSize++] = 0;
        Graph dijkstraGraph(vertexCount);
        
        while (pqSize > 0) {
            int minIdx = 0;
            for (int i = 1; i < pqSize; ++i) {
                if (pqDist[i] < pqDist[minIdx]) {
                    minIdx = i;
                }
            }
            int node = pqNode[minIdx];
            int distToNode = pqDist[minIdx];
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
                    pqNode[pqSize] = neighbor;
                    pqDist[pqSize++] = dist[neighbor];
                    dijkstraGraph.addEdge(node, neighbor, weight);
                }
            }      
            delete[] neighbors;  
        }
        std::cout << "Distances from start node " << start << ":" << std::endl;
        for (int i = 0; i < vertexCount; ++i) {
            std::cout << "Node " << i << ": " << (dist[i] == INF ? "INF" : std::to_string(dist[i])) << std::endl;
        }
        delete[] dist;
        delete[] visited;
        delete[] pqNode;
        delete[] pqDist;
        return dijkstraGraph;
    }
    
    Graph Algorithms::prim(Graph& g) {
        int vertexCount = g.getVertexCount();
        bool* inMST = new bool[vertexCount]();
        int* key = new int[vertexCount];
        int* parent = new int[vertexCount];
        
        for (int i = 0; i < vertexCount; ++i) {
            key[i] = INF;  // Initialize key values to big nubmer
            parent[i] = -1;  
        }
        
        key[0] = 0;
        int* pqNode = new int[vertexCount];
        int* pqKey = new int[vertexCount];
        int pqSize = 0;
        pqNode[pqSize] = 0; 
        pqKey[pqSize++] = 0;
        Graph mstGraph(vertexCount);
        
        while (pqSize > 0) {
            int minIdx = 0;
            for (int i = 1; i < pqSize; ++i) {
                if (pqKey[i] < pqKey[minIdx]) {
                    minIdx = i;
                }
            }
        
            int u = pqNode[minIdx];
            pqSize--; 
            for (int i = minIdx; i < pqSize; ++i) {
                pqNode[i] = pqNode[i + 1];
                pqKey[i] = pqKey[i + 1];
            }
        
            inMST[u] = true;  
        
            int neighborCount = 0;
            int* neighbors = g.getNeighbors(u, neighborCount);  
            if (neighbors == nullptr) {
                std::cerr << "Error: No neighbors found for node " << u << std::endl;
                continue;  
            }
        
            for (int i = 0; i < neighborCount; ++i) {
                int v = neighbors[i];
                int weight = g.getWeight(u, v);
                if (!inMST[v] && weight < key[v]) { 
                    key[v] = weight;
                    parent[v] = u;
                    pqNode[pqSize] = v;
                    pqKey[pqSize++] = key[v];
                    mstGraph.addEdge(u, v, weight);
                }
            }   
            delete[] neighbors; 
        }
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
        return mstGraph;
    }

    Graph Algorithms::kruskal(Graph& graph) {
        int num_vertices = graph.getVertexCount();
        if (num_vertices == 0) {
            throw std::invalid_argument("Graph has no vertices.");
        }
        UnionFind uf(num_vertices);
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
        Edge** edges = new Edge*[num_edges];  
        int index = 0;
        for (int i = 0; i < num_vertices; ++i) {
            int* adj_vertices = graph.getAdjacentVertices(i);
            int j = 0;
            while (adj_vertices[j] != -1) {
                int v = adj_vertices[j];
                int weight = graph.getWeight(i, v);
                edges[index++] = new Edge(i, v, weight); 
                ++j;
            }
            delete[] adj_vertices;
        }
        for (int i = 0; i < num_edges - 1; ++i) {
            for (int j = 0; j < num_edges - 1 - i; ++j) {
                if (edges[j]->getWeight() > edges[j + 1]->getWeight()) {

                    Edge* temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
        Graph mst(num_vertices);
        for (int i = 0; i < num_edges; ++i) {
            Edge* edge = edges[i];
            int u = edge->getStart();
            int v = edge->getEnd();
    
            if (uf.find(u) != uf.find(v)) {
                mst.addEdge(u, v, edge->getWeight());  
                uf.unionSets(u, v);  
            }
        }
    
        for (int i = 0; i < num_edges; ++i) {
            delete edges[i];  
        }
        delete[] edges; 
    
        return mst;
    }
} 
    
