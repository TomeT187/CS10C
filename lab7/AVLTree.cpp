#include "AVLTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;
/*
void AVLTree::insert(const string& key) {
  // Edge case:  The tree is empty
  if(root == nullptr){
    root  = new Node(key);
    return;
  }
  // Edge case: If we find the key in the tree, just increment its count
  // Typical case, we find a hole where this key belongs
  // ==> if we would go left and there is no child there, insert new node to left
  // ==> if we would go right and there is no child there, insert new node to right
  Node* curr = root;
  while(curr != nullptr){
    //every iteration down the tree checks if the key:
          //1) is already there
          //2) should be to the left
          //3) should be to the right
              //if it should be to the left or right, it checks if there is a hole for to be placed in
    if(curr->key == key){
      curr->count++;
      return;
    }else if(key < curr->key){
      if(curr->left == nullptr){
        curr->left = new Node(key);
        return;
      }
      curr = curr->left;
    }else{
      if(curr->right == nullptr){
        curr->right = new Node(key);
        return;
      }
      curr = curr->right;
    }
  }
}
*/
void AVLTree::insert(const string& word){
  if(root == nullptr){
    root = new Node(word);
  }else{
    insert(nullptr,root,word);
  }
}
void AVLTree::insert(Node* parent, Node* curr,const string& word){
  if(word < curr->key){
    if(curr->left == nullptr){
      curr->left = new Node(word);
    }else{
      insert(curr,curr->left,word);
    }
  }else{
    if(curr->right == nullptr){
      curr->right = new Node(word);
    }else{
      insert(curr,curr->right,word);
    }
  }
  fix(parent,curr);
  
}
void AVLTree::fix(Node* parent,Node* curr){
//balance checking
  int balanceFactor = getBalanceFactor(curr);
  //if unbalanced to the left
  if(balanceFactor > 1){
    
    //zig zag case
    if(getBalanceFactor(curr->left) < 0){
      rotateLeft(curr,curr->left);
      rotateRight(parent,curr);
    }else{
      rotateRight(parent,curr);
    }
  }
  //if unbalanced to the right
  else if(balanceFactor < -1){
    if(getBalanceFactor(curr->right) > 0){
      rotateRight(curr, curr->right);
      rotateLeft(parent, curr);
    }else{
      rotateLeft(parent, curr);
    }
  }
}

void AVLTree::rotateLeft(Node* parent,Node* curr){
  Node* T1 = curr->left;
  Node* T2 = curr->right->left;
  Node* T3 = curr->right->right;
  //if rotating the root
  if(parent == nullptr){
    root = curr->right;
    root->left = curr;
    // curr->left = T1;//repetitive?
    curr->right = T2;
    root->right = T3;
  }
  //if rotating parent's left child
  else if(curr->key < parent->key){
    parent->left = curr->right;
    parent->left->left = curr;
    // curr->left = T1;//repetitive?
    curr->right = T2;
    parent->left->right = T3;
  }
  //if rotating parent's right child
  else{
    parent->right = curr->right;
    parent->right->left = curr;
    // curr->left = T1;//repetitive?
    curr->right = T2;
    parent->right->right = T3;
  }
}

void AVLTree::rotateRight(Node* parent,Node* curr){
  //rotating root
  Node* T1 = curr->left->left;
  Node* T2 = curr->left->right;
  Node* T3 = curr->right;

  if(parent == nullptr){
    root = curr->left;
    root->left = T1;
    root->right = curr;
    curr->left = T2;
    // curr->right = T3;
  }
  //rotating left child
  else if(curr->key < parent->key){
    parent->left = curr->left;
    parent->left->left = T1;//PROBLEM CHANGING PARENTS LEFT AFTER CHANGING PARENT LEFT ABOVE
    parent->left->right = curr;
    curr->left = T2;
    // curr->right = T3;
  }
  //rotating right child
  else{
    parent->right = curr->left;
    parent->right->left = T1;
    parent->right->right = curr;
    curr->left = T2;
    // curr->right = T3;
  }
}



int AVLTree::height_of(Node* tree) const {
  // The height (length of longest path to the bottom) of an empty tree is -1
  // Otherwise, you pick the larger of the left height and the right height
  // and add one to that
  if(tree == nullptr){//base case for recursive function
    return -1;
  }
  int leftHeight = height_of(tree->left);//returns height in the left direction
  int rightHeight = height_of(tree->right);//returns height in the right direction
  if(leftHeight > rightHeight){//returns 1 + the largest of the two heights
    return (1 + leftHeight);
  }else{
    return (1 + rightHeight);
  }
}

void AVLTree::printBalanceFactors() const{
  inOrder(root);
  cout << endl;
  preOrder(root);//REMOVE LATER
}

void AVLTree::inOrder(Node* tree) const {
  // do left, print key, do right
  if (tree == nullptr) return;
  inOrder(tree->left);
  cout << tree->key << "(" << getBalanceFactor(tree) << "), ";
  inOrder(tree->right);
}

int AVLTree::getBalanceFactor(Node* curr) const{
  return (height_of(curr->left) - height_of(curr->right));
}


//old BST functions
//old BST functions
//old BST functions
//old BST functions











bool AVLTree::search(const string& key) const {
  // Search can be done in a loop (or recursively).  A loop is best here
  Node* curr = root;
  while(curr != nullptr){
    if(curr->key == key){//if the key is found; returns true
      return true;
    }else if(key < curr->key){//if the key is smaller than curr; move left
      curr = curr->left;
    }else{        //if the key is bigger than curr; move right
      curr = curr->right;
    }
  }
  return false;//if the while loop is exited, the key does not exist
}


string AVLTree::largest() const {
  // Edge case: Tree is empty (return "")
  // Largest can be done in a loop (or recursively).  A loop is best here

  string largestString = "";//if the root is nullptr, the while loop never starts and this value is returned
  Node* curr = root;
  while(curr != nullptr){
    largestString = curr->key;
    curr = curr->right;//iterates down the right(largest) side of the tree
  }
  return largestString;
}

string AVLTree::smallest() const {
  // Smallest can be done in a loop (or recursively).  A loop is best here
  // Edge case: Tree is empty

  string smallestString = "";//if the root is nullptr, the while loop never starts and this value is returned
  Node* curr = root;
  while(curr != nullptr){
    smallestString = curr->key;
    curr = curr->left;//iterates down the left(smallest) side of the tree
    
  }
  return smallestString;
}

int AVLTree::height(const string& key) const {
  // First find the node with this key, then run "height_of" to get
  // the height that zybooks wants
  Node* curr = root;
  //iterates left and right down the tree until the correct node is found
  while(curr != nullptr){
    if(curr->key == key){
      return height_of(curr);//calls helper function once the node is found
    }else if(key < curr->key){
      curr = curr->left;
    }else{
      curr = curr->right;
    }
  }
  return -1;//if the while loop exits, the node does not exist in the tree
}

//ran out of time :(
void AVLTree::remove(const string& key) {
  remove(nullptr,root,key);
  
}

//calls private helper function 
void AVLTree::preOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  preOrder(root);
  cout << endl;
}

//calls private helper function 
void AVLTree::postOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  postOrder(root);
  cout << endl;
}

//calls private helper function 
void AVLTree::inOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  inOrder(root);
  cout << endl;
}

void AVLTree::remove(Node* parent, Node* tree, const string& key) {
  //if a leaf is reached without finding the value to remove the value is not in the tree
  if(tree == nullptr){
    return;
  }
  //when the key is found
  if(tree->key == key){
    //if the key count is more than one, decrement the count
    if(tree->count > 1){
      tree->count--;
    }
    //if key is in a leaf and key count is one
    else if(tree->left == nullptr && tree->right == nullptr){
      //if the key is in the root
      if(parent == nullptr){
        root = nullptr;
      }
      //key is to the left
      else if(parent->left == tree){
        parent->left = nullptr;
      }
      //key is to the right
      else{
        parent->right = nullptr;
      }
      delete tree;
    }
    //else the key is in a non leaf node
    else{
      //find largest left or smallest right
      Node* replacement;
      string newKey;
      int newCount;
      //if there is a left tree
      //finds the largest value in it
      if(tree->left != nullptr){
        replacement = tree->left;
        newKey = replacement->key;
        newCount = replacement->count;
        while(replacement->right != nullptr){
          replacement = replacement->right;
          newKey = replacement->key;
          newCount = replacement->count;
        }
        replacement->count = 1;
        remove(tree,tree->left,newKey);
      }
      //else finds the smallest value in the right tree
      else{
        replacement = tree->right;
        newKey = replacement->key;
        newCount = replacement->count;
        while(replacement->left != nullptr){
          replacement = replacement->left;
          newKey = replacement->key;
          newCount = replacement->count;
        }
        replacement->count = 1;
        remove(tree,tree->right,newKey);
      }
      //replace the node to be deleted with the replacement's values
      tree->key = newKey;
      tree->count = newCount;
    }
  }else if(key < tree->key){
    //key is on the left of the current node
    remove(tree,tree->left,key);
  }else{
    //key is on the right of the current node
    remove(tree,tree->right,key);
  }
}



void AVLTree::preOrder(Node* tree) const {
  // print key, do left, do right
  if (tree == nullptr) return;
  cout << tree->key << "(" << tree->count << "), ";//should have used << operator overloded, oh well
  preOrder(tree->left);
  preOrder(tree->right);
  
}

void AVLTree::postOrder(Node* tree) const {
  // do left, do right, print key
  if (tree == nullptr) return;
  postOrder(tree->left);
  postOrder(tree->right);
  cout << tree->key << "(" << tree->count << "), ";
}


