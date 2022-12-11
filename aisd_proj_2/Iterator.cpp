#include "Iterator.h"
Iterator::Iterator(int index, int position)
{
    this->index = index;
    this->position = position;
    this->next = NULL;
    this->prev = NULL;
    this->current = NULL;
}