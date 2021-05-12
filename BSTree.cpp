#include "BSTree.h"

BSTree::BSTree() { 
    root = nullptr;
}

void BSTree::insert(const string &newString) {
    insert(root, newString);
}

void BSTree::insert(Node* node, const string data) {    
    if (data < node->getData()) {
        if (node->getLeft() == nullptr) {
            Node* nodeInsert = new Node(data);
            node->setLeft(nodeInsert);
            return;
        }
        insert(node->getLeft(), data);
    }

    else if (data > node->getData()) {
        if (node->getRight() == nullptr) {
            Node* nodeInsert = new Node(data);
            node->setRight(nodeInsert);
            return;
        }
        insert(node->getRight(), data);
    }

    // strings are equal
    else {
        node->incrementCount();
        return;
    }
}

