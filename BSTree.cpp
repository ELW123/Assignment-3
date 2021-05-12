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

int BSTree::height(const string& key) const {
    if (!search(key))
        return -1;

    return height(root, key);
}

int BSTree::height(Node* node, const string& key) const {
    // base case: node is the desired key; function finds height and exits
    if (node->getData() == key) {
        int leftHeight = 0;
        int rightHeight = 0;
        Node* temp = node;

        while (temp->getLeft() != nullptr) {
            leftHeight++;
            temp = temp->getLeft();
        }

        while (temp->getRight() != nullptr) {
            rightHeight++;
            temp = temp->getRight();
        }

        if (leftHeight <= rightHeight)
            return rightHeight;
        else 
            return leftHeight;
    }
    
    else if (key < node->getData()) {
        return height(node->getLeft(), key);
    }

    else if (key > node->getData()) {
        return height(node->getRight(), key);
    }
}

void BSTree::remove(const string& key) {
    // key is not in tree
    if (!search(key)) {
        cout << "key does not exist!" << endl;
        return;
    }

    remove(root, key);
}

// remove function is still incomplete
void BSTree::remove(Node* node, const string& key) {
    if (node->getData() == key) {
        // if count > 1
        if (node->getCount() > 1) {
            node->decrementCount();
            return;
        }

        // if leaf node
        if (node->getLeft() == nullptr && node->getRight() == nullptr) {
            node = nullptr;
            Node* temp = node;
            delete temp;
            return;
        }

        // if only left child
        if (node->getLeft() != nullptr && node->getRight() == nullptr) {
            node = node->getLeft();
            return;
        }

        // if only right child
        if (node->getLeft() == nullptr && node->getRight() != nullptr) {
            node = node->getRight();
            return;
        }

        // if two children
    }
    
    // find location
    else if (key < node->getData())
        remove(node->getLeft(), key);

    else if (key > node->getData())
        remove(node->getRight(), key);
}