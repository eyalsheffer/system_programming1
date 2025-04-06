#include "PriorityQueue.hpp"
#include <iostream>
#include <stdexcept>

PriorityQueue::PriorityQueue(int cap) : capacity(cap), size(0) {
    data = new int[capacity];
    priorities = new int[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] data;
    delete[] priorities;
}

void PriorityQueue::heapifyUp(int index) {
    while (index > 0 && priorities[index] < priorities[(index - 1) / 2]) {
        // Swap the data and priorities
        std::swap(data[index], data[(index - 1) / 2]);
        std::swap(priorities[index], priorities[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void PriorityQueue::heapifyDown(int index) {
    int leftChild, rightChild, smallest;

    while (index * 2 + 1 < size) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        smallest = index;

        if (leftChild < size && priorities[leftChild] < priorities[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < size && priorities[rightChild] < priorities[smallest]) {
            smallest = rightChild;
        }

        if (smallest == index) break;

        std::swap(data[index], data[smallest]);
        std::swap(priorities[index], priorities[smallest]);
        index = smallest;
    }
}

void PriorityQueue::push(int value, int priority) {
    if (size == capacity) {
        std::cerr << "PriorityQueue is full!" << std::endl;
        return;
    }

    // Insert new value and priority at the end of the heap
    data[size] = value;
    priorities[size] = priority;

    // Restore the heap property by moving the new element up
    heapifyUp(size);
    size++;
}

void PriorityQueue::pop() {
    if (isEmpty()) {
        std::cerr << "PriorityQueue is empty!" << std::endl;
        return;
    }

    // Move the last element to the root
    data[0] = data[size - 1];
    priorities[0] = priorities[size - 1];
    size--;

    // Restore the heap property by moving the root element down
    heapifyDown(0);
}

int PriorityQueue::top() const {
    if (isEmpty()) {
        throw std::underflow_error("PriorityQueue is empty!");
    }

    return data[0]; // Return the element with the highest priority (root of the heap)
}

bool PriorityQueue::isEmpty() const {
    return size == 0;
}

int PriorityQueue::getSize() const {
    return size;
}
