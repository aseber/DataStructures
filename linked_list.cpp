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
#include <typeinfo>

template <typename T>
class linked_list {
    class Node {
        T object;
        Node * parent;
        Node * child;

     public:
        Node(const T data, Node * parentElement = 0, Node * childElement = 0) : object(data), parent(parentElement), child(childElement) {}
        ~Node() {
            parent = NULL;
            child = NULL;
        }

        bool operator== (const Node & rhs) const {
            if (object == rhs.getData() && parent == rhs.getParentNode() && child == rhs.getChildNode()) {
                return true;
            }

            return false;
        }

        bool operator!= (const Node & rhs) const {
            return !(*this == rhs);
        }

        /*bool operator= ()

        Node & operator= (Node rhs) {

            if (this != &rhs) {

                clear();

                if (size) {

                    head = rhs.getNode(0);
                    tail = rhs.getNode(size - 1);
                    size = rhs.getSize();

                }

            }

            return *this;

        }*/

        bool setParentNode(Node * element) {
            parent = element;
            return true;
        }

        Node* getParentNode() const {
            return parent;
        }

        bool clearParentNode() {
            parent = NULL;
            return true;
        }

        bool setChildNode(Node * element) {
            child = element;
            return true;
        }

        Node* getChildNode() const {
            return child;
        }

        bool clearChildNode() {
            child = NULL;
            return true;
        }

        bool setData(const T data) {
            object = data;
            return true;
        }

        T getData() const {
            return object;
        }

        void print(std::ostream & stream) const {
            stream << object;
        }
    };

    Node * head;
    Node * tail;
    int size;

    Node * getNode(const int position) const {
        if (position > (size - 1)) {
            // Throw error
            std::ostringstream stream;
            stream << "linked_list getNode failed (position = " << position << ", size = " << size << ")";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node * currentNode;
        if (position < size/2) {
            currentNode = head;
            int i = 0;

            while (i < position) {
                currentNode = currentNode->getChildNode();
                i++;
            }
        } else {
            currentNode = tail;
            int i = size - 1;

            while (i > position) {
                currentNode = currentNode->getParentNode();
                i--;
            }
        }

        return currentNode;
    }

    Node * getBasicNode(const int position) const {
        if (position > (size - 1)) {
            // Throw error
            std::ostringstream stream;
            stream << "linked_list getNode failed (position = " << position << ", size = " << size << ")";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node * currentNode = head;
        int i = 0;

        while (i < position) {
            currentNode = currentNode->getChildNode();
            i++;
        }

        return currentNode;
    }

 public:
    linked_list() : head(NULL), tail(NULL), size(0) {}
    /*linked_list(std::initializer_list<T> args) : head(NULL), tail(NULL), size(0) {
        typename std::initializer_list<T>::iterator it;

        for (it = args.begin(); it != args.end(); ++it) {
            push_back(*it);
        }
    }*/
    /*linked_list(linked_list<T> && other) : head(NULL), tail(NULL), size(0) {
        for (int i = 0; i < other.getSize(); i++) {
            push_back(other.pop_front());
        }
    }*/
    linked_list(int count, const T & initial_value) : head(NULL), tail(NULL), size(0) {
        for (int i = 0; i < count; i++) {
            push_back(initial_value);
        }
    }

    ~linked_list() {
        clear();
    }

    bool operator== (const linked_list<T> & rhs) const {
        if (size != rhs.getSize()) {
            return false;
        }

        for (int i = 0; i < size; i++) {
            if (getData(i) != rhs.getData(i)) {
                return false;
            }
        }

        return true;
    }

    bool operator!= (const linked_list<T> & rhs) const {
        return !(*this == rhs);
    }

    linked_list<T> & operator= (const linked_list<T> & rhs) {
        if (this != &rhs) {
            clear();

            for (int i = 0; i < rhs.getSize(); i++) {
                push_back(rhs.getData(i));
            }

            // head = rhs.getNode(0);
            // tail = rhs.getNode(size - 1); // Should not set to the pointer
            // size = rhs.getSize(); // because if we delete one, it breaks
                                    // the other (even a copy!)
        }

        return *this;
    }

    /*linked_list<T> & operator= (linked_list<T>&& rhs) {

        if (this != &rhs) {

            clear();

            for (int i = 0; i < rhs.getSize(); i++) {

                push_back(rhs.pop_front());

            }

        }

        return *this;

    }*/

    /*linked_list<T> & operator=(linked_list<T> rhs) {

        if (this != &rhs) {

            clear();

            for (int i = 0; i < rhs.getSize(); i++) {

                push_back(rhs.getData(i));

            }

        }

    }*/// Broken? Useless?

    linked_list<T> & operator+ (linked_list<T> & rhs) {
        for (int i = 0; i < rhs.getSize(); i++) {
            push_back(rhs.getData(i));
        }

        return *this;
    }

    bool insert(const int & position, const T & object) {
        if (position > size || position < 0) {
            // Throw error, out of bounds
            std::ostringstream stream;
            stream << "linked_list insert failed (position = " << position << ", object = " << object << ", size = " << size << ")";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node * newNode = new Node(object);

        if (position == 0 && size == 0) {   // Header && size == 0
            head = newNode;
            tail = newNode;
            size++;
            return true;
        }

        if (position == 0 && size > 0) {    // Header && size > 0
            newNode->setChildNode(head);
            head->setParentNode(newNode);
            head = newNode;
            size++;
            return true;
        }

        if (position < (size - 1) && position != 0) {   // Middle
            newNode->setChildNode(getBasicNode(position));
            newNode->setParentNode(getBasicNode(position - 1));
            getBasicNode(position - 1)->setChildNode(newNode);
            getBasicNode(position + 1)->setParentNode(newNode);
            size++;
            return true;
        }

        if (position == size && size > 0) {    // Tail
            newNode->setParentNode(tail);
            getNode(position - 1)->setChildNode(newNode);
            tail = newNode;
            size++;
            return true;
        }

        std::cout << "WARNING! Insert not handled!" << std::endl;

        return false;
    }

    bool push_front(const T & object) {
        return insert(0, object);
    }

    bool push_back(const T & object) {
        return insert(size, object);
    }

    int findElement(const T & element, const int & position = 0) const {
        if (position >= size || position < 0) {
            // Throw error, out of bounds
            std::ostringstream stream;
            stream << "linked_list findElement failed (position = " << position << ", size = " << size << ")";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        for (int i = position; i < getSize(); i++) {
            if (getData(i) == element) {
                return i;
            }
        }

        return -1;
    }

    linked_list<int> findAllElements(const T & element) const {
        linked_list<int> list;
        int position = findElement(element, 0);

        while (position != -1) {
            list.push_back(position);

            if (position != getSize() - 1) {
                position = findElement(element, position + 1);
            } else {
                position = -1;
            }
        }

        return list;
    }

    int findNumAllElements(const T & element) const {
        return findAllElements(element).getSize();
    }

    bool insert(const int & position, const T objects[], const int size) {
        int i = 0;
        bool shouldContinue = true;

        while (i < size && shouldContinue) {
            shouldContinue = insert(position + i, objects[i]);
            i++;
        }

        return shouldContinue;
    }

    T remove(const int & position) {
        if (position >= size || position < 0) {
            // Throw error, out of bounds
            std::ostringstream stream;
            stream << "linked_list remove failed (position = " << position << ", size = " << size << ")";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node * nodeToDelete;

        if (position == 0 && size == 1) {   // Head, Size == 1
            nodeToDelete = head;
            T val = nodeToDelete->getData();
            head = NULL;
            tail = NULL;
            size--;
            // delete nodeToDelete;
            return val;
        }

        if (position == 0 && size > 1) {    // Head, Size > 1
            nodeToDelete = head;
            T val = nodeToDelete->getData();
            getNode(1)->clearParentNode();
            head = getNode(1);
            size--;
            // delete nodeToDelete;
            return val;
        }

        if (position < (size - 1) && position != 0) {   // Middle
            nodeToDelete = getNode(position);
            T val = nodeToDelete->getData();
            getNode(position - 1)->setChildNode(getNode(position + 1));
            getNode(position)->setParentNode(getNode(position - 1));
            size--;
            // delete nodeToDelete;
            return val;
        }

        if (position == (size - 1)) {   // Tail
            nodeToDelete = getNode(position);
            T val = nodeToDelete->getData();
            getNode(position - 1)->clearChildNode();
            tail = getNode(position - 1);
            size--;
            // delete nodeToDelete;
            return val;
        }

        std::ostringstream stream;
        stream << "WARNING! remove not handled! Position = " << position << " Size = " << size;
        std::cerr << stream.str() << std::endl;
        throw std::out_of_range(stream.str());
    }

    int getSize() const {
        return size;
    }

    // int size() const {

        // return size; // I like to name variables such that they're useful
        // The only reason this one is here is to make the testing program work

    // }

    T getData(const int & position) const {
        if (position >= size || position < 0) {
            // Throw error
            std::cerr << "linked_list getData failed (position = " << position << ", size = " << size << ")" << std::endl;
            throw std::out_of_range("Position is not valid inside this linked_list");
        }

        return getNode(position)->getData();
    }

    bool setData(const int & position, const T & data) {
        return getNode(position)->setData(data);
    }

    bool elementExists(const T & object) const {
        for (int i = 0; i < size; i++) {
            if (getData(i) == object) {
                return true;
            }
        }

        return false;
    }

    T begin() const {
        return head->getData();
    }

    T end() const {
        return tail->getData();
    }

    T pop_front() {
        return remove(0);
    }

    T pop_back() {
        return remove(size - 1);
    }

    T item_at(const int & position) const {
        if (position >= size || position < 0) {
            // Throw error
            std::cerr << "linked_list item_at failed (position = " << position << ", size = " << size << ")" << std::endl;
            throw std::out_of_range("Position is not valid inside this linked_list");
        }

        return getNode(position)->getData();
    }

    T * toArray() const {
        T * array = new T[size];

        for (int i = 0; i < size; i++) {
            array[i] = getNode(i)->getData();
        }

        return array;
    }

    bool empty() const {
        if (size == 0) {
            return true;
        }

        return false;
    }

    bool clear() {
        while (getSize()) {
            pop_front();
        }

        return true;
    }

    void print(std::ostream & stream) const {
        if (size >= 0) {
            stream << "{";
            int i = 0;
            while (i < size) {
                getNode(i)->print(stream);
                if (i != size - 1) {
                    stream << ", ";
                }

                i++;
            }

            stream << "}";
        } else {
            stream << "Bad list data, size is negative.";
        }
    }
};
