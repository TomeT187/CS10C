#include "HashTable.h"
#include "WordEntry.h"



/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
  size = s;
  hashTable = new list<WordEntry>[size];
}


int HashTable::computeHash(const string &str) const {
  int mod = size;

  //Written by chat GPT
  //Prompt: write a simple hash function in c++ that takes in a string 
  const unsigned int prime = 31;
  unsigned int hash = 0;
  unsigned int power = 1;

  for (char c : str) {
      hash = (hash + (c * power) % mod) % mod;
      power = (power * prime) % mod;
  }
  return hash;
}


/* 
*  checks if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it to the back
*/
void HashTable::put(const string &s, int score) {
  // expected slot for word
  int h = computeHash(s);
  //iterates through the slot
  for(WordEntry& entry:hashTable[h]){
    //if found: adds new appearance with the score
    if(entry.getWord() == s){
      entry.addNewAppearance(score);
      return;
    }
  }
  //else adds new word to the list
  WordEntry newWord(s,score);
  hashTable[h].push_back(newWord);
}


/* 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  If not found, return the value 2.0 (neutral result)
*/
double HashTable::getAverage(const string &s) const {
  // expected slot for word
  int h = computeHash(s);
  //iterates through the slot
  for(WordEntry& entry:hashTable[h]){
    //if found: returns the average of the slot
    if(entry.getWord() == s){
      return entry.getAverage();
    }
  }
  //else returns default
  return 2.0;
}

/* 
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) const {
  // expected slot for word
  int h = computeHash(s);
  //iterates through the slot
  for(WordEntry& entry:hashTable[h]){
      //returns true if found
    if(entry.getWord() == s){
      return true;
    }
  }
  //else returns false
  return false;
}

