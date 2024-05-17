#include "Tree.h"
#include <iostream>
#include <string>

using namespace std;

/* Uncomment these out if you want to use them... the 'static' means
   that they are only available here in Tree.cpp
*/
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
  // TURD: You have to write this eventually, but you can
  // wait until remove works correctly and then just keep
  // removing the smallest key in the root until the tree
  // is empty
}


bool Tree::noChildren( Node* node ) const {
  return (node->left == nullptr);
}

void Tree::insert( const string& word ) {
  if ( root == nullptr ) {
    root = new Node( word );
  } else {
    //find the correct leaf to add to
    Node* curr = root;
    while(! noChildren(curr)){
      if(word < curr->small){
        cout << 1;
        curr = curr->left;
      }else if(curr->numData = 1){//if there is only one key in curr
        cout << 2;
        curr = curr->middle;
      }else{
        cout << 3;
        curr = curr->right;
      }
    }
    cout << "made it" << endl;
    insert( curr, word );
  }
}

// TURD: Concentrate on the easy ones needed for test1 first
void Tree::insert( Node* curr, const string& word ) {
  
  //if the node being inserted to has room
  if(curr->numData != 2){
    cout << "adding " << word << " to " << curr->small << endl;
    addData(curr,word);
  }
  //need to explode
  else{
    cout << "explosion needed" << endl;
    string low = minStr(curr->small,word,curr->large);
    string mid = midStr(curr->small,word,curr->large);
    string high = maxStr(curr->small,word,curr->large);
    
    
    //if the tree is only one node
    if(curr->parent == nullptr && noChildren(curr)){
      cout << "tree is only one node" << endl;
      root = new Node(mid);
      root->left = new Node(low);
      root->left->parent = root;
      root->middle = new Node(high);
      root->middle->parent = root;
      delete curr;
    }else{
      cout << "here " << endl;
      cout << low << mid << high << endl; 
      if(curr == curr->parent->left){
        Node* newLowNode = new Node(low);
        newLowNode->parent = curr->parent;
        Node* newMidNode = new Node(high);
        newMidNode->parent = curr->parent;
        curr->parent->left = newLowNode;
        curr->parent->right = curr->parent->middle;
        curr->parent->middle = newMidNode;
        if(curr->parent->numData == 1){
          insert(curr->parent,mid);
        }else{
          throw runtime_error("You need to write this to get simple insert working");
        }
        


      }else if(curr == curr->parent->middle){
        Node* newMiddleNode = new Node(low);
        newMiddleNode->parent = curr->parent;
        Node* newRightNode = new Node(high);
        newRightNode->parent = curr->parent;
        curr->parent->middle = newMiddleNode;
        curr->parent->right = newRightNode;
        if(curr->parent->numData == 1){
          insert(curr->parent,mid);
        }else{
          throw runtime_error("You need to write this to get simple insert working");
        }
      }else{
        throw runtime_error("You need to write this to get simple insert working");
      }
    }
    

    //throw runtime_error("You need to write this to get simple insert working");
  }
  
}

// This is handy since it puts a key into the right spot (small or
// large string)
void Tree::addData( Node* addHere, const string& word ) {
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
  cout  << "| " << curr->small;
  if(curr->numData == 2){
    cout << curr->large << " |";
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
  cout << curr->small << " ";
  inOrder(curr->middle);
  if(curr->numData == 2){
    cout << curr->large << " ";
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
  cout << curr->small << " ";
  if(curr->numData == 2){
    cout << curr->large << " ";
  }
}

void Tree::remove(const string& word) {
  // Nothing to do in an empty tree, just return
  if ( !root )
    return;
  
  // Find the node that holds this key.  If it does not exist, then
  // we have nothing to do.  Just return (no error)

  // Removing the a key in the root is a special case
  // If it is the last key, better set root back to nullptr!

  // if the node to remove is not a leaf, move the value to a leaf
  // TURD: (This is the easiest strategy to do a remove -- though the
  // zybook isn't really clear about it)

  // if we made an empty node (numData == 0), we have to fix it
}

void Tree::fix(Node* emptyNode) {
  // This is where the real heart of the program is at...
  // We have to deal with fusion, rotation, redistribution
  // here

  // Some cases:
  // emptyNode is nullptr, do nothing
  // emptyNode is the root, one of our children becomes the root

  // check for redistribution... Can I steal from a sibling with two keys?

  // If not, I have to do a merge
}

bool Tree::hasTwoChildSibling(Node* sib) const {
  throw runtime_error("this one will be handy");
}

// TURD: This is NOT const because we want the node* so we can
// do a remove
Node* Tree::search(const string& word) {
  return search(root, word);
}

// TURD: You should know how to do this one for the final
Node* Tree::search( Node* curr, const string& word ) {
  throw runtime_error("you will need to write the helper");
}
