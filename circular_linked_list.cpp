#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

// Circular single linked list

template <typename T>
class circular_linked_list {
 public:
    class Element {
        const T* object;    // Immutable after initialization
        Element* next;     // Mutable

     public:
        Element (const T& data, Element* tempNext = NULL) : object(new T(data)), next(tempNext) {}

        ~Element() {
            delete object;
            next = NULL;
        }

        const T& getData() const {
            return *object;
        }

        Element* getChildElement() const {
            return next;
        }

        void setChildElement(Element* tempNext) {
            next = tempNext;
        }

        void print(std::ostream& stream) const {
            stream << getData();
        }

        bool operator==(const Element& rhs) const {
            if (object == rhs.getData() && next == rhs.getChildElement()) {
                return true;
            }

            return false;
        }

        bool operator!=(const Element& rhs) const {
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
    class iterator : public std::iterator<std::forward_iterator_tag, Element*> {
        circular_linked_list<T>& list;
        bool endFlag;
        Element* itr;

     public:
        iterator(circular_linked_list<T>& tempList, const Element* temp = NULL) : list(tempList), endFlag(!(list.getSize())), itr(temp) {}

        iterator(circular_linked_list<T>& tempList, Element* temp = NULL) : list(tempList), endFlag(!(list.getSize())), itr(temp) {}

        iterator(const iterator& newItr) : list(newItr.list), endFlag(!(list.getSize())), itr(newItr.itr) {}

        T remove() {
            if (itr == NULL) { throw std::invalid_argument("Iterator refers to a NULL pointer");}

            Element* elementToDelete = itr;
            operator++();
            T val = list.remove(elementToDelete);
            endFlag = !(list.getSize());
            return val;
        }

        const bool& endPassed() const { return endFlag; }

        iterator& operator++() {
            if (itr == NULL) { throw std::invalid_argument("Iterator refers to a NULL pointer");}

            do {
                Element * newItr = itr->getChildElement();
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

        iterator& operator=(const Element* newItr) {
            itr = newItr;
            return *this;
        }

        iterator& operator=(Element* newItr) {
            itr = newItr;
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return itr == rhs.itr;
        }

        bool operator==(const Element* rhs) const {
            return itr == rhs;
        }

        bool operator!=(const iterator& rhs) const {
            return !(*this == rhs);
        }

        bool operator!=(const Element* rhs) const {
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
    Element * head;
    Element * tail;
    int size;

    Element* getElement(const int& position) const {
        if (position < 0 || position > getSize() - 1) {
            // Throw error
            std::ostringstream stream;
            stream << "circular_linked_list getElement failed (position = " << position << ", size = " << getSize() << ")";
            stream << std::endl;
            throw std::out_of_range(stream.str());
        }
        Element* currentElement = head->getChildElement();
        int i = 0;

        while (i < position) {
            currentElement = currentElement->getChildElement();
            if (currentElement != head) {
                i++;
            }
        }

        return currentElement;
    }

    T remove(Element* element) {
        int index = getIndex(element);
        return remove(index);
    }

    const int getIndex(Element* element) {
        if (element == head) { return -1; }
        int index = 0;
        iterator it = iterator(*this, begin());

        for (; !it.endPassed(); it++) {
            if (it == element) {
                return index;
            }

            index++;
        }

        return -1;
    }

 public:
    circular_linked_list() : head(new Element(T())), tail(NULL), size(1) {
        tail = head;
        head->setChildElement(head);
    }

    ~circular_linked_list() { clear(); }

    bool insert(const int& position, const T& object) {
        if (position < 0 || position > getSize()) {
            // Throw error, out of bounds
            std::ostringstream stream;
            stream << "circular_linked_list insert failed (position = " << position << ", object = " << object << ", size = " << getSize() << ")";
            stream << std::endl;
            throw std::out_of_range(stream.str());
        }

        Element* newElement = new Element(object);

        if (!getSize()) {
            newElement->setChildElement(head);
            head->setChildElement(newElement);
            tail = newElement;
        } else if (!position) {
            newElement->setChildElement(getElement(0));
            head->setChildElement(newElement);
        } else if (position  == getSize()) {
            newElement->setChildElement(head);
            tail->setChildElement(newElement);
            tail = newElement;
        } else {
            newElement->setChildElement(getElement(position));
            getElement(position - 1)->setChildElement(newElement);
        }

        size++;
        return true;
    }

    bool insert(const int& position, const T* object) {
        return insert(position, *object);
    }

    const T& at(const int& position) const {
        if (position < 0 || position > getSize() - 1) {
            // Throw error
            std::ostringstream stream;
            stream << "circular_linked_list at failed (position = " << position << ", size = " << getSize() << ")";
            stream << std::endl;
            throw std::out_of_range(stream.str());
        }

        return getElement(position)->getData();
    }

    Element* begin() const {
        if (getSize()) {
            return head->getChildElement();
        }

        return NULL;
    }

    iterator getIterator(Element* element) {
        return iterator(*this, element);
    }

    T remove(const int& position) {
        if (position < 0 || position > getSize() - 1) {
            // Throw error, out of bounds
            std::ostringstream stream;
            stream << "circular_linked_list remove failed (position = " << position << ", size = " << getSize() << ")";
            stream << std::endl;
            throw std::out_of_range(stream.str());
        }

        Element * elementToDelete = getElement(position);
        T val = elementToDelete->getData();

        if (getSize() == 1) {
            tail = head;
            head->setChildElement(head);
        } else if (!position) {
            head->setChildElement(getElement(1));
        } else if (position == getSize() - 1) {
            tail = getElement(getSize() - 2);
            tail->setChildElement(head);
        } else {
            getElement(position - 1)->setChildElement(getElement(position + 1));
        }

        size--;
        delete elementToDelete;
        return val;
    }

    const int getSize() const { return size - 1; }

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
