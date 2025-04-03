#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

class PriorityQueue {
private:
    int* data;         // Array to store the data
    int* priorities;   // Array to store the priorities of the data
    int capacity;      // Current capacity of the arrays
    int size;          // Current size of the queue

    void heapifyUp(int index);   // Restore heap property by moving element up
    void heapifyDown(int index); // Restore heap property by moving element down

public:
    // Constructor
    PriorityQueue(int cap);

    // Destructor
    ~PriorityQueue();

    // Adds an element to the queue with a specified priority
    void push(int value, int priority);

    // Removes the highest priority element from the queue
    void pop();

    // Returns the element at the front of the queue
    int top() const;

    // Returns true if the queue is empty
    bool isEmpty() const;

    // Returns the size of the queue
    int getSize() const;
};

#endif

