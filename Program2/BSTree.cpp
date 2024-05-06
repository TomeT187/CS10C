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
    if(curr->key == key){
      return true;
    }else if(key < curr->key){
      curr = curr->left;
    }else{
      curr = curr->right;
    }
  }
  return false;
}

string BSTree::largest() const {
  // Edge case: Tree is empty (return "")
  // Largest can be done in a loop (or recursively).  A loop is best here
  string largestString = "";
  Node* curr = root;
  while(curr != nullptr){
    largestString = curr->key;
    curr = curr->right;
  }
  return largestString;
}

string BSTree::smallest() const {
  // Smallest can be done in a loop (or recursively).  A loop is best here
  // Edge case: Tree is empty
  string smallestString = "";
  Node* curr = root;
  while(curr != nullptr){
    smallestString = curr->key;
    curr = curr->left;
    
  }
  return smallestString;
}

int BSTree::height(const string& key) const {
  // First find the node with this key, then run "height_of" to get
  // the height that zybooks wants
  Node* curr = root;
  while(curr != nullptr){
    if(curr->key == key){
      return height_of(curr);
    }else if(key < curr->key){
      curr = curr->left;
    }else{
      curr = curr->right;
    }
  }
  return -1;
  throw runtime_error("not done height");
}

void BSTree::remove(const string& key) {
  throw runtime_error("not done remove");
}

void BSTree::preOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  preOrder(root);
  cout << endl;
}

void BSTree::postOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  postOrder(root);
  cout << endl;
}

void BSTree::inOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  inOrder(root);
  cout << endl;
}

void BSTree::remove(Node* parent, Node* tree, const string& key) {
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
  throw runtime_error("not done remove");
}

int BSTree::height_of(Node* tree) const {
  // The height (length of longest path to the bottom) of an empty tree is -1
  // Otherwise, you pick the larger of the left height and the right height
  // and add one to that
  if(tree == nullptr){
    return -1;
  }
  int leftHeight = height_of(tree->left);
  int rightHeight = height_of(tree->right);
  if(leftHeight > rightHeight){
    return (1 + leftHeight);
  }else{
    return (1 + rightHeight);
  }
}

void BSTree::preOrder(Node* tree) const {
  // print key, do left, do right
  cout << tree->key << "(" << tree->count << "), ";
  
  if(tree->left != nullptr){
    preOrder(tree->left);
  }
  if(tree->right != nullptr){
    preOrder(tree->right);
  }
  
}

void BSTree::postOrder(Node* tree) const {
  // do left, do right, print key
  if(tree->left != nullptr){
    preOrder(tree->left);
  }
  if(tree->right != nullptr){
    preOrder(tree->right);
  }
  cout << tree->key << "(" << tree->count << "), ";
}

void BSTree::inOrder(Node* tree) const {
  // do left, print key, do right
  if(tree->left != nullptr){
    preOrder(tree->left);
  }
  cout << tree->key << "(" << tree->count << "), ";
  if(tree->right != nullptr){
    preOrder(tree->right);
  }
}

// This is a pre-order traversal that shows the full state of the tree
// (but it is a code turd)
void BSTree::debug(Node* tree, int indent) const {
  if (tree == nullptr) return;
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << tree << ' ' << *tree << endl;
  debug(tree->left,indent+1);
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << "-" << endl;
  debug(tree->right,indent+1);
}
