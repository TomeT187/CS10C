#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::sort;

using std::clock_t;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

// If using C++ 14, this is better as constexpr
const int NUMBERS_SIZE = 50000;

// Provided by zybooks
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

// Provided by zybooks
void fillArrays(int arr1[], int arr2[],int arr3[]) {
  for(int i = 0; i < NUMBERS_SIZE; ++i){
    arr1[i] = genRandInt(0,NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}

int QPartition(int numbers[], int midPoint, int low, int high) {
  int pivot = numbers[midPoint];

  bool done = false;
  while(!done){
    //find value greater than pivot in the first partition
    while(numbers[low] < pivot){
      low++;
    }
    //find value lower than pivot in the second partition
    while(pivot < numbers[high]){
      high--;
    }
    //if low crossed high 
    if(low >= high){
      done = true;
    }
    else{
      //swap low and high
      int oldLow = numbers[low];
      numbers[low] = numbers[high];
      numbers[high] = oldLow;

      low++;
      high--;
    }
  }
  return high;

}

void Quicksort_midpoint(int numbers[], int low, int high) {
  if(low >= high){
    return;
  }
  //set midpoint to be middle value
  //partition current values and cut in half
  int midPoint = low + (high - low) / 2;
  int lowEndIndex = QPartition(numbers,midPoint,low,high);
  Quicksort_midpoint(numbers,low,lowEndIndex);
  Quicksort_midpoint(numbers,lowEndIndex + 1,high);
}

void Quicksort_medianOfThree(int numbers[], int low, int high) {
  if(low >= high){
    return;
  }

  //determins which value to use for the pivot
  int pivotIndex = 0;
  int midPoint = low + (high - low) / 2;
  if(numbers[low] < numbers[midPoint] && numbers[midPoint] < numbers[high] ){
    pivotIndex = midPoint;
  }else if(numbers[midPoint] < numbers[low]  && numbers[low] < numbers[high])  {
    pivotIndex = low;
  }else{
    pivotIndex = high;
  }
  
  int lowEndIndex = QPartition(numbers,pivotIndex,low,high);
  Quicksort_midpoint(numbers,low,lowEndIndex);
  Quicksort_midpoint(numbers,lowEndIndex + 1,high);
}

void InsertionSort(int numbers[], int numbersSize) {
  for(int i = 0; i < numbersSize; i++){
    int inserted = i;
    //while numbers[inserted] is not at the end and less than the previous index
    while(inserted > 0 && numbers[inserted] < numbers[inserted - 1]) {
      //swaps numbers[inserted] with the one before it and decreases inserted
      int swapHolder = numbers[inserted];
      numbers[inserted] = numbers[inserted - 1];
      numbers[inserted - 1] = swapHolder;
      --inserted;
    }
  }
}


// A helper function that will let us know if we have sorted
// everything
static bool is_sorted(int numbers[], int numbersSize) {
  if (numbersSize <= 0) return true;
  int last = numbers[0];
  for(int i=0; i < numbersSize; ++i) {
    int curr = numbers[i];
    if (curr < last) return false;
    last = curr;
  }
  return true;
}

static void copy_vector_into_array(const std::vector<int>& source, int array[]) {
  for(int i=0;i<static_cast<int>(source.size()); ++i) {
    array[i] = source[i];
  }
}

int main() {
  // I'm going to use the same array every time for all the
  // functions.  This is different than the Zybooks suggestion
  // but will give us more consistent timings
  std::vector<int> sample;
  sample.reserve(NUMBERS_SIZE);
  for(int i=0; i<NUMBERS_SIZE; ++i) {
    sample.push_back(rand() % (NUMBERS_SIZE + 1));
  }
  
  // We'll run our tests across a bunch of sizes
  int test_sizes[4] = { 10, 100, 1000, 50000 };
  int test_array[NUMBERS_SIZE];
  for(int i=0; i<4; ++i) {
    int size = test_sizes[i];
    cout << endl;
    cout << "-------------------- size " << size << " --------------------" << endl;

    // Insertion Sort
    {
      copy_vector_into_array(sample, test_array);
       clock_t Start = clock();
      InsertionSort(test_array, size);
       clock_t End = clock();
       int elapsedTime = (End - Start)/CLOCKS_PER_MS;
       cout << elapsedTime << " ms" << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // QuickSort MidPartition
    {
      copy_vector_into_array(sample, test_array);

       clock_t Start = clock();
      Quicksort_midpoint(test_array, 0, size);
       clock_t End = clock();
       int elapsedTime = (End - Start)/CLOCKS_PER_MS;
       cout << elapsedTime << " ms" << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // Quicksort median of three
    {
      copy_vector_into_array(sample, test_array);

       clock_t Start = clock();
      Quicksort_medianOfThree(test_array, 0,size);
       clock_t End = clock();
       int elapsedTime = (End - Start)/CLOCKS_PER_MS;
       cout << elapsedTime << " ms" << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
  }
  return 0;
}
