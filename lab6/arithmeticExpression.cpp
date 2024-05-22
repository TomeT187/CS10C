#include <iostream>
#include <sstream>
#include <stack>

#include "arithmeticExpression.h"

using namespace std;

arithmeticExpression::arithmeticExpression(const string& expression)
  : infixExpression(expression),
    root(nullptr)
{
}

//calls TreeNode Destructor
arithmeticExpression::~arithmeticExpression(){
    delete root;
}

//recursively destroys all subtrees
TreeNode::~TreeNode(){
      if(left != nullptr){
         delete left;
      }
      if(right != nullptr){
         delete right;
      }
      delete this;
    }


void arithmeticExpression::buildTree() {
    const string postfix = infix_to_postfix();
    stack<TreeNode*> nodeStack;
    TreeNode* oppNode;
    //if current char is an opperand add it to the stack as a new node
    for(unsigned int i = 0; i < postfix.size(); i++){
        if(not is_operator(postfix.at(i))){
            oppNode = new TreeNode(postfix.at(i));
            nodeStack.push(oppNode);
        }else{//if the current char is an opperator
            //take last two nodes from the stack and set them as the children of an operator node
            //place operator node in the tree
            oppNode = new TreeNode(postfix.at(i));
            oppNode->right = nodeStack.top();
            nodeStack.pop();
            oppNode->left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(oppNode);
        }
    }
    root = nodeStack.top();
}

void arithmeticExpression::infix() {
  infix(root);
}

void arithmeticExpression::infix(TreeNode * curr){
    if (curr == nullptr) return;
    if(is_operator(curr->key)){
        cout << "(";
        infix(curr->left);
        cout << curr->key;
        infix(curr->right);
        cout << ")";

    }else{
        infix(curr->left);
        cout << curr->key;
        infix(curr->right);
    }
    
    
}

void arithmeticExpression::prefix() {
  prefix(root);
}

void arithmeticExpression::prefix(TreeNode *curr){
    if (curr == nullptr) return;
    cout << curr->key;
    prefix(curr->left);
    prefix(curr->right);

}

void arithmeticExpression::postfix() {
  postfix(root);
}

void arithmeticExpression::postfix(TreeNode *curr){
    if (curr == nullptr) return;
    
    postfix(curr->left);
    postfix(curr->right);
    cout << curr->key;
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if (op == '('){
        priority =  3;
    }
    else if (op == '*' || op == '/') {
        priority = 2;
    }
    else if (op == '+' || op == '-') {
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix() {
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i) {
        c = infixExpression.at(i);
        if (c == ' ') {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
            if ( c == '(') {
                s.push(c);
            }
            else if (c == ')') {
                while(s.top() != '(') {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())) {
                    if (s.top() == '(') {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()) {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

bool arithmeticExpression::is_operator(char val){
    return (val == '+' || val == '-' || val == '*' || val == '/');
}