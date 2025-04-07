#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

class PriorityQueue {
private:
    int* data;        
    int* priorities;   
    int capacity;     
    int size;          

    void heapifyUp(int index);   
    void heapifyDown(int index); 

public:
    PriorityQueue(int cap);
    ~PriorityQueue();

    void push(int value, int priority);
    void pop();
    int top() const;
    bool isEmpty() const;
    int getSize() const;
};

#endif

