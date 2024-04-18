#include "IntList.h"
#include <iostream>
using namespace std;

IntList::IntList(){
    dummyHead = new IntNode(-1);
    dummyTail = new IntNode(-1);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
    dummyHead->prev = nullptr;
    dummyTail->next = nullptr;
}

IntList::~IntList(){
    while(!empty()){
        pop_front();
    }
}

void IntList::push_front(int value){
    IntNode* newNode = new IntNode(value);
    newNode->next = dummyHead->next;
    dummyHead->next->prev = newNode;
    newNode->prev = dummyHead;
    dummyHead->next = newNode;
}

void IntList::pop_front(){
    IntNode* nodeToDelete = dummyHead->next;
    dummyHead->next = nodeToDelete->next;
    nodeToDelete->next->prev = dummyHead;
    delete nodeToDelete;
}

void IntList::push_back(int value){
    IntNode* newNode = new IntNode(value);
    newNode->prev = dummyTail->prev;
    dummyTail->prev->next = newNode;
    newNode->next = dummyTail;
    dummyTail->prev = newNode;
}

void IntList::pop_back(){
    IntNode* nodeToDelete = dummyTail->prev;
    dummyTail->prev = nodeToDelete->prev;
    nodeToDelete->prev->next = dummyTail;
}

bool IntList::empty() const{
    return (dummyHead->next == dummyTail);
}

std::ostream & operator<<(std::ostream &out, const IntList &rhs){
    for(IntNode* curr = rhs.dummyHead->next; curr != rhs.dummyTail; curr = curr->next){
        out << curr->data;
        if(curr->next != rhs.dummyTail){
            out << " ";
        }
    }
    return out;
}

void IntList::printReverse() const{
    for(IntNode* curr = dummyTail->prev; curr != dummyHead; curr = curr->prev){
        cout << curr->data;
        if(curr->prev != dummyHead){
            cout << " ";
        }
    }
}
