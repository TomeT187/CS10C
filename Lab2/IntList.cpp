#include "IntList.h"
#include <iostream>
using namespace std;


//createst empty list with two dummy nodes at front and back connected to each other
IntList::IntList(){
    dummyHead = new IntNode(-1);
    dummyTail = new IntNode(-1);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
    dummyHead->prev = nullptr;
    dummyTail->next = nullptr;
}

//calls the pop_front() function until all nodes are deleted
IntList::~IntList(){
    while(!empty()){
        pop_front();
    }
}

//creates new node and places it inbtween the last node and dummyhead
void IntList::push_front(int value){
    IntNode* newNode = new IntNode(value);
    newNode->next = dummyHead->next;
    dummyHead->next->prev = newNode;
    newNode->prev = dummyHead;
    dummyHead->next = newNode;
}

//connects first node's next to the head
//deletes the original first node
void IntList::pop_front(){
    IntNode* nodeToDelete = dummyHead->next;
    dummyHead->next = nodeToDelete->next;
    nodeToDelete->next->prev = dummyHead;
    delete nodeToDelete;
}

//creates new node and places it inbtween the last node and dummytail
void IntList::push_back(int value){
    IntNode* newNode = new IntNode(value);
    newNode->prev = dummyTail->prev;
    dummyTail->prev->next = newNode;
    newNode->next = dummyTail;
    dummyTail->prev = newNode;
}

//connects last node's previous to the tail
//deletes the original last node
void IntList::pop_back(){
    IntNode* nodeToDelete = dummyTail->prev;
    dummyTail->prev = nodeToDelete->prev;
    nodeToDelete->prev->next = dummyTail;
    delete nodeToDelete;
}

//returns true if no nodes are in the list
bool IntList::empty() const{
    return (dummyHead->next == dummyTail);
}

//iterates through the list from the head and adds the value of each node to the 
//stream with spaces in between without at a space at the end
std::ostream & operator<<(std::ostream &out, const IntList &rhs){
    //curr is set to dummyHead's previous and iterated to its next until curr is the dummytail
    for(IntNode* curr = rhs.dummyHead->next; curr != rhs.dummyTail; curr = curr->next){
        out << curr->data;
        if(curr->next != rhs.dummyTail){
            out << " ";
        }
    }
    return out;
}

//iterates through the list starting at the tail and cout's the value of each
//node with a space inbetween until the head is reached
void IntList::printReverse() const{
    //curr is set to dummyTail's previous and iterated to its next until curr is the dummyhead
    for(IntNode* curr = dummyTail->prev; curr != dummyHead; curr = curr->prev){
        cout << curr->data;
        if(curr->prev != dummyHead){
            cout << " ";
        }
    }
}
