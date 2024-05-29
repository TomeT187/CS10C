#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
  // Caution: Code turd comments below!
  // NOTE: The hashtable is a dynamically allocated ARRAY OF LISTS OF WORDENTRIES
  // that is why it is a pointer and you'll use new to allocate it.
  // If it was an array of int, you would use new int[size] to make it..
  // Here, each element (slot) is a list<WordEntry>....
  // 
  // Since each hashtable slot is a linked list... what is our collision
  // strategy????
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*
*  Code turd alert!
*  Pick a better hash function here -- feel free to explore
*  various options (this one is pretty bad!
*  Feel free to ask ChatGPT to write a hash function for you.  Vary the
*  prompts to get an interesting one.
*
*  Does this one work though?  Does it work well?  Can you notice the difference
*  if you use the full movie database vs the sample?
*/
int HashTable::computeHash(const string &s) const {
  return 3 % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
  // Code turd:
  // add the string and score to your hashtable...
  // How should you handle collisions?  What if the
  // string is already in your overflow chain?
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/
double HashTable::getAverage(const string &s) const {
  // Code turd:
  // Obviously, you have to compute the average and not just use the default
  return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) const {
  // Code turd:
  // Obviously, it should return true if you are holding the word!
  return false;
}

