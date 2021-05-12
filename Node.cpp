#include "Node.h"

using namespace std;

Node::Node(string k) {
   data = k;
   left = nullptr;
   right = nullptr;
   height = 1;
   count = 1;
}

string Node::getData() {
   return data;
}

void Node::setLeft(Node* left){
   this->left = left;
}

Node* Node::getLeft(){
   return left;
}

void Node::setRight(Node* right){
   this->right= right;
}

Node* Node::getRight(){
   return right;
}

int Node::getHeight() {
   return height;
}

void Node::setHeight(int h) {
   height = h;
}

int Node::getCount() {
   return count;
}

void Node::incrementCount() {
   count++;
}

void Node::decrementCount() {
   count--;
}