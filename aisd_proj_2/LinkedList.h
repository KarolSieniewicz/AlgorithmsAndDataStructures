#pragma once
#include <iostream>
#include <string>
#include "Node.h"
#include "Iterator.h"
using namespace std;
class Linkedlist {
    Node* head;
    Node* tail;
    Iterator* iteratorHead;
public:
    // Default constructor
    Linkedlist() { head = NULL; iteratorHead = NULL; tail = NULL; }

    // Function to insert an interator of x number at y position
    void insertIterator(int, int);

    void updateIterators(Node*, Iterator*);

    //finding nodes and iterators
    Iterator* findIterator(int);

    //void printIterators() const;

    //obsluga +x -x
    void moveIteratorUp(int);
    void moveIteratorDown(int);

    //obsluga dodawania data
    void insertNode(uint64_t, string, string&);

    //obsluga usuwania na iteratorze
    void deleteNodeOnIterator(string);
    
    int getLength() const;
    
    // Function to print the
    // linked list.
    void printList() const;
    void printNode(int);

    ~Linkedlist();
};