#pragma once
#include "Node.h"
class Iterator
{
public:
	int position;
    int index;
    Iterator* next;
    Iterator* prev;
    Node* current;
    Iterator(int, int);
};

