# Graph Algorithms Project

This project implements several graph algorithms and data structures. It includes the fundamental concepts of graphs, nodes, priority queues, stacks, and union-find data structures. The core functionality is encapsulated in several classes designed to handle graph-related operations and algorithms.

## Classes Overview

### `Graph` Class
The `Graph` class represents an undirected graph using an adjacency list. The graph can have a specified number of vertices, and edges can be added between vertices with a given weight. 

Key functions:
- `addEdge(int start, int end, int weight)`: Adds an edge between two nodes with a specified weight.

- `removeEdge()`: Remove a specified edge.
- `printGraph()`: Prints the graph in terms of its edges and weights.

### `Algorithms` Class
The `Algorithms` class implements various graph algorithms, including traversal algorithms and algorithms for finding the shortest paths or minimum spanning trees. 

Key algorithms:
- `bfs(Graph& g, int start)`: Performs a Breadth-First Search starting from a specified node.
- `dfs(Graph& g, int start)`: Performs a Depth-First Search starting from a specified node.
- `dijkstra(Graph& g, int start)`: Finds the shortest paths from the start node to all other nodes using Dijkstra's algorithm.
- `prim(Graph& g)`: Implements Prim's algorithm to generate a Minimum Spanning Tree (MST) from the graph.
- `kruskal(Graph& g)`: Implements Kruskal's algorithm to generate a Minimum Spanning Tree (MST) from the graph, using union find.

### Other Classes

#### `Node` Class
The `Node` class represents a node in a linked list or a graph. Each node holds some data and a pointer to the next node.

#### `Edge` Class
The `Edge` class represents an edge between two nodes in a graph. It contains the start and end nodes, the weight of the edge, and a pointer to the next edge in the adjacency list.

#### `PriorityQueue` Class
The `PriorityQueue` class implements a priority queue using a heap-based structure. It allows for adding elements with specific priorities and retrieving or removing the element with the highest priority - the minimum value.

Key functions:
- `push(int value, int priority)`: Adds an element with a given priority.
- `pop()`: Removes the highest priority element.
- `top()`: Returns the highest priority element without removing it.
- `isEmpty()`: Checks if the queue is empty.
- `getSize()`: Returns the current size of the queue.

#### `Stack` Class
The `Stack` class implements a simple stack data structure, which operates on a Last-In-First-Out (LIFO) principle.

Key functions:
- `push(int value)`: Adds an element to the stack.
- `pop()`: Removes and returns the top element of the stack.
- `returnTop()`: Returns the top element without removing it.
- `isEmpty()`: Checks if the stack is empty.

#### `UnionFind` Class
The `UnionFind` class implements the union-find data structure. It supports the union and find operations, which are used in  Kruskal's algorithm for finding the Minimum Spanning Tree.

Key functions:
- `find(int x)`: Finds the representative (root) of the set that contains the element `x`.
- `unionSets(int x, int y)`: Unites the sets containing elements `x` and `y`.
- `connected(int x, int y)`: Checks if elements `x` and `y` belong to the same set.

## Compilation Instructions

To compile and run the project using g++ compiler, use the following commands:

### Build the Main Program
```bash
make Main
```
This will compile the necessary object files and link them into an executable named Main.
Run the Main Program
```bash
./Main
```
This will execute the compiled program.
Run Unit Tests
```bash
make test
```
This will compile and run the unit tests using `doctest` for the project.
Run Valgrind (Memory Check)
```bash
make valgrind
```
This will run the Main program with Valgrind to check for memory leaks and other memory-related issues.
Clean Build Files
```bash
make clean
```
This will remove all the object files, executables, and test binaries.
