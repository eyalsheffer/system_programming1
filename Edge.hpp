#ifndef EDGE_HPP
#define EDGE_HPP

class Edge {
private:
    int start;      
    int end;         
    int weight;      
    Edge* next;      

public:
    Edge();
    explicit Edge(int s, int e, int w); 
    Edge(const Edge& other);

    Edge& operator=(const Edge& other);
    ~Edge();

    int getStart() const;
    int getEnd() const;
    int getWeight() const;
    Edge* getNext() const;

    void setStart(int s);
    void setEnd(int e);
    void setWeight(int w);
    void setNext(Edge* nextEdge);

    void print() const;
};

#endif 
