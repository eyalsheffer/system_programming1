#ifndef STACK_HPP
#define STACK_HPP

class Stack {
private:
    int* data;
    int top;
    int capacity;

public:
    Stack(int size);
    ~Stack();

    bool isEmpty();
    void push(int value);
    int pop();
};

#endif
