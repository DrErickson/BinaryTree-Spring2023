

#include "TreeT.h"

template<class T>
TreeT<T>::TreeT() {
    root = nullptr;
    numNodes = 0;
}

template<class T>
TreeT<T>::~TreeT() {
    DestroyTree(root);
}

// tree = tree;
template<class T>
TreeT<T> &TreeT<T>::operator=(const TreeT &otherTree) {

    if (this != &otherTree) {
        copyOther(otherTree);
    }

    return *this;
}

template<class T>
TreeT<T>::TreeT(const TreeT &otherTree) {
    copyOther(otherTree);
}

template<class T>
void TreeT<T>::copyOther(const TreeT<T> &otherTree) {
    CopyHelper(root, otherTree.root);
}

template<class T>
void TreeT<T>::Add(T value) {
    Node* newNode = new Node;
    newNode->value = value;

    if (root == nullptr)  {
        root = newNode;
        numNodes++;
        return;
    }
    Node* curr = root;

    while (curr != nullptr) {
        if (value < curr->value) {
            if (curr->left == nullptr) {
                curr->left = newNode;
                break;
            }

            curr = curr->left;      // go left
        }
        else if (value > curr->value) {
            if (curr->right == nullptr) {
                curr->right = newNode;
                break;
            }

            curr = curr->right;     // go right
        }
        else {
            delete newNode;
            return;
        }
    }
    numNodes++;
}

template<class T>
void TreeT<T>::Remove(T value) {
    RemoveHelper(root, value);
}

template<class T>
bool TreeT<T>::Contains(T value) {

    Node* curr = root;

    while (curr != nullptr) {
        if (value < curr->value) {     // go left
            curr = curr->left;
        }
        else if (value > curr->value) {     // go right
            curr = curr->right;
        }
        else {
            return true;
        }
    }

    return false;
}

template<class T>
int TreeT<T>::Size() {
    return numNodes;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {

    // Make the entire queue empty
    while (!iterQue.empty())
        iterQue.pop();

    if (traverseOrder == IN_ORDER) {
        PlaceInOrder(root);
    }
    else if (traverseOrder == POST_ORDER) {
        PlacePostOrder(root);
    }
    else if (traverseOrder == PRE_ORDER) {
        PlacePreOrder(root);
    }
}

template<class T>
void TreeT<T>::PlaceInOrder(TreeT::Node *node) {
    if (node == nullptr) {
        return;
    }

    PlaceInOrder(node->left);
    iterQue.push(node->value);
    PlaceInOrder(node->right);
}

template<class T>
void TreeT<T>::PlacePreOrder(TreeT::Node *node) {
    if (node == nullptr) {
        return;
    }

    iterQue.push(node->value);  // self
    PlacePreOrder(node->left);  // left
    PlacePreOrder(node->right); // right
}

template<class T>
void TreeT<T>::PlacePostOrder(TreeT::Node *node) {
    if (node == nullptr) {
        return;
    }

    PlacePostOrder(node->left);  // left
    PlacePostOrder(node->right); // right
    iterQue.push(node->value);  // self
}

template<class T>
T TreeT<T>::GetNextItem() {

    if (iterQue.empty()) {
        throw EmptyTreeError();
    }

    T nextItem = iterQue.front();
    iterQue.pop();

    return nextItem;
}

template<class T>
void TreeT<T>::DestroyTree(TreeT::Node *node) {
    if (node == nullptr)
        return;

    DestroyTree(node->left);
    DestroyTree(node->right);
    delete node;
}

template<class T>
void TreeT<T>::RemoveHelper(TreeT::Node *&subtree, T value) {
    if (value < subtree->value) {
        RemoveHelper(subtree->left, value);
    }
    else if (value > subtree->value) {
        RemoveHelper(subtree->right, value);
    }
    else {
        DeleteNode(subtree);
    }
}

template<class T>
void TreeT<T>::DeleteNode(TreeT::Node *&subtree) {
    T data;
    Node* tempPtr;

    tempPtr = subtree;
    if (subtree->left == nullptr && subtree->right == nullptr) {
        delete subtree;
    }
    else if (subtree->left == NULL)
    {
        subtree = subtree->right;
        delete tempPtr;
    }
    else if (subtree->right == NULL)
    {
        subtree = subtree->left;
        delete tempPtr;
    }
    else
    {
        GetPredecessor(subtree->left, data);
        subtree->value = data;
        RemoveHelper(subtree->left, data);
        // Delete predecessor node.
    }

}

template<class T>
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T &value) {
    while (curr->right != NULL)
        curr = curr->right;
    value = curr->value;
}

template<class T>
void TreeT<T>::CopyHelper(TreeT::Node *&thisTree, TreeT::Node *otherTree) {
    if (otherTree == nullptr)
        return;

    thisTree = new Node;
    thisTree->value = otherTree->value;
    CopyHelper(thisTree->left, otherTree->left);
    CopyHelper(thisTree->right, otherTree->right);
}





