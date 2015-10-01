// Circular single linked list

#ifndef SEBER_CIRCULAR_LINKED_LIST
#define SEBER_CIRCULAR_LINKED_LIST

// Should make begin() and end return constant I think
// issue with clear(); with last element!
// print fails when you add and remove all elements

template <typename T>
class circular_linked_list {
    class Node {
     public:
        Node (const T& data, Node* childPointer = NULL);
        ~Node();
        const T& getData() const;
        Node* getChildNode() const;
        void setChildNode(Node* newChildPointer);
        void print(std::ostream& stream);
        bool operator==(const Node& rhs);
        bool operator!=(const Node& rhs);
        const T& operator*() const;
        const T& operator->() const;
    };

 public:
    class iterator : public std::iterator<std::forward_iterator_tag, Node*> {
     public:
        iterator(circular_linked_list<T>& tempList, const Node* temp);
        iterator(circular_linked_list<T>& tempList, Node* temp);
        iterator(const iterator& newItr);
        T remove();
        const bool& endPassed() const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator=(const Node* newItr);
        iterator& operator=(Node* newItr);
        bool operator==(const iterator& rhs) const;
        bool operator==(const Node* rhs) const;
        bool operator!=(const iterator& rhs) const;
        bool operator!=(const Node* rhs) const;
        const T& operator*() const;
        const T& operator->() const;
    };

 private:
    const Node* getNode(const int& position) const;
    T remove(Node* element);
    const int& getIndex(Node* element) const;

 public:
    circular_linked_list();
    ~circular_linked_list();
    bool insert(const int& position, const T& object);
    bool insert(const int& position, const T* object);
    const T& item_at(const int& position) const;
    const Node* begin() const;
    iterator getIterator(Node* element);
    T remove(const int& position);
    const int size() const;
    void empty();
    friend std::ostream& operator<< (std::ostream& os, const circular_linked_list<T>& list);
};

#endif