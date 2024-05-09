#include <iostream>
#include "Heap.h"

using namespace std;

Heap::Heap()
  : numItems(0)
{
}

Heap::~Heap() {
  delete[] arr;
}
//Other rule of three stuff too!


void Heap::enqueue(PrintJob* job) {
  if(numItems == MAX_HEAP_SIZE) throw runtime_error("heap is full");
  arr[numItems] = job;
  MaxHeapPercolateUp(numItems);
  numItems++;

}

void Heap::dequeue() {
  if(numItems == 0) throw runtime_error("heap is empty");
  arr[0] = arr[numItems - 1];
  trickleDown(0);
  numItems--;

}

PrintJob* Heap::highest() {
  return arr[0];
}

void Heap::print() const {
  //Priority: priority, Job Number: jobNum, Number of Pages: numPages
  cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " 
          << arr[0]->getJobNumber() << ", Number of Pages:" << arr[0]->getPages() << endl;
}


//taken from zybooks
void Heap::MaxHeapPercolateUp(int nodeIndex) {
  int parentIndex;
  PrintJob* swapHolder;
   while (nodeIndex > 0) {
      parentIndex = (nodeIndex - 1) / 2;
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
  
}