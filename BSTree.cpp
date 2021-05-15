#include "BSTree.h"

BSTree::BSTree() {
    root = nullptr;
}

void BSTree::insert(const string& newString) {
    root = insert(root, newString);
	root->setParent(nullptr);
	updateHeightAndParent(root);		// update height & parent
}

Node* BSTree::insert(Node* node, const string& data) {
    // base case: node is nullptr
    if (node == nullptr) {
        Node* nodeInsert = new Node(data);
        return nodeInsert;
    }
    
    if (data < node->getData()) {
        node->setLeft(insert(node->getLeft(), data));
    }

    else if (data > node->getData()) {
        node->setRight(insert(node->getRight(), data));
    }

    // strings are equal
    else {
        node->incrementCount();
        return node;
    }

    return node;
}

bool BSTree::search(const string& key) const {
    return search(root, key);
}

bool BSTree::search(Node* node, const string& key) const {
    // base case: node is nullptr
    if (node == nullptr) {
        return false;
    }

    // base case: string equals the node data
    if (key == node->getData())
        return true;

    else if (key < node->getData()) {

        return search(node->getLeft(), key);
    }

    else // if (key > node->getData()) {
        return search(node->getRight(), key);
    //}
}

Node* BSTree::locate(Node* node, const string& key) const {
    // base case: node is nullptr
    if (node == nullptr) {
        return nullptr;
    }

    // base case: string equals the node data
    if (key == node->getData())
        return node;

    else if (key < node->getData()) {

        return locate(node->getLeft(), key);
    }

    else // if (key > node->getData()) {
        return locate(node->getRight(), key);
    //}
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
	Node* temp = locate(root, key);

	if (temp == nullptr) 
		return -1;

    return temp->getHeight();
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

    else //if (key > node->getData()) {
        return height(node->getRight(), key);
    //}
}

void BSTree::remove(const string& key) {
    // key is not in tree
     
    if (!search(key)) {
        //cout << "key does not exist!" << endl;
        return;
    }

	// special handling for root
	if (root->getData() == key) {
        // if count > 1
        if (root->getCount() > 1) {
            root->decrementCount();
            return;
        }
        // if leaf node
        if (root->getLeft() == nullptr && root->getRight() == nullptr) {
			delete root;
			root = nullptr;
			return;
		}
        // if only left child
        if (root->getLeft() != nullptr && root->getRight() == nullptr) {
			Node* tmp = root;
			root = root->getLeft();
			root->setParent(nullptr);
			delete tmp;
			tmp = nullptr;
			return;
		}
        // if only right child
        if (root->getLeft() == nullptr && root->getRight() != nullptr) {
			Node* tmp = root;
			root = root->getRight();
			root->setParent(nullptr);
			delete tmp;
			tmp = nullptr;
			return;
		}
        // if has both child
        if (root->getLeft() != nullptr && root->getRight() != nullptr) {
            Node* suc = findMin(root->getRight());
            string holder = suc->getData();
			int suc_count = suc->getCount();
			suc->setCount(1);	// force it to 1 to delete it, not countdown
            remove(suc, suc->getData());
            root->setData(holder);
			root->setCount(suc_count);
            return;
		}
	}

    remove(root, key);
	root->setParent(nullptr);
	updateHeightAndParent(root);		// update height & parent
}

void BSTree::remove(Node* node, const string& key) {
   
    if (node->getData() == key) {
        // if count > 1
        if (node->getCount() > 1) {
            node->decrementCount();
            return;
        }

        // if leaf node
        if (node->getLeft() == nullptr && node->getRight() == nullptr) {
			Node* nodeparent = node->getParent();
			if (nodeparent != nullptr) {
				if (nodeparent->getData() < node->getData()) {
					nodeparent->setRight(nullptr);
				} else {
					nodeparent->setLeft(nullptr);
				}
			}
			delete node;
            node = nullptr;
            //Node* temp = node;
            //delete temp;
            return;
        }

        // if only left child
        if (node->getLeft() != nullptr && node->getRight() == nullptr) {
			Node* nodeparent = node->getParent();
			if (nodeparent != nullptr) {
				if (nodeparent->getData() < node->getLeft()->getData()) {
					nodeparent->setLeft(node->getLeft());
				} else {
					nodeparent->setRight(node->getLeft());
				}
			}
			delete node;
			node=nullptr;
            return;
        }

        // if only right child
        if (node->getRight() != nullptr && node->getLeft() == nullptr) {
			Node* nodeparent = node->getParent();
			if (nodeparent != nullptr) {
				if (nodeparent->getData() < node->getRight()->getData()) {
					nodeparent->setRight(node->getRight());
				} else {
					nodeparent->setLeft(node->getRight());
				}
			}
			delete node;
			node=nullptr;
            return;
        }

        // if  two children
        else {
            Node* suc = findMin(node->getRight());
            string holder = suc->getData();
			int suc_count = suc->getCount();
			suc->setCount(1);	// force it to 1 to delete it, not countdown
            remove(suc, suc->getData());
            node->setData(holder);
			node->setCount(suc_count);
            return;
        }
    }

    // find location
    else if (key < node->getData())
        remove(node->getLeft(), key);

    else if (key > node->getData())
        remove(node->getRight(), key);

}

void BSTree::inOrder() const {
    inOrder(root);
}

void BSTree::preOrder() const {
    preOrder(root);
}

void BSTree::postOrder()const {
    postOrder(root);
}

void BSTree::inOrder(Node* currN)const {
    if (currN == nullptr)
        return;


    else {
        /*if ((currN->getLeft() == 0) && (currN->getRight() == 0)) {
            cout << currN->getData();
            cout << '(' << currN->getCount() << "), ";
        }
       
        else { */

            
            inOrder(currN->getLeft());
            cout << currN->getData();
            cout << '(' << currN->getCount() << "), ";
            inOrder(currN->getRight());
            
        //}
    }
}


void BSTree::preOrder(Node* currN)const {
    if (currN == nullptr)
        return;

    else {
        /*if ((currN->getLeft() == 0) && (currN->getRight() == 0)) {
            cout << currN->getData();
            cout << '(' << currN->getCount() << "), ";
        }

        else { */
            cout << currN->getData();
            cout << '(' << currN->getCount() << "), ";
            preOrder(currN->getLeft());
            preOrder(currN->getRight());
        //}
    }
}

void BSTree::postOrder(Node* currN)const {
    if (currN == nullptr)
        return;

    else {
        /*if ((currN->getLeft() == 0) && (currN->getRight() == 0)) {
            cout << currN->getData();
            cout << '(' << currN->getCount() << "), ";
        }
       
        else { */
            postOrder(currN->getLeft());
            postOrder(currN->getRight());
            cout << currN->getData();
            cout << '(' << currN->getCount() << "), ";
        //}
    }
}

int BSTree::updateHeightAndParent(Node* node) const {
	int leftHeight = -1;
	if (node->getLeft() !=nullptr) {
		leftHeight=updateHeightAndParent(node->getLeft());
		node->getLeft()->setParent(node);
	}

	int rightHeight = -1;
	if (node->getRight() !=nullptr) {
		rightHeight=updateHeightAndParent(node->getRight());
		node->getRight()->setParent(node);
	}

	int height = max(leftHeight, rightHeight) + 1;
	node->setHeight(height);

	return height;
}

Node* BSTree::findMin(Node* node) const {
    while (node->getLeft() != nullptr) {
        node = node->getLeft();
    }

    return node;
}

Node* BSTree::findMax(Node* node) const {
    while (node->getRight() != nullptr) {
        node = node->getRight();
    }

    return node;
}
