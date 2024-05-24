#include "AVLTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void AVLTree::insert(const string& word){
  if(root == nullptr){
    root = new Node(word);
  }else{
    insert(nullptr,root,word);
  }
}
void AVLTree::insert(Node* parent, Node* curr,const string& word){
  //if the word is already in the tree, increments the node's count
  if(curr->key == word){
    curr->count++;
  }
  //adds new node when a space is found or recursively calls insert on the node in the next space
  else if(word < curr->key){//if the word is less than curr's word
    if(curr->left == nullptr){
      curr->left = new Node(word);
    }else{
      insert(curr,curr->left,word);
    }
  }
  else{//if the word is greater than curr's word
    if(curr->right == nullptr){
      curr->right = new Node(word);
    }else{
      insert(curr,curr->right,word);
    }
  }
  //called after every recursive call back up to the root
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
    }
    //normal case
    else{
      rotateRight(parent,curr);
    }
  }
  //if unbalanced to the right
  else if(balanceFactor < -1){
    if(getBalanceFactor(curr->right) > 0){
      rotateRight(curr, curr->right);
      rotateLeft(parent, curr);
    }
    //normal case
    else{
      rotateLeft(parent, curr);
    }
  }
}

void AVLTree::rotateLeft(Node* parent,Node* curr){
  Node* newRight = curr->right->left;

  //if rotating the root
  if(parent == nullptr){
    root = curr->right;
    root->left = curr;
    curr->right = newRight;
  }
  //if rotating parent's left child
  else if(curr->key < parent->key){
    parent->left = curr->right;
    parent->left->left = curr;
    curr->right = newRight;
  }
  //if rotating parent's right child
  else{
    parent->right = curr->right;
    parent->right->left = curr;
    curr->right = newRight;
  }
}

void AVLTree::rotateRight(Node* parent,Node* curr){
  Node* newLeft = curr->left->right;

  //rotating root
  if(parent == nullptr){
    root = curr->left;
    root->right = curr;
    curr->left = newLeft;
  }
  //rotating left child
  else if(curr->key < parent->key){
    parent->left = curr->left;
    parent->left->right = curr;
    curr->left = newLeft;
  }
  //rotating right child
  else{
    parent->right = curr->left;
    parent->right->right = curr;
    curr->left = newLeft;
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
