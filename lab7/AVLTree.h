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
  int height_of(Node* tree) const;
  void inOrder(Node* tree) const;
  unsigned int balanceFactor(Node* curr) const;

  //old bst helper functons
  void remove(Node* parent, Node* tree, const string& key);
  void preOrder(Node* tree) const;
  void postOrder(Node* tree) const;
  

};
