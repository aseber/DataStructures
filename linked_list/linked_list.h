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

// Doubly linked list

#ifndef SEBER_LINKED_LIST
#define SEBER_LINKED_LIST

template <typename T>
class linked_list {
    class Node {
     public:
        Node(const T& data, Node* parentNode = 0, Node* childNode = 0);
        ~Node();
        const T& getData() const;
        Node* getParentNode() const;
        void setParentNode(Node* newNode);
        Node* getChildNode() const;
        void setChildNode(Node* newNode);
        void print(std::ostream& stream);
        bool operator== (const Node& rhs);
        bool operator!= (const Node& rhs);
        const T& operator*() const;
        const T& operator->() const;
        // Node& operator= (Node rhs);
        // bool setData(const T data);
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
    T remove(Node* node);
    const Node* getForwardNode(const int& position) const;
    const int& getIndex(Node* node) const;

 public:
    linked_list();
    ~linked_list();
    // bool operator!= (const linked_list<T> & rhs);
    // bool operator== (const linked_list<T> & rhs);
    // linked_list<T> & operator= (const linked_list<T> & rhs);
    // linked_list<T> & operator+ (linked_list<T> & rhs);
    bool insert(const int& position, const T& object);
    bool insert(const int& position, const T* object);
    const T& item_at(const int & position) const;
    const Node* begin() const;
    const Node* end() const;
    iterator getIterator(Node* element);
    bool push_front(const T& object);
    bool push_back(const T& object);
    T pop_front();
    T pop_back();
    T remove(const int& position);
    // int findNode(const T& node, const int & position = 0);
    // linked_list<int> findAllNodes(const T & node);
    // int findNumAllNodes(const T & node);
    const int size() const;
    // bool replace(const int& position, const T& data);
    // bool contains(const T& object);
    bool empty();
    friend std::ostream& operator<< (std::ostream& os, const circular_linked_list<T>& list);
};

#endif
