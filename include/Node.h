#pragma once

template<typename T>
struct Node {
    T data;     // STORES THE DATA OF THE NODE
    Node* next; // POINTER TO THE NEXT NODE
    Node* prev; // POINTER TO THE PREVIOUS NODE

    // CONSTRUCTOR TO INITIALIZE A NODE WITH GIVEN DATA
    Node(T data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};
