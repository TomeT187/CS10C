#include <iostream>
#include "Heap.h"

using namespace std;

Heap::Heap()
  : numItems(0)
{
}

//calls dequeue until all items are removed
Heap::~Heap() {
  while(numItems > 0){
    dequeue();
  }
}
//places new node at the bottom of the heap
//percolates up until in the correct position
void Heap::enqueue(PrintJob* job) {
  if(numItems  == MAX_HEAP_SIZE) {
    return;
  }
  arr[numItems] = job;
  MaxHeapPercolateUp(numItems);
  numItems++;
}

//removes node at the top of the heap and calls delete on the pointer
//takes lowest node and replaces it
//percolates the node down until in the correct position
void Heap::dequeue() {
  if(numItems == 0){
    return;
  }
  delete arr[0];
  arr[0] = arr[numItems - 1];
  trickleDown(0);
  numItems--;
  
  
}
//returns the value at the top of the heap
PrintJob* Heap::highest() {
  if(numItems == 0){
    return nullptr;
  }
  return arr[0];
}

//prints node at the top of the heap as followed: Priority: priority, Job Number: jobNum, Number of Pages: numPages and ends with a newline
void Heap::print() const {
  if(numItems == 0) throw runtime_error("heap is empty");
  cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " 
          << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages() << endl;
}


//taken from zybooks
void Heap::MaxHeapPercolateUp(int nodeIndex) {
  int parentIndex;
  PrintJob* swapHolder;
   //loops until you reach the top
   while (nodeIndex > 0) {
      parentIndex = (nodeIndex - 1) / 2;
      //if node is smaller than its parent: do nothing
      if (arr[nodeIndex]->getPriority() <= arr[parentIndex]->getPriority())
         return;
      else {
        //swaps node and its parent
        swapHolder = arr[nodeIndex];
        arr[nodeIndex] = arr[parentIndex];
        arr[parentIndex] = swapHolder;
        nodeIndex = parentIndex;
      }
   }
}

void Heap::trickleDown(int nodeIndex){
  int childIndex = 2 * nodeIndex + 1;
  int value = arr[nodeIndex]->getPriority();

  int maxValue;
  int maxIndex;
  PrintJob* swapHolder;

  //while the end of the array has not been reached
  while (childIndex < numItems) {
      // Find the max among the node and all the node's children
      maxValue = value;
      maxIndex = -1;
      for (int i = 0; i < 2 && i + childIndex < numItems; i++) {
         if (arr[i + childIndex]->getPriority() > maxValue) {
            maxValue = arr[i + childIndex]->getPriority();
            maxIndex = i + childIndex;
         }
      }
      //do nothing if values are the same
      if (maxValue == value) {
         return;
      }
      //swaps parent with child 
      else {
        swapHolder = arr[nodeIndex];
        arr[nodeIndex] = arr[maxIndex];
        arr[maxIndex] = swapHolder;
        nodeIndex = maxIndex;
        childIndex = 2 * nodeIndex + 1;
      }
   }

}
