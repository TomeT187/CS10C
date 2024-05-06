#pragma once
#include <stdexcept>

using std::overflow_error;
using std::runtime_error;
using std::underflow_error;
using std::out_of_range;

#define MAX_SIZE (20)

template<typename T>
class stack {
  T data[MAX_SIZE];
  int size = 0;
public:
  // push(T val): inserts a new element (val) of type T (T could be integer or string)
  // into the data. If the data data is full, this function should throw an overflow_error
  // exception with error message "Called push on full stack.".
  void push(const T& value) {
    if (size == MAX_SIZE) throw overflow_error("Called push on full stack.");
    data[size] = value;
    size++;
  }

  // empty(): returns true if the stack is empty otherwise it returns false.
  bool empty() const { return (size == 0); }

  // pop(): removes the last element from data. If the data array is empty, this function
  // should throw an outofrange exception with error message "Called pop on empty stack.".
  void pop() {
    if (empty()) throw underflow_error("Called pop on empty stack.");
    size--;
  }

  // pop_two(): removes the last two elements from data. If the data array is empty or is
  // of size 1, this function should throw an out_of_range exception. If empty then the error
  // message should be "Called pop_two on empty stack." If the size is 1 then the error
  // message should be "Called pop_two on a stack of size 1.".
  void pop_two() {
    if (empty()) throw out_of_range("Called pop_two on empty stack.");
    if (size == 1) throw out_of_range("Called pop_two on a stack of size 1.");
    size -= 2;
  }

  // PROFPAT: Zybooks doesn't actually use the const version, but it should be
  // PROFPAT: be written for completeness
  // top(): returns the top element of stack (last inserted element). If stack is empty,
  // this function should throw an underflow_error exception with error message
  // "Called top on empty stack.".
  T& top() {
    if (empty()) throw underflow_error("Called top on empty stack.");
    return data[size - 1];
  }
  const T& top() const {
    if (empty()) throw underflow_error("Called top on empty stack.");
    return data[size - 1];
  }
};
