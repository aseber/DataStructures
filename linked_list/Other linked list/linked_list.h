// Doubly linked list

#ifndef SEBER_LINKED_LIST
#define SEBER_LINKED_LIST

template <typename T>
class linked_list {
    class Node {
     public:
        Node(const T data, Node * parentElement = 0, Node * childElement = 0);
        ~Node();
        bool operator== (const Node & rhs);
        bool operator!= (const Node & rhs);
        Node & operator= (Node rhs);
        bool setParentNode(Node * element);
        Node* getParentNode();
        bool clearParentNode();
        bool setChildNode(Node * element);
        Node* getChildNode();
        bool clearChildNode();
        bool setData(const T data);
        T getData();
        void print(std::ostream & stream);
    };

    Node * getNode(const int position);
    Node * getBasicNode(const int position);

 public:
    linked_list();
    linked_list(int count, const T & initial_value);
    ~linked_list();
    bool operator== (const linked_list<T> & rhs);
    bool operator!= (const linked_list<T> & rhs);
    linked_list<T> & operator= (const linked_list<T> & rhs);
    linked_list<T> & operator+ (linked_list<T> & rhs);
    bool insert(const int & position, const T & object);
    bool push_front(const T & object);
    bool push_back(const T & object);
    int findElement(const T & element, const int & position = 0);
    linked_list<int> findAllElements(const T & element);
    int findNumAllElements(const T & element);
    bool insert(const int & position, const T objects[], const int size);
    T remove(const int & position);
    int getSize();
    T getData(const int & position);
    bool setData(const int & position, const T & data);
    bool elementExists(const T & object);
    T begin();
    T end();
    T pop_front();
    T pop_back();
    T item_at(const int & position);
    T * toArray();
    bool empty();
    bool clear();
    void print(std::ostream & stream);
};

#endif
