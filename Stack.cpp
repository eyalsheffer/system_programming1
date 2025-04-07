#include "Stack.hpp"

Stack::Stack(int size) {
    capacity = size;
    data = new int[size];
    top = -1;
}

Stack::~Stack() {
    delete[] data;
}

bool Stack::isEmpty() {
    return top == -1;
}

void Stack::push(int value) {
    if (top == capacity - 1) {
        return;
    }
    data[++top] = value;
}

int Stack::pop() {
    if (isEmpty()) {
        return -1;  
    }
    return data[top--];
}
int Stack::returnTop(){
    return data[top];
}
