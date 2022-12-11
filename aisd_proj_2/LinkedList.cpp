#include "LinkedList.h"

int Linkedlist::getLength() const
{
    Node* temp = head;
    int ListLen = 0;
    while (temp != NULL) {
        temp = temp->next;
        ListLen++;
    }
    return ListLen;
}
/*
void Linkedlist::printIterators() const
{
    Iterator* temp = iteratorHead;
    if (head == NULL)
    {
        cout << "Pusta lista" << endl;
        return;
    }
    printList();
    cout << endl;
    cout << "Head: " << head->data << '(' << head << ')' << " Tail: " << tail->data << '(' << tail << ')' << endl;
    cout << "Head prev: " << head->prev << " Head next: " << head->next << endl;
    cout << "Tail prev: " << tail->prev << " Tail next: " << tail ->next << endl;
    if (temp == NULL)
    {
        cout << "Nie ma zadnych iteratorow." << endl;
        return;
    }
    while (temp != NULL) {
        cout << "Iterator o indeksie: " << temp->index << " wskazuje na element: " << temp->current->data << endl;
        temp = temp->next;
    }
}

*/

//DO POPRAWY
Iterator* Linkedlist::findIterator(int index)
{
    Iterator* temp = iteratorHead;
    if (temp->index == index) return temp;
    while (temp->next!=NULL) {
        if (temp->next->index == index) return temp->next;
        temp = temp->next;
    }

    return NULL; 
}

void Linkedlist::updateIterators(Node* deletedNode, Iterator* iterator)
{
    Iterator* temp = iteratorHead;
    if (head == deletedNode) head = iterator->current;
    if (tail == deletedNode) tail = iterator->current;
    while (temp != NULL)
    {
        if (temp->current == deletedNode)
        {
            if (iterator == NULL)
            {
                if (temp->next == NULL) return;
                temp = temp->next;
                temp->prev = NULL;
            }
            else
            {
                temp->current = iterator->current;
                temp = temp->next;
            }
        }
        else temp = temp->next;
    }
}

// Function to delete the
// node at given position
void Linkedlist::deleteNodeOnIterator(string iteratorIndex)
{
    // Deleting the head.
    if (iteratorIndex == "BEG") {
        // Update head
        Node* deadHead = head;

        if (head->next == NULL)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = head->next;
            head->prev = NULL;
        }

        delete deadHead;
        return;
    }

    //deleting the tail
    if (iteratorIndex == "END")
    {
        Node* deadEnd = tail;
        tail = deadEnd->prev;
        if (tail == NULL) head = NULL;
        else tail->next = NULL;
        delete deadEnd;
        return;
    }

    Iterator* temp = findIterator(atoi(iteratorIndex.c_str()));

    Node* deadNode = temp->current;
    if (deadNode->next == NULL)
    {
        if (deadNode->prev == NULL)
        {
            head = NULL;
            tail = NULL;
            iteratorHead = NULL;
        }
        else
        {
            temp->current = deadNode->prev;
            temp->current->next = NULL;
        }
    }
    else
    {        
        temp->current = temp->current->next;
        if (deadNode->prev != NULL) deadNode->prev->next = temp->current;
        temp->current->prev = deadNode->prev;        
    }
    // Update other iterators with the same node in them
    updateIterators(deadNode, temp);
    // Delete the node
    delete deadNode;
}

void Linkedlist::insertNode(uint64_t data, string iteratorIndex, string& placement)
{
    Node* newNode = new Node(data);
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
        return;
    }
    if (iteratorIndex == "BEG" || iteratorIndex == "END")
    {
        if (iteratorIndex == "BEG")
        {
            if (placement == ".A")
            {
                //replace head
                Node* temp = head;
                head = newNode;
                newNode->next = temp;
                temp->prev = newNode;
                if (head == tail) tail = temp;
            }
            if (placement == "A.")
            {
                Node* temp = head->next;
                head->next = newNode;
                newNode->next = temp;
                newNode->prev = head;
                if (head == tail) tail = newNode;
            }
        }
        if (iteratorIndex == "END")
        {
            if (placement == ".A")
            {
                Node* temp = tail->prev;
                tail->prev = newNode;                
                if (temp == NULL) head = newNode;
                else temp->next = newNode;
                newNode->prev = temp;
                newNode->next = tail;
            }
            if (placement == "A.")
            {
                //replace tail
                Node* temp = tail;
                tail = newNode;
                newNode->prev = temp;
                temp->next = newNode;
            }
        }
    }
    else
    {
        Iterator* iterator = findIterator(atoi(iteratorIndex.c_str()));
        if (placement == ".A")
        {
            Node* temp = iterator->current->prev;
            iterator->current->prev = newNode;
            newNode->prev = temp;
            newNode->next = iterator->current;
            if (temp != NULL) temp->next = newNode;
            else head = newNode;
        }
        if (placement == "A.")
        {
            Node* temp = iterator->current->next;
            iterator->current->next = newNode;
            newNode->next = temp;
            newNode->prev = iterator->current;
            if (temp != NULL) temp->prev = newNode;
            else tail = newNode;
        }
    }
}


//DO POPRAWY
//inserting an iterator at x-th iterator at y position
void Linkedlist::insertIterator(int index, int position)
{    
    Iterator* newIterator = new Iterator(index, position);
    if (iteratorHead == NULL) {
        iteratorHead = newIterator;
    }
    else
    {
        if (findIterator(index) != NULL) return;
        Iterator* temp = iteratorHead;
        while (temp->next != NULL) {
            // Update temp
            temp = temp->next;
        }
        newIterator->prev = temp;
        temp->next = newIterator;
    }

    Node* temp = head;

    if (position == getLength())
    {
        newIterator->current = tail;
    }
    else
    {
        int temppos = 0;
        while (temppos < position) {
            temp = temp->next;
            temppos++;
        }
        newIterator->current = temp;
    }
}

// Function to print the
// nodes of the linked list.
void Linkedlist::printList() const
{
    Node* temp = head;

    // Check for empty list.
    if (head == NULL) {
        return;
    }

    // Traverse the list.
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

void Linkedlist::printNode(int iteratorIndex)
{
    Iterator* iterator = findIterator(iteratorIndex);
    cout << iterator->current->data << endl;
}

void Linkedlist::moveIteratorUp(int index)
{
    Iterator* temp = findIterator(index);
    if (temp->current->next != NULL)
    {
        temp->current = temp->current->next;
    }
}
void Linkedlist::moveIteratorDown(int index)
{
    Iterator* temp = findIterator(index);
    if (temp->current->prev != NULL)
    {
        temp->current = temp->current->prev;
    }
}

Linkedlist::~Linkedlist()
{

    Node* temp1 = head;
    if (temp1 != NULL)
    {
        while (temp1->next != NULL)
        {
            Node* temp2 = temp1;
            temp1 = temp1->next;
            delete temp2;
        }
    }
    
    Iterator* temp3 = iteratorHead;
    if (temp3 != NULL)
    {
        while (temp3->next != NULL)
        {
            Iterator* temp4 = temp3;
            temp3 = temp3->next;
            delete temp4;
        }
    }
    
    
}