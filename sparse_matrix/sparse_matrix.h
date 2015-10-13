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

#ifndef SEBER_SPARSE_MATRIX_CPP
#define SEBER_SPARSE_MATRIX_CPP

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "linked_list.h"
#include "general.h"

template <typename T>
class Element {};

template <typename T>
class sparse_matrix {
    const int findIndex(const int&, const linked_list<Element<T> >*) const;

 public:
    sparse_matrix();
    sparse_matrix(const int&, const int&);
    ~sparse_matrix();
    void insert(const int&, const int&, const T&);
    void read();
    const T item_at(const int&, const int&) const;
    T remove(const int&, const int&);
    void mask(const sparse_matrix<bool>&, sparse_matrix<T>&);
    const int* size() const;
    void setSize(const int&, const int&);
    void empty();
    bool isEmpty() const;
    void print();
};

template <typename Y>
std::ostream& operator<< (std::ostream&, const Element<Y>&);
template <typename Y>
std::ostream& operator<< (std::ostream&, sparse_matrix<Y>&);

#endif
