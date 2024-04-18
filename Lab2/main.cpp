#include <iostream>
#include "IntList.h"
using namespace std;

int main(){
    IntList testList;
    testList.push_front(1);
    testList.push_front(2);
    testList.push_front(3);
    testList.push_front(4);
    cout << testList << endl;
    //cout << "Is empty: " << testList.empty() << endl;


    testList.push_back(1);
    testList.push_back(2);
    testList.push_back(3);
    testList.push_back(4);
    cout << testList << endl;

    testList.push_front(5);
    testList.push_back(5);
    cout << testList << endl;

    testList.pop_front();
    testList.pop_front();
    testList.pop_front();
    testList.pop_front();
    testList.pop_front();
    cout << testList << endl;

    testList.pop_back();
    testList.pop_back();
    testList.pop_back();
    testList.pop_back();
    
    cout << testList << endl;
    
    testList.push_back(2);
    testList.push_back(3);
    testList.push_back(4);
    testList.push_back(5);
    testList.printReverse();
    cout << "no new line or space" << endl;

    testList.pop_back();
    testList.pop_back();
    testList.pop_back();
    testList.pop_back();
    testList.pop_back();

    cout << "Empty List: " << testList << endl;
    cout << "Is empty: " << testList.empty() << endl;
    return 0;
}