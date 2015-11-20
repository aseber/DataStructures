/*
 *
 * Name: Austin Seber
 *
 * UFID: 01516234
 *
 * Gator ID: aseber
 *
 * Discussion Section: 13A8
 *
 */

#ifndef SEBER_MIN_PRIORITY_TREE_QUEUE_H
#define SEBER_MIN_PRIORITY_TREE_QUEUE_H

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>

template<typename T>
struct Node {
    T value;
    Node* leftChild;
    Node* rightChild;

    Node() : value(T()), leftChild(NULL), rightChild(NULL) {}
};

template<typename T>
class min_priority_tree_queue {
    Node<T>* root;
    int internalSize;

    int distToLeaf(const Node<T>* currentNode) {
        int leftDistance = 1;
        int rightDistance = 1;

        if (currentNode == NULL) {
            std::cout << "This should not happen" << std::endl;
            return 0;
        }

        if (currentNode->leftChild != NULL) {
            leftDistance += distToLeaf(currentNode->leftChild);
        }

        if (currentNode->rightChild != NULL) {
            rightDistance += distToLeaf(currentNode->rightChild);
        }

        return std::min(leftDistance, rightDistance);
    }

 public:
    min_priority_tree_queue() : root(NULL), internalSize(0) {}

    ~min_priority_tree_queue() {
        empty();
    }

    const int& size() const {
        return internalSize;
    }

    bool isEmpty() const {
        if (!size()) {
            return true;
        }

        return false;
    }

    void empty() {
        while(!isEmpty()) {
            pop();
        }
    }

    void push(const T& elementToAdd) {
        Node<T>* newNode = new Node<T>();
        newNode->value = elementToAdd;
        root = meld(root, newNode);
        internalSize++;
    }

    const T& top() const {
        if (isEmpty()) {
            std::ostringstream stream;
            stream << "min_priority_tree_queue top failed. Queue is empty";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        return root->value;
    }

    T pop() {
        if (isEmpty()) {
            std::ostringstream stream;
            stream << "min_priority_tree_queue pop failed. Queue is empty";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        T value = T(root->value);
        Node<T>* temp = meld(root->leftChild, root->rightChild);
        delete root;
        root = temp;
        internalSize--;
        return value;
    }

    Node<T>* meld(Node<T>* leftBranch, Node<T>* rightBranch) {
        if (leftBranch == NULL) {
            return rightBranch;
        } else if (rightBranch == NULL) {
            return leftBranch;
        }

        if (leftBranch->value > rightBranch->value) {
            Node<T>* temp = leftBranch;
            leftBranch = rightBranch;
            rightBranch = temp;
        }

        leftBranch->rightChild = meld(leftBranch->rightChild, rightBranch);

        if (leftBranch->leftChild == NULL) {
            leftBranch->leftChild = leftBranch->rightChild;
            leftBranch->rightChild = NULL;
        } else if (distToLeaf(leftBranch->leftChild) < distToLeaf(leftBranch->rightChild)) {
            Node<T>* temp = leftBranch->leftChild;
            leftBranch->leftChild = leftBranch->rightChild;
            leftBranch->rightChild = temp;
        }

        return leftBranch;
    }
};

#endif
