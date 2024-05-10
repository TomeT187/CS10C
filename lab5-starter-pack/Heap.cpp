#include <iostream>
#include "Heap.h"

using namespace std;

Heap::Heap()
  : numItems(0)
{
}

Heap::~Heap() {
  for (int i = 0; i < numItems; i++){
    delete arr[i];
  }
}

void Heap::enqueue(PrintJob* job) {
  if(numItems  == MAX_HEAP_SIZE) {
    return;
  }
  arr[numItems] = job;
  MaxHeapPercolateUp(numItems);
  numItems++;
}

void Heap::dequeue() {
  if(numItems == 0){
    return;
  }
  arr[0] = arr[numItems - 1];
  trickleDown(0);
  numItems--;
}

PrintJob* Heap::highest() {
  if(numItems == 0){
    return nullptr;
  }
  return arr[0];
}

void Heap::print() const {
  if(numItems == 0) throw runtime_error("heap is empty");
  //Priority: priority, Job Number: jobNum, Number of Pages: numPages
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
