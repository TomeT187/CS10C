#include "IntList.h"

#include <iostream>
#include <exception>

using namespace std;

// This is just for the throws during the
// development phase... it is a turd once
// you remove all the HERE's
#define STRINGIZE(x) #x
#define STR(x) STRINGIZE(x)
#define HERE ("Broken at\n" __FILE__ ":" STR(__LINE__) ": broken")

#include <iostream>
ostream & operator<<(ostream &out, const IntList &rhs) {
  return out;
}

IntList::~IntList() {
  // You can't actually throw an exception in a destructor "as-is"
  // throw runtime_error(HERE);
}

void IntList::push_front(int value) {
  throw runtime_error(HERE);
}

void IntList::pop_front() {
  throw runtime_error(HERE);
}

void IntList::push_back(int value) {
  throw runtime_error(HERE);
}

void IntList::pop_back() {
  throw runtime_error(HERE);
}

bool IntList::empty() const {
  throw runtime_error(HERE);
}

void IntList::printReverse() const {
  throw runtime_error(HERE);
}

