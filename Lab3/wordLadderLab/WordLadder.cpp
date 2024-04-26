#include "WordLadder.h"

#include <iostream>
#include <fstream>

// This gives us access to std::stack and std::queue.  
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

bool WordLadder::offByOne(const string& word1, const string& word2) const{
    int offCount = 0;
    //compares the letters at i of each string
    for(int i = 0; i < 5; i++){
      if(word1.at(i) != word2.at(i)){
        offCount++;
      }
    }
    return (offCount == 1);
  }

//opens an input file stream for the dictionary and confirms it is open
//iterates through each word in the dictionary and confirms the word 
//  correctly extracted and is the correct length
WordLadder::WordLadder(const string& filename) {
  ifstream fin;
  fin.open(filename);
  if(!fin.is_open()) {
    cout << "File not opened" << endl;
    return;
  }
  string word;
  //extracts a word from the given file and adds it to the dict list
  while (fin >> word){
    //if a word did not extract correctlly or the word is not the correct length
    //  outputs an error message and returns early
    if(fin.fail() || word.size() != 5) {
      cout << "Word is not size 5 or extraction failed" << endl;
      return;
    }
    dict.push_back(word);
  }
  

}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  
  //verifies both words are in the dictionary
  if (!(std::find(dict.begin(),dict.end(),start) != dict.end())) {
     cout << start << " is in not in dictionary" << endl;
     return;
  }
  if (!(std::find(dict.begin(),dict.end(),end) != dict.end())) {
     cout << end << " is in not in dictionary" << endl;
     return;
  }

  //opens output stream and verified it opened correctly
  ofstream fout;
  fout.open(outputFile);
  if(!fout.is_open()) {
    cout << "File not opened" << endl;
    return;
  }
  //sets up queue to have one stack containing the starting word
  queue<stack<string>> queueOfStacks;
  stack<string> wordsStack;
  wordsStack.push(start);
  queueOfStacks.push(wordsStack);
  string currentWord;

  //edge case if the start is the same as the end word
  if(start == end){
    fout << start << endl;
    return;
  }

  //while the queue has a possible word ladder in it
  while(!queueOfStacks.empty()){
    currentWord = queueOfStacks.front().top();//the word at the top of the first stack in the queue

    //iterates through each word in the dict list
    //if the word is off by exactly one letter a new stack is added to the queue with this word on the top
    //  this word is then removed from the dict  
    for(auto it = dict.begin(); it != dict.end(); ++it) {
      const string itWord = *it;
      if(offByOne(currentWord,itWord)){
        stack<string> newWordStack =  queueOfStacks.front();
        newWordStack.push(itWord);
        if(itWord == end){
        //if the current word in the dict is the same as the end word
          //outputs the word ladder to the given file and returns
          string wordLadderString = "";
          while(!newWordStack.empty()){
            wordLadderString = newWordStack.top() +"\n" + wordLadderString ;
            newWordStack.pop();
          }
          fout << wordLadderString;
          return;
        }
        else{
          queueOfStacks.push(newWordStack);
          it = dict.erase(it);
          it--;
        }
      }
    }
    queueOfStacks.pop();
  }
  //only executes if the queue is emptied without a word ladder  found
  fout << "No Word Ladder Found." << endl;
}
