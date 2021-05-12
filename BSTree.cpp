#include "BSTree.h"

BSTree::BSTree() { 
    root = nullptr;
}

void BSTree::insert(const string& newString) {
    insert(root, newString);
}

void BSTree::insert(Node* node, const string& data) {    
    // base case: node is nullptr
    if (node == nullptr) {
        Node* nodeInsert = new Node(data);
        node = nodeInsert;
        return;
    }
    
    if (data < node->getData()) {
        /*
        if (node->getLeft() == nullptr) {
            Node* nodeInsert = new Node(data);
            node->setLeft(nodeInsert);
            return;
        } */
        insert(node->getLeft(), data);
    }

    else if (data > node->getData()) {
        /*
        if (node->getRight() == nullptr) {
            Node* nodeInsert = new Node(data);
            node->setRight(nodeInsert);
            return;
        } */
        insert(node->getRight(), data);
    }

    // strings are equal
    else {
        node->incrementCount();
        return;
    }
}

bool BSTree::search(const string &key) const {
    search(root, key);
}

bool BSTree::search(Node* node, const string &key) const {
    // base case: node is nullptr
    if (node == nullptr) {
        return false;
    }

    // base case: string equals the node data
    if (key == node->getData())
        return true;

    else if (key < node->getData()) {
        
        search(node->getLeft(), key);
    }

    else if (key > node->getData()) {
        search(node->getRight(), key);
    }
}

string BSTree::largest() const {
    Node* temp = root;
    
    if (temp == nullptr)
        return "";
    
    while (temp->getRight() != nullptr) {
        temp = temp->getRight();
    }

  return temp->getData();
}

string BSTree::smallest() const {
    Node* temp = root;
    
    if (temp == nullptr)
        return "";
    
    while (temp->getLeft() != nullptr) {
        temp = temp->getLeft();
    }

  return temp->getData();
}