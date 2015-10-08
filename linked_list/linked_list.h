// Doubly linked list

#ifndef SEBER_LINKED_LIST_H
#define SEBER_LINKED_LIST_H

template <typename T>
class linked_list {
    class Node {
     public:
        Node(const T&, Node*, Node*);
        Node(const Node&);
        ~Node();
        const T& getData() const;
        Node* getNext() const;
        void setNext(Node*);
        Node* getPrevious() const;
        void setPrevious(Node*);
        void print(std::ostream&) const;
        Node& operator=(const Node*);
        bool operator== (const Node&) const;
        bool operator!= (const Node&) const;
        const T& operator*() const;
        const T& operator->() const;
        friend std::ostream& operator<< (std::ostream&, const Node&);
    };

    Node* getNode(const int&) const;
    T remove(Node*);
    const int getIndex(Node*);

 public:
    class iterator : public std::iterator<std::forward_iterator_tag, Node*> {
     public:
        iterator(linked_list<T>&, const Node*);
        iterator(const iterator&);
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator=(const Node&);
        bool operator==(const iterator&) const;
        bool operator==(const Node&) const;
        bool operator!=(const iterator&) const;
        bool operator!=(const Node&) const;
        const T& operator*() const;
        const T& operator->() const;
    };

    linked_list();
    linked_list(const linked_list<T>&);
    ~linked_list();
    bool insert(const int&, const T&);
    bool replace(const int&, const T&);
    const T& item_at(const int&) const;
    bool contains(const T&);
    Node* begin() const;
    Node* front() const;
    Node* back() const;
    Node* end() const;
    iterator getIterator(Node*);
    linked_list<T>& operator=(const linked_list<T>&);
    bool push_front(const T&);
    bool push_back(const T&);
    T pop_front();
    T pop_back();
    T remove(const int&);
    const int size() const;
    void empty();
    bool isEmpty();
    friend std::ostream& operator<< (std::ostream&, linked_list<T>&);
};

#endif
