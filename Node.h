#ifndef Node_H_
#define Node_H_

#include <string>

using namespace std;

class Node {

 public:
    Node(string);
    ~Node() {}
    string getData();
    void setLeft(Node*);
    Node* getLeft();
    void setRight(Node*);
    Node* getRight();
    int getHeight();
    void setHeight(int);
    void incrementCount();
    void decrementCount();
 private:
    string data;
    Node *left;
    Node *right;
    int height;
    int count;
};

#endif