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
        // Stack overflow condition
        return;
    }
    data[++top] = value;
}

int Stack::pop() {
    if (isEmpty()) {
        // Stack underflow condition
        return -1;  // Return an invalid value to indicate underflow
    }
    return data[top--];
}
int Stack::returnTop(){
    return data[top];
}
