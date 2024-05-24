#pragma once

#include "Node.h"

class AVLTree {
  Node* root;

public:
  AVLTree()
    : root(nullptr)
  {
  }
  ~AVLTree() {
    // Safe to delete nullptr, so no check needed
    // The Node struct recursively deletes its children
    delete root;
  }
  AVLTree(const AVLTree&) = delete;
  AVLTree& operator=(const AVLTree&) = delete;
  
  void insert(const string& key);
  void printBalanceFactors() const;

  //old bst functions
  bool search(const string& key) const;
  string largest() const;
  string smallest() const;
  int height(const string& key) const;
  void remove(const string& key);
  void preOrder() const;
  void postOrder() const;
  void inOrder() const;

private:
  void insert(Node* parent, Node* curr, const string& word);
  int height_of(Node* tree) const;
  void inOrder(Node* tree) const;
  int getBalanceFactor(Node* curr) const;
  void rotateLeft(Node* parent,Node* curr);
  void rotateRight(Node* parent,Node* curr);
  void fix(Node* parent, Node* curr);

  //old bst helper functons
  void remove(Node* parent, Node* tree, const string& key);
  void preOrder(Node* tree) const;
  void postOrder(Node* tree) const;
  

};
