#pragma once
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
    void setParent(Node*);
    Node* getParent();
    int getHeight();
    void setHeight(int);
	void updateHeight(Node*);
    int getCount();
    void setCount(int);
    void incrementCount();
    void decrementCount();
    void setData(string);
private:
    string data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    int count;
};

#endif
