#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>

template <typename T>
class linked_list {
    class Node {
        const T* object;
        Node* previous;
        Node* next;

     public:
        Node(const T& data, Node* tempPrevious = 0, Node* tempNext = 0) : object(new T(data)), previous(tempPrevious), next(tempNext) {}

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

        bool operator== (const Node & rhs) const {
            if (object == rhs.getData() && previous == rhs.getPrevious() && next == rhs.getNext()) {
                return true;
            }

            return false;
        }

        bool operator!= (const Node & rhs) const {
            return !(*this == rhs);
        }

        const T& operator*() const {
            return getData();
        }

        const T& operator->() const {
            return getData();
        }
    };

 public:
    class iterator : public std::iterator<std::forward_iterator_tag, Node*> {
        linked_list<T>& list;
        Node* itr;

     public:
        iterator(linked_list<T>& tempList, const Node* temp = NULL) : list(tempList), itr(temp) {}

        iterator(linked_list<T>& tempList, Node* temp = NULL) : list(tempList), itr(temp) {}

        iterator(const iterator& newItr) : list(newItr.list), itr(newItr.itr) {}

        T remove() {
            if (itr == NULL) { throw std::invalid_argument("Iterator refers to a NULL pointer");}

            Node* nodeToDelete = itr;
            operator++();
            T val = list.remove(nodeToDelete);
            return val;
        }

        iterator& operator++() {
            if (itr == NULL) { throw std::invalid_argument("Iterator refers to a NULL pointer");}

            itr = itr->getNext();
            return *this;
        }

        iterator operator++(int) {
            iterator result(*this);
            ++(*this);
            return result;
        }

        iterator& operator=(const Node* newItr) {
            itr = newItr;
            return *this;
        }

        iterator& operator=(Node* newItr) {
            itr = newItr;
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

    Node* getForwardNode(const int& position) const {
        if (position > (size() - 1)) {
            // Throw error
            std::ostringstream stream;
            stream << "linked_list getForwardNode failed (position = " << position << ", internalSize = " << size() << ")";
            std::cerr << stream.str() << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node* currentNode = head;
        int i = 0;

        while (i < position) {
            currentNode = currentNode->getNext();
            i++;
        }

        return currentNode;
    }

    T remove(Node* node) {
        int index = getIndex(node);
        return remove(index);
    }

    const int getIndex(Node* node) {
        if (node == head) { return -1; }
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
    linked_list() : head(NULL), tail(NULL), internalSize(0) {}

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
            Node* next = current->getNext();
            newNode->setNext(current);
            newNode->setPrevious(previous);
            previous->setNext(newNode);
            current->setPrevious(newNode);
        }

        internalSize++;
        return true;
    }

    bool insert(const int& position, const T* object) {
        return insert(position, *object);
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

    const T& item_at(const int & position) const {
        if (position >= size() || position < 0) {
            // Throw error
            std::cerr << "linked_list item_at failed (position = " << position << ", internalSize = " << size() << ")" << std::endl;
            throw std::out_of_range("Position is not valid inside this linked_list");
        }

        return getNode(position)->getData();
    }

    bool contains(const T & object) const {
        for (int i = 0; i < size(); i++) {
            if (item_at(i) == object) {
                return true;
            }
        }

        return false;
    }

    Node* begin() const {
        return head;
    }

    Node* end() const {
        return tail;
    }

    iterator getIterator(Node* node) {
        return iterator(*this, node);
    }

    bool push_front(const T & object) {
        return insert(0, object);
    }

    bool push_back(const T & object) {
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
        if (size() == 0) {
            return true;
        }

        return false;
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& os, linked_list<T>& list) {
    std::stringstream ss;
    std::stringstream newSS;
    typename linked_list<T>::iterator it = list.getIterator(list.begin());
    ss << "[";
    for (; it != NULL; it++) {
        ss << *it << ", ";
    }

    std::string str = ss.str();
    str = str.substr(0, str.size() - 2);
    str += "]";
    newSS << str;
    os << newSS.str();
    return os;
}
