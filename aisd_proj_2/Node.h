#pragma once
#include <iostream>
class Node {
public:
    uint64_t data;
    Node* next;
    Node* prev;

    // Parameterised Constructor
    explicit Node(uint64_t data)
    {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};

