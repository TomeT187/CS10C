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
    for(int i = 0; i < 5; i++){
      if(word1.at(i) != word2.at(i)){
        offCount++;
      }
    }
    return (offCount == 1);
  }

WordLadder::WordLadder(const string& filename) {
  ifstream fin;
  fin.open(filename);
  if(!fin.is_open()) {
    cout << "File not opened" << endl;
    return;
  }
  string word;
  while (fin >> word){
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

  //opens output stream and verified it
  ofstream fout;
  fout.open(outputFile);
  if(!fout.is_open()) {
    cout << "File not opened" << endl;
    return;
  }

  queue<stack<string>> queueOfStacks;
  stack<string> wordsStack;
  wordsStack.push(start);
  queueOfStacks.push(wordsStack);
  string currentWord;
  if(start == end){
    fout << start << endl;
    return;
  }
  while(!queueOfStacks.empty()){
    currentWord = queueOfStacks.front().top();

    // This is how we traverse the std::list dict
    for(auto it = dict.begin(); it != dict.end(); ++it) {
      const string itWord = *it;
      if(offByOne(currentWord,itWord)){
        stack<string> newWordStack =  queueOfStacks.front();
        newWordStack.push(itWord);
        if(itWord == end){
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
  fout << "No Word Ladder Found." << endl;


  
  
  
}
