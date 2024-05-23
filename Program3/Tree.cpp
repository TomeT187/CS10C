#include "Tree.h"
#include <iostream>
#include <string>

using namespace std;

static const string& midStr( const string& s1, const string& s2, const string& s3 ) {
  if (( s1 < s2 && s1 > s3 ) ||( s1 < s3 && s1 > s2 ) ) 
    return s1;
  else if (( s2 < s1 && s2 > s3 ) ||( s2 < s3 && s2 > s1 ) ) 
    return s2;
  else 
    return s3;
}

static const string& minStr( const string& s1, const string& s2, const string& s3 ) {
  if ( s1 < s2 && s1 < s3 ) 
    return s1;
  else if ( s2 < s1 && s2 < s3 ) 
    return s2;
  else
    return s3;
}

static const string& maxStr( const string& s1, const string& s2, const string& s3 ) {
  if ( s1 > s2 && s1 > s3 ) 
    return s1;
  else if ( s2 > s1 && s2 > s3 ) 
    return s2;
  else
    return s3;
}

Tree::Tree() {
  root = NULL;
}

Tree::~Tree() {
  destructorHelper(root);
}

void Tree::destructorHelper(Node* target){
  if(target == nullptr) return;
  destructorHelper(target->left);
  destructorHelper(target->middle);
  destructorHelper(target->right);
  delete target;
}


bool Tree::noChildren( Node* node ) const {
  return (node->left == nullptr);
}

void Tree::insert( const string& word ) {
  if ( root == nullptr ) {
    root = new Node( word );
  } else {
    root = insert( root, word );
  }
}

Node* Tree::insert( Node* curr, const string& word ) {
  //if a leaf
  if(noChildren(curr)){
    // there is room
    if(curr->numData == 1){
      addData(curr,word);
      return curr;
    }else{//there isnt room -> explosion needed
      if(curr->parent == nullptr){//exploding root
      Node* leftChild = new Node(minStr(curr->small,word,curr->large));
      leftChild->parent = curr;
      Node* rightChild = new Node(maxStr(curr->small,word,curr->large));
      rightChild->parent = curr;
      curr->numData = 1;
      curr->left = leftChild;
      curr->middle = rightChild;
      curr->right = nullptr;
      curr->small = midStr(curr->small,word,curr->large);
      return curr;
      }else{//exploding non root
        if(curr->parent->numData == 1){
          string min = minStr(curr->small,word,curr->large);
          string mid = midStr(curr->small,word,curr->large);
          string max = maxStr(curr->small,word,curr->large);
          
          //creates new children nodes for the new root and deletes the original node
          //returns the new root
          Node* leftChild = new Node(min);
          leftChild->parent = curr->parent;
          Node* rightChild = new Node(max);
          rightChild->parent = curr->parent;
          if(word < curr->parent->small){
            curr->parent->left = leftChild;
            curr->parent->right = curr->parent->middle;
            curr->parent->middle = rightChild;
          }else{
            curr->parent->middle = leftChild;
            curr->parent->right = rightChild;
          }
          addData(curr->parent,mid);
          Node* newRoot = curr->parent;
          delete curr;
          return newRoot;
          
          

        }else{
          throw runtime_error("Sending a value to a parent with more than one data point unfinished");
        }
      }
    }
  }else{//not a leaf
  //each case for if the value should be in the left middle or right
    if(word < curr->small){
      if(curr->left->numData == 2){
        return insert(curr->left,word);
      }
      curr->left = insert(curr->left,word);
      return curr;
    }else if(curr->numData == 2 && word < curr->large){
      
      curr->right = insert(curr->right, word);
      return curr;
    }else{
      if(curr->middle->numData == 2){
        return insert(curr->middle,word);
      }
      curr->middle = insert(curr->middle, word);
      return curr;
    }
  }
}

void Tree::addData( Node* addHere, const string& word ) {
  //compares each value and places in the correct spot
  if(addHere->small < word){
    addHere->large = word;
  }else{
    addHere->large = addHere->small;
    addHere->small = word;
  }
  addHere->numData++;
}

void Tree::preOrder() const {
  preOrder( root );
  cout << endl;
}

void Tree::preOrder( const Node* curr ) const {
  if(curr == nullptr) return;
  cout << curr->small << ", ";
  if(curr->numData == 2){
    cout << curr->large << ", ";
  }
  preOrder(curr->left);
  preOrder(curr->middle);
  preOrder(curr->right);
}

void Tree::inOrder() const {
  inOrder( root );
  cout << endl;
}

void Tree::inOrder(const Node* curr) const {
  if(curr == nullptr) return;
  inOrder(curr->left);
  cout << curr->small << ", ";
  inOrder(curr->middle);
  if(curr->numData == 2){
    cout << curr->large<< ", ";
  }
  inOrder(curr->right);
}

void Tree::postOrder() const {
  postOrder( root );
  cout << endl;
}

void Tree::postOrder(const Node* curr) const {
  if(curr == nullptr) return;
  postOrder(curr->left);
  postOrder(curr->middle);
  postOrder(curr->right);
  cout << curr->small << ", ";
  if(curr->numData == 2){
    cout << curr->large << ", ";
  }
}

void Tree::remove(const string& word) {
  // Nothing to do in an empty tree, just return
  if ( !root ){
    return;
  }else{
    //if the value is not found do nothing
    Node* searchResult = search(word);
    if(searchResult == nullptr){
      return;
    }
    //if the value is in the root
    if(searchResult == root){
      if(noChildren(root)){//if the value is the only key set the root to nulltpr
        if(root->numData == 1){
          delete root;
          root = nullptr;
        }else{//else set the node to have the other value
          if(root->small == word){
            root->small = root->large;
            root->numData = 1;
          }else{
            root->numData = 1;
          }
        }
      }else{
        //merge children
        if(noChildren(root->left)){//if removing from second to last layer
          root->small = root->left->small;
          root->large = root->middle->small;
          root->numData = 2;
          delete root->left;
          delete root->middle;
          root->left = nullptr;
          root->middle = nullptr;
        }else{
          throw runtime_error("Removing from an innernode unfinished");
        }
      }
    }else if(noChildren(searchResult)){//if the key is in a leaf
      if(searchResult->numData == 2){//if the node has two values, remove the word and lower numData
        //determines which word should be the new small key
        if(searchResult->large == word){
          searchResult->numData = 1;
        }else{
          searchResult->small = searchResult->large;
          searchResult->numData = 1;
        }
      }else{
        throw runtime_error("Removing from a node with only one value unfinished");
      }
    }else{
      throw runtime_error("Unfinished edgecase");
    }
  }
}

Node* Tree::search(const string& word) {
  return search(root, word);
}

//recursively follows the path a value would be at or returns nullptr if a leaf is reached without finding it
Node* Tree::search( Node* curr, const string& word ) {
  if(curr == nullptr){
    return nullptr;
  }
  if(curr->small == word || curr->large == word){
    return curr;
  }else{
    if(word < curr->small){
      return search(curr->left,word);
    }else if(curr->numData == 2 && word > curr->large){
      return search(curr->right,word);
    }else{
      return search(curr->middle,word);
    }
  }
}
