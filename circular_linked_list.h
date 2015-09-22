// Circular single linked list

#ifndef SEBER_CIRCULAR_LINKED_LIST
#define SEBER_CIRCULAR_LINKED_LIST

// Should make begin() and end return constant I think
// issue with clear(); with last element!
// print fails when you add and remove all elements

template <typename T>
class circular_linked_list {
    class Element {
     public:
        Element (const T& data, Element* childPointer = NULL);
        ~Element();
        const T& getData() const;
        Element* getChildElement() const;
        void setChildElement(Element* newChildPointer);
        void print(std::ostream& stream);
        bool operator==(const Element& rhs);
        bool operator!=(const Element& rhs);
        const T& operator*() const;
        const T& operator->() const;
    };

    class iterator : public std::iterator<std::forward_iterator_tag, Element*> {
     public:
        iterator(circular_linked_list<T> & tempList, const Element* temp);
        iterator(circular_linked_list<T> & tempList, Element* temp);
        iterator(const iterator& newItr);
        T remove();
        const bool& endPassed() const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator=(const Element* newItr);
        iterator& operator=(Element* newItr);
        bool operator==(const iterator& rhs) const;
        bool operator==(const Element* rhs) const;
        bool operator!=(const iterator& rhs) const;
        bool operator!=(const Element* rhs) const;
        const T& operator*() const;
        const T& operator->() const;
    };

 private:
    const Element* getElement(const int& position) const;
    T remove(Element* element);
    const int& getIndex(Element* element) const;

 public:
    circular_linked_list();
    ~circular_linked_list();
    bool insert(const int& position, const T& object);
    bool insert(const int& position, const T* object);
    const T& at(const int& position) const;
    const Element* begin() const;
    iterator getIterator(Element* element);
    T remove(const int& position);
    const int getSize() const;
    void clear();
    friend std::ostream& operator<< (std::ostream& os, const circular_linked_list<T>& list);
};

#endif