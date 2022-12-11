// Driver Code
#include "LinkedList.h"
int main()
{
    Linkedlist list;
    string input;
    while (cin >> input)
    {
        if (input == "I")
        {
            //nothing
        }
        if (input == "i")
        {
            int iteratorIndex;
            string iteratorPos;            
            cin >> iteratorIndex >> iteratorPos;
            if (iteratorPos == "BEG" || iteratorPos == "END")
            {
                if(iteratorPos == "BEG") list.insertIterator(iteratorIndex, 0);
                if(iteratorPos == "END") list.insertIterator(iteratorIndex, list.getLength());
            }
            else list.insertIterator(iteratorIndex, atoi(iteratorPos.c_str()));
        }
        if (input == "+")
        {
            int iteratorIndex;
            cin >> iteratorIndex;
            list.moveIteratorUp(iteratorIndex);
        }
        if (input == "-")
        {
            int iteratorIndex;
            cin >> iteratorIndex;
            list.moveIteratorDown(iteratorIndex);
        }
        if (input == ".A")
        {
            string iteratorIndex;
            uint64_t data;
            cin >> iteratorIndex >> data;
            list.insertNode(data, iteratorIndex, input);
        }
        if (input == "A.")
        {
            string iteratorIndex;
            uint64_t data;
            cin >> iteratorIndex >> data;
            list.insertNode(data, iteratorIndex, input);
        }
        if (input == "R")
        {
            string iteratorIndex;
            cin >> iteratorIndex;
            list.deleteNodeOnIterator(iteratorIndex);
        }
        if (input == "P")
        {
            string command;
            cin >> command;
            if (command == "ALL") list.printList();
            else
            {
                int listElement = atoi(command.c_str());
                list.printNode(listElement);
            }            
        }
        //list.printIterators();
    }
    return 0;
}