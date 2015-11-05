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

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>

template<typename T>
class min_priority_heap_queue {
    int maxCapacity;
    int currentCapacity;
    T** arrayOfElements;

    int findParent(const int& currentElement) {
        return ((currentElement) / 2);
    }

    int findLeftChild(const int& currentElement) {
        return (currentElement + 1)*2 - 1;
    }

    int findRightChild(const int& currentElement) {
        return (currentElement + 1)*2;
    }

    int compareElements(const int& element1, const int& element2) {
        if (*arrayOfElements[element1] > *arrayOfElements[element2]) {
            return 1;
        } else if (*arrayOfElements[element1] < *arrayOfElements[element2]) {
            return -1;
        }

        return 0;
    }

    void siftUpElement(const int& index) {
        int currentElement = index;
        int parentElement = findParent(currentElement);

        while(currentElement != parentElement && compareElements(currentElement, parentElement) == -1) {
            T* temp = arrayOfElements[currentElement];
            arrayOfElements[currentElement] = arrayOfElements[parentElement];
            arrayOfElements[parentElement] = temp;
            currentElement = parentElement;
            parentElement = findParent(currentElement);
        }
    }

    void siftDownElement(const int& index) {
        int currentElement = index;
        int leftChild = findLeftChild(currentElement);
        int rightChild = findRightChild(currentElement);
        bool leftChildExists = leftChild < currentCapacity;
        bool rightChildExists = rightChild < currentCapacity;

        while((leftChildExists && rightChildExists) && (compareElements(currentElement, leftChild) == 1 || compareElements(currentElement, rightChild) == 1)) {
            // std::cout << "element: " << currentElement << " (" << *arrayOfElements[currentElement] << ")" << std::endl;
            // std::cout << "left: " << leftChild << " (" << *arrayOfElements[leftChild] << ")" << std::endl;
            // std::cout << "right: " << rightChild << " (" << *arrayOfElements[rightChild] << ")" << std::endl;
            // std::cout << "leftExist: " << leftChildExists << std::endl;
            // std::cout << "rightExist: " << rightChildExists << std::endl;

            if (*arrayOfElements[leftChild] < *arrayOfElements[rightChild]) {
                // std::cout << "Shift down left" << std::endl;
                // Push up left, sift down
                T* temp = arrayOfElements[currentElement];
                arrayOfElements[currentElement] = arrayOfElements[leftChild];
                arrayOfElements[leftChild] = temp;
                currentElement = leftChild;
                leftChild = findLeftChild(currentElement);
                rightChild = findRightChild(currentElement);
                leftChildExists = leftChild < currentCapacity;
                rightChildExists = rightChild < currentCapacity;
            } else {
                // std::cout << "Shift down right" << std::endl;
                // Push up right, sift down
                T* temp = arrayOfElements[currentElement];
                arrayOfElements[currentElement] = arrayOfElements[rightChild];
                arrayOfElements[rightChild] = temp;
                currentElement = rightChild;
                leftChild = findLeftChild(currentElement);
                rightChild = findRightChild(currentElement);
                leftChildExists = leftChild < currentCapacity;
                rightChildExists = rightChild < currentCapacity;
            }
        }
    }

 public:
    min_priority_heap_queue(const int& initialSize) : maxCapacity(initialSize), currentCapacity(0), arrayOfElements(new T*[initialSize]) {}

    ~min_priority_heap_queue() {
        delete[] arrayOfElements;
    }

    int size() {
        return currentCapacity;
    }

    bool isEmpty() {
        if (!currentCapacity) {
            return true;
        }

        return false;
    }

    void empty() {
        delete[] arrayOfElements;
        arrayOfElements = new T[maxCapacity];
    }

    void push(const T& elementToAdd) {
        if (currentCapacity == maxCapacity) {
            std::ostringstream stream;
            stream << "min_priority_heap_queue push failed. Queue is full capacity";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        T* newElement = new T(elementToAdd);
        arrayOfElements[currentCapacity] = newElement;
        siftUpElement(currentCapacity);
        currentCapacity++;
    }

    const T& top() {
        if (isEmpty()) {
            std::ostringstream stream;
            stream << "min_priority_heap_queue top failed. Queue is empty";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        return *arrayOfElements[0];
    }

    T pop() {
        if (isEmpty()) {
            std::ostringstream stream;
            stream << "min_priority_heap_queue pop failed. Queue is empty";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        // Handle empty

        T elementToRemove = T(*arrayOfElements[0]); // is this copying or just getting the value?
        arrayOfElements[0] = arrayOfElements[size() - 1];
        siftDownElement(0);
        currentCapacity--;
        return elementToRemove;
    }
};