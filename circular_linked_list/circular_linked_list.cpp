#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

// Circular single linked list

template <typename T>
class circular_linked_list {
 public:
    class Node {
        const T* object;    // Immutable after initialization
        Node* next;     // Mutable

     public:
        Node (const T& data, Node* tempNext = NULL) : object(new T(data)), next(tempNext) {}

        ~Node() {
            delete object;
            next = NULL;
        }

        const T& getData() const {
            return *object;
        }

        Node* getChildNode() const {
            return next;
        }

        void setChildNode(Node* tempNext) {
            next = tempNext;
        }

        void print(std::ostream& stream) const {
            stream << getData();
        }

        bool operator==(const Node& rhs) const {
            if (object == rhs.getData() && next == rhs.getChildNode()) {
                return true;
            }

            return false;
        }

        bool operator!=(const Node& rhs) const {
            // std::cout << !(*this == rhs) << std::cout;
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
        circular_linked_list<T>& list;
        bool endFlag;
        Node* itr;

     public:
        iterator(circular_linked_list<T>& tempList, const Node* temp = NULL) : list(tempList), endFlag(!(list.size())), itr(temp) {}

        iterator(circular_linked_list<T>& tempList, Node* temp = NULL) : list(tempList), endFlag(!(list.size())), itr(temp) {}

        iterator(const iterator& newItr) : list(newItr.list), endFlag(!(list.size())), itr(newItr.itr) {}

        T remove() {
            if (itr == NULL) { throw std::invalid_argument("Iterator refers to a NULL pointer");}

            Node* nodeToDelete = itr;
            operator++();
            T val = list.remove(nodeToDelete);
            endFlag = !(list.size());
            return val;
        }

        const bool& endPassed() const { return endFlag; }

        iterator& operator++() {
            if (itr == NULL) { throw std::invalid_argument("Iterator refers to a NULL pointer");}

            do {
                Node * newItr = itr->getChildNode();
                if (itr == list.head) {endFlag = true;}
                itr = newItr;
            } while (itr == list.head);

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

 private:
    Node * head;
    Node * tail;
    int internalSize;

    Node* getNode(const int& position) const {
        if (position < 0 || position > size() - 1) {
            // Throw error
            std::ostringstream stream;
            stream << "circular_linked_list getNode failed (position = " << position << ", internalSize = " << size() << ")";
            stream << std::endl;
            throw std::out_of_range(stream.str());
        }
        Node* currentNode = head->getChildNode();
        int i = 0;

        while (i < position) {
            currentNode = currentNode->getChildNode();
            if (currentNode != head) {
                i++;
            }
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

        for (; !it.endPassed(); it++) {
            if (it == node) {
                return index;
            }

            index++;
        }

        return -1;
    }

 public:
    circular_linked_list() : head(new Node(T())), tail(NULL), internalSize(1) {
        tail = head;
        head->setChildNode(head);
    }

    ~circular_linked_list() { clear(); }

    bool insert(const int& position, const T& object) {
        if (position < 0 || position > size()) {
            // Throw error, out of bounds
            std::ostringstream stream;
            stream << "circular_linked_list insert failed (position = " << position << ", object = " << object << ", internalSize = " << size() << ")";
            stream << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node* newNode = new Node(object);

        if (!size()) {
            newNode->setChildNode(head);
            head->setChildNode(newNode);
            tail = newNode;
        } else if (!position) {
            newNode->setChildNode(getNode(0));
            head->setChildNode(newNode);
        } else if (position  == size()) {
            newNode->setChildNode(head);
            tail->setChildNode(newNode);
            tail = newNode;
        } else {
            newNode->setChildNode(getNode(position));
            getNode(position - 1)->setChildNode(newNode);
        }

        internalSize++;
        return true;
    }

    bool insert(const int& position, const T* object) {
        return insert(position, *object);
    }

    const T& item_at(const int& position) const {
        if (position < 0 || position > size() - 1) {
            // Throw error
            std::ostringstream stream;
            stream << "circular_linked_list at failed (position = " << position << ", internalSize = " << size() << ")";
            stream << std::endl;
            throw std::out_of_range(stream.str());
        }

        return getNode(position)->getData();
    }

    Node* begin() const {
        if (size()) {
            return head->getChildNode();
        }

        return NULL;
    }

    iterator getIterator(Node* node) {
        return iterator(*this, node);
    }

    T remove(const int& position) {
        if (position < 0 || position > size() - 1) {
            // Throw error, out of bounds
            std::ostringstream stream;
            stream << "circular_linked_list remove failed (position = " << position << ", internalSize = " << size() << ")";
            stream << std::endl;
            throw std::out_of_range(stream.str());
        }

        Node * nodeToDelete = getNode(position);
        T val = nodeToDelete->getData();

        if (size() == 1) {
            tail = head;
            head->setChildNode(head);
        } else if (!position) {
            head->setChildNode(getNode(1));
        } else if (position == size() - 1) {
            tail = getNode(size() - 2);
            tail->setChildNode(head);
        } else {
            getNode(position - 1)->setChildNode(getNode(position + 1));
        }

        internalSize--;
        delete nodeToDelete;
        return val;
    }

    const int size() const { return internalSize - 1; }

    void clear() {
        iterator it = getIterator(begin());

        for (; !it.endPassed();) {
            it.remove();
        }
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& os, circular_linked_list<T>& list) {
    std::stringstream ss;
    std::stringstream newSS;
    typename circular_linked_list<T>::iterator it = list.getIterator(list.begin());
    ss << "[";

    for (; !it.endPassed(); it++) {
        ss << *it << ", ";
    }

    std::string str = ss.str();
    str = str.substr(0, str.size() - 2);
    str += "]";
    newSS << str;
    os << newSS.str();
    return os;
}
