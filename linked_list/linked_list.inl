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

#ifndef SEBER_LINKED_LIST_CPP
#define SEBER_LINKED_LIST_CPP

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>

template <typename T>
class linked_list {
    class Node {
        const T* object;
        Node* previous;
        Node* next;

     public:
        Node(const T& data, Node* tempPrevious = 0, Node* tempNext = 0) : object(new T(data)), previous(tempPrevious), next(tempNext) {}

        Node(const Node& newNode) : object(new T(newNode.getData())), previous(newNode.getPrevious()), next(newNode.getNext()) {}

        ~Node() {
            delete object;
            previous = NULL;
            next = NULL;
        }

        const T& getData() const {
            return *object;
        }

        Node* getNext() const {
            return next;
        }

        void setNext(Node* tempNext) {
            next = tempNext;
        }

        Node* getPrevious() const {
            return previous;
        }

        void setPrevious(Node* tempPrevious) {
            previous = tempPrevious;
        }

        void print(std::ostream& stream) const {
            stream << getData();
        }

        Node& operator=(const Node* otherNode) {
            object = new T(otherNode->getData());
            previous = otherNode->getPrevious();
            next = otherNode->getNext();
            return *this;
        }

        bool operator== (const Node& rhs) const {
            if (*object == rhs.getData() && previous == rhs.getPrevious() && next == rhs.getNext()) {
                return true;
            }

            return false;
        }

        bool operator!= (const Node& rhs) const {
            return !(*this == rhs);
        }

        const T& operator*() const {
            return getData();
        }

        const T& operator->() const {
            return getData();
        }

    };

    Node* head;
    Node* tail;
    int internalSize;

    Node* getNode(const int& position) const {
        if (position > (size() - 1)) {
            // Throw error
            std::ostringstream stream;
            stream << "linked_list getNode failed (position = " << position << ", internalSize = " << size() << ")";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node* currentNode;
        if (position < size()/2) {
            currentNode = head;
            int i = 0;

            while (i < position) {
                currentNode = currentNode->getNext();
                i++;
            }
        } else {
            currentNode = tail;
            int i = size() - 1;

            while (i > position) {
                currentNode = currentNode->getPrevious();
                i--;
            }
        }

        return currentNode;
    }

    T remove(Node* node) {
        int index = getIndex(node);
        return remove(index);
    }

    const int getIndex(Node* node) {
        int index = 0;
        iterator it = iterator(*this, begin());

        for (; it != end(); it++) {
            if (it == node) {
                return index;
            }

            index++;
        }

        return -1;
    }

 public:
    class iterator : public std::iterator<std::forward_iterator_tag, Node*> {
        linked_list<T>& list;
        Node* itr;

     public:
        iterator(linked_list<T>& tempList, Node* temp = NULL) : list(tempList), itr(temp) {}

        iterator(const iterator& newItr) : list(newItr.list), itr(newItr.itr) {}

        iterator& operator++() {
            if (itr == NULL) { throw std::invalid_argument("Iterator refers to a NULL pointer");}

            itr = itr->getNext();
            return *this;
        }

        iterator operator++(int) {
            iterator orig = *this;
            ++(*this);
            return orig;
        }

        iterator& operator--() {
            if (itr == NULL) { throw std::invalid_argument("Iterator refers to a NULL pointer");}

            itr = itr->getPrevious();
            return *this;
        }

        iterator operator--(int) {
            iterator orig = *this;
            ++(*this);
            return orig;
        }

        iterator& operator=(const Node& newItr) {
            list = newItr.list;
            itr = newItr.itr;
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return itr == rhs.itr;
        }

        bool operator==(const Node* rhs) const {
            return itr == rhs;
        }

        bool operator!=(const iterator& rhs) const {
            return !(*this == rhs);
        }

        bool operator!=(const Node* rhs) const {
            return !(*this == rhs);
        }

        const T& operator*() const {
            return itr->getData();
        }

        const T& operator->() const {
            return itr->getData();
        }
    };

 public:
    linked_list() : head(NULL), tail(NULL), internalSize(0) {}

    linked_list(linked_list<T>& otherList) : head(NULL), tail(NULL), internalSize(0) {
        *this = otherList;
    }

    ~linked_list() { empty(); }

    bool insert(const int& position, const T& object) {
        if (position > size() || position < 0) {
            // Throw error, out of bounds
            std::ostringstream stream;
            stream << "linked_list insert failed (position = " << position << ", object = " << object << ", internalSize = " << size() << ")";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node* newNode = new Node(object);

        if (!size()) {
            head = newNode;
            tail = newNode;
        } else if (!position) {
            newNode->setNext(head);
            head->setPrevious(newNode);
            head = newNode;
        } else if (position  == size()) {
            newNode->setPrevious(tail);
            tail->setNext(newNode);
            tail = newNode;
        } else {
            Node* current = getNode(position);
            Node* previous = current->getPrevious();
            newNode->setNext(current);
            newNode->setPrevious(previous);
            previous->setNext(newNode);
            current->setPrevious(newNode);
        }

        internalSize++;
        return true;
    }

    bool replace(const int& position, const T& data) {
        Node* newNode = new Node(data);
        Node* oldNode = getNode(position);
        Node* previous = oldNode->getPrevious();
        Node* next = oldNode->getNext();
        newNode->setPrevious(previous);
        previous->setNext(newNode);
        newNode->setNext(next);
        next->setPrevious(newNode);
        delete oldNode;
        return true;
    }

    const T& item_at(const int& position) const {
        if (position >= size() || position < 0) {
            // Throw error
            std::cerr << "linked_list item_at failed (position = " << position << ", internalSize = " << size() << ")" << std::endl;
            throw std::out_of_range("Position is not valid inside this linked_list");
        }

        return getNode(position)->getData();
    }

    bool contains(const T& object) {
        iterator it = getIterator(begin());
        for (; it != end(); it++) {
            if (*it == object) {
                return true;
            }
        }

        return false;
    }

    Node* begin() const {
        return head;
    }

    // useful if you are reverse iterating
    Node* front() const {
        return NULL;
    }

    // useful if you are reverse iterating
    Node* back() const {
        return tail;
    }

    Node* end() const {
        return NULL;
    }

    iterator getIterator(Node* node) {
        return iterator(*this, node);
    }

    linked_list<T>& operator=(const linked_list<T>& otherList) {
        empty();
        for (int index = 0; index < otherList.size(); index++) {
            push_back(otherList.item_at(index));
        }

        // This method is terrible. It should be using
        // an iterator, but the iterators are not const!

        return *this;
    }

    bool push_front(const T& object) {
        return insert(0, object);
    }

    bool push_back(const T& object) {
        return insert(size(), object);
    }

    T pop_front() {
        return remove(0);
    }

    T pop_back() {
        return remove(size() - 1);
    }

    T remove(const int& position) {
        if (position >= size() || position < 0) {
            // Throw error, out of bounds
            std::ostringstream stream;
            stream << "linked_list remove failed (position = " << position << ", internalSize = " << size() << ")";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node* nodeToDelete = getNode(position);
        T val = nodeToDelete->getData();

        if (position == 0 && size() == 1) {   // Head, Size == 1
            head = NULL;
            tail = NULL;
        } else if (position == 0 && size() > 1) {    // Head, Size > 1
            head = getNode(1);
            head->setPrevious(NULL);
        } else if (position < (size() - 1) && position != 0) {   // Middle
            getNode(position - 1)->setNext(getNode(position + 1));
            getNode(position)->setPrevious(getNode(position - 1));
        } else if (position == (size() - 1)) {   // Tail
            tail = getNode(position - 1);
            tail->setNext(NULL);
        }

        internalSize--;
        delete nodeToDelete;
        return val;
    }

    const int size() const {
        return internalSize;
    }

    void empty() {
        while (size()) {
            pop_front();
        }
    }

    bool isEmpty() {
        return !size();
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& os, const typename linked_list<T>::Node& node) {
    return os << node.getData();
}

template <typename T>
std::ostream& operator<< (std::ostream& os, linked_list<T>& list) {
    std::stringstream ss;
    std::stringstream newSS;
    typename linked_list<T>::iterator it = list.getIterator(list.begin());
    ss << "[";
    for (; it != list.end(); it++) {
        ss << *it << ", ";
    }

    std::string str = ss.str();
    str = str.substr(0, str.size() - 2);
    str += "]";
    newSS << str;
    os << newSS.str();
    return os;
}

#endif
