#ifndef EDGE_HPP
#define EDGE_HPP

class Edge {
private:
    int start;       // Start node of the edge
    int end;         // End node of the edge
    int weight;      // Weight of the edge
    Edge* next;      // Pointer to the next edge in the adjacency list

public:
    // Default constructor
    Edge();

    // Parameterized constructor
    explicit Edge(int s, int e, int w);  // Start, End, and Weight

    // Copy constructor (Rule of Three)
    Edge(const Edge& other);

    // Copy assignment operator (Rule of Three)
    Edge& operator=(const Edge& other);

    // Destructor
    ~Edge();

    // Getter functions
    int getStart() const;
    int getEnd() const;
    int getWeight() const;
    Edge* getNext() const;

    // Setter functions
    void setStart(int s);
    void setEnd(int e);
    void setWeight(int w);
    void setNext(Edge* nextEdge);

    // Print function to display edge information
    void print() const;
};

#endif // EDGE_HPP
