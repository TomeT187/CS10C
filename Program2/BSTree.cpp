#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void BSTree::insert(const string& key) {
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
bool BSTree::search(const string& key) const {
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

string BSTree::largest() const {
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

string BSTree::smallest() const {
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

int BSTree::height(const string& key) const {
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
void BSTree::remove(const string& key) {
  remove(nullptr,root,key);
  
}

//calls private helper function 
void BSTree::preOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  preOrder(root);
  cout << endl;
}

//calls private helper function 
void BSTree::postOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  postOrder(root);
  cout << endl;
}

//calls private helper function 
void BSTree::inOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  inOrder(root);
  cout << endl;
}

//ran out of time :(
//ran out of time :(
void BSTree::remove(Node* parent, Node* tree, const string& key) {
  //if a leaf is reached without finding the value to remove the value is not in the tree
  if(tree == nullptr){
    cout << "heres" << endl;
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
      cout << "deleting " << tree->key << endl;
      delete tree;
    }
    //else the key is in a non leaf node
    else{
      cout << "non leaf" << endl;
      //find largest left or smallest right
      Node* replacement;
      string newKey;
      int newCount;
      if(tree->left != nullptr){
        replacement = tree->left;
        newKey = replacement->key;
        newCount = 
        while(replacement->right != nullptr){
          replacement = replacement->right;
          newKey = replacement->key;
        }
        remove(tree,tree->left,newKey);
      }else{
        replacement = tree->right;
        newKey = replacement->key;
        while(replacement->left != nullptr){
          replacement = replacement->left;
          newKey = replacement->key;
        }
        remove(tree,tree->right,newKey);
      }
      //replace the node to be deleted with the replacement's values
      tree->key = newKey;
      tree->count = 1;
    }
  }else if(key < tree->key){
    //key is on the left of the current node
    remove(tree,tree->left,key);
  }else{
    //key is on the right of the current node
    remove(tree,tree->right,key);
  }
  // Hint: A good approach is to find the parent and the curr node that holds that key
  // Edge case: The key is not found (do nothing)
  // Edge case.  The key count is greater than 1.  Just decrement the count
  // Edge case: leaf (no children).  Just remove from parent
  //  ==> case 1: parent is nullptr (we are removing the last node from root)
  //  ==> case 2: curr is the left child, remove it from parent
  //  ==> case 3: curr is the right child, remove it from parent
  // Typical case.  Find the target
  // It is either the largest key in the left tree (if one exists)
  // or the smallest key in the right tree (since not a leaf one will exist)
  // Copy the target information into the node we found, set the target count to
  // one, and recursively remove it from left or right subtree (current node is the parent)
}

int BSTree::height_of(Node* tree) const {
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

void BSTree::preOrder(Node* tree) const {
  // print key, do left, do right
  //base case for recursive function
  cout << tree->key << "(" << tree->count << "), ";//should have used << operator overloded, oh well
  
  //recursively calls preOrder on the left and right nodes until a leaf is reached
  if(tree->left != nullptr){
    preOrder(tree->left);
  }
  if(tree->right != nullptr){
    preOrder(tree->right);
  }
  
}

void BSTree::postOrder(Node* tree) const {
  // do left, do right, print key
  //recursively calls preOrder on the left and right nodes until a leaf is reached
  if(tree->left != nullptr){
    preOrder(tree->left);
  }
  if(tree->right != nullptr){
    preOrder(tree->right);
  }
  //base case for recursive function
  cout << tree->key << "(" << tree->count << "), ";
}

void BSTree::inOrder(Node* tree) const {
  // do left, print key, do right
  //recursively calls preOrder on the left and right nodes until a leaf is reached
  if(tree->left != nullptr){
    preOrder(tree->left);
  }

  //base case for recursive function
  cout << tree->key << "(" << tree->count << "), ";

  if(tree->right != nullptr){
    preOrder(tree->right);
  }
}
