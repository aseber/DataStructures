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
#include "linked_list.inl"
#include "general.cpp"

template <typename T>
class Element {
 public:
    int index;
    T value;
};

template <typename T>
class sparse_matrix {
    linked_list<Element<T> >** rows;
    int internalSize[2];

    // Finding index assumes we are working with a particular row in the rows array
    const int findIndex(const int& columnIndex, const linked_list<Element<T> >* row) const {
        for (int index = 0; index < row->size(); index++) {
            if (row->item_at(index).index == columnIndex) {
                return index;
            }
        }

        return -1;
    }

 public:
    sparse_matrix() : rows(new linked_list<Element<T> >*[0]), internalSize{0, 0} {}

    sparse_matrix(const int& numRows, const int& numColumns) : rows(new linked_list<Element<T> >*[numRows]), internalSize{numRows, numColumns} {
        for (int index = 0; index < numRows; index++) {
            rows[index] = new linked_list<Element<T> >();
        }
    }

    ~sparse_matrix() {
        empty();

        for (int index = 0; index < size()[0]; index++) {
            delete rows[index];
            rows[index] = NULL;
        }

        delete rows;
    }

    void insert(const int& rowIndex, const int& columnIndex, const T& object) {
        if (rowIndex < 1 || columnIndex < 1 || rowIndex > size()[0] || columnIndex > size()[1]) {
            std::ostringstream stream;
            stream << "sparse_matrix item_at failed: (" << rowIndex << ", " << columnIndex << ") | internalSize: (" << (size())[0] << ", " << (size())[1] << ") | object = " << object;
            std::cout << stream.str() << std::endl;
            return;
            // throw std::out_of_range(stream.str());
        } else if (!object) {
            std::ostringstream stream;
            stream << "sparse_matrix item_at failed: (" << rowIndex << ", " << columnIndex << ") | internalSize: (" << (size())[0] << ", " << (size())[1] << ") | object = !object";
            std::cout << stream.str() << std::endl;
            return;
            // throw std::out_of_range(stream.str());
        }

        linked_list<Element<T> >* row = rows[rowIndex - 1];
        // std::cout << row << std::endl;
        int index = findIndex(columnIndex, row);
        if (index == -1) {
            Element<T> newElement;
            newElement.index = columnIndex;
            newElement.value = object;
            row->push_back(newElement);
        } else {
            Element<T> newElement = row->remove(index);
            newElement.value = object;
            row->insert(index, newElement);
        }
    }

    void read() {
        string input;
        linked_list<string> list;

        // Enter size
        std::cout << "Enter number of rows, columns" << std::endl;
        getline(std::cin, input);
        list = stringTokenizer(input, " ");
        setSize(atoi(list.item_at(0).c_str()), atoi(list.item_at(1).c_str()));

        for (int rowIndex = 1; rowIndex <= size()[0]; rowIndex++) {
            std::cout << "Enter number of terms in row " << rowIndex << std::endl;
            getline(std::cin, input);
            list = stringTokenizer(input, " ");
            int numElements = atoi(list.item_at(0).c_str());
            if (numElements) {
                std::cout << "Enter element's column, and value of each term in row " << rowIndex << std::endl;
                getline(std::cin, input);
                list = stringTokenizer(input, " ");
                std::cout << list << std::endl;
                for (int numColumns = 0; numColumns < numElements; numColumns++) {
                    insert(rowIndex, atoi(list.item_at(numColumns * 2).c_str()), atoi(list.item_at(numColumns * 2 + 1).c_str()));
                }
            }
        }
    }

    const T item_at(const int& rowIndex, const int& columnIndex) const {
        if (rowIndex < 1 || columnIndex < 1 || rowIndex > size()[0] || columnIndex > size()[1]) {
            std::ostringstream stream;
            stream << "sparse_matrix item_at failed: (" << rowIndex << ", " << columnIndex << ") | internalSize: (" << (size())[0] << ", " << (size())[1] << ")";
            std::cout << stream.str() << std::endl;
            return T();
            // throw std::out_of_range(stream.str());
        }

        linked_list<Element<T> >* row = rows[rowIndex - 1];
        int index = findIndex(columnIndex, row);
        if (index == -1) {
            return T();
        } else {
            return row->item_at(index).value;
        }
    }

    T remove(const int& rowIndex, const int& columnIndex) {

        if (rowIndex < 1 || columnIndex < 1 || rowIndex > size()[0] || columnIndex > size()[1]) {
            std::ostringstream stream;
            stream << "sparse_matrix remove failed: (" << rowIndex << ", " << columnIndex << ") | internalSize: (" << (size())[0] << ", " << (size())[1] << ")";
            std::cout << stream.str() << std::endl;
            return T();
            // throw std::out_of_range(stream.str());
        }

        linked_list<Element<T> >* row = rows[rowIndex - 1];
        int index = findIndex(columnIndex, row);
        T data;
        if (index == -1) {
            data = T();
        } else {
            data = row->remove(index).value;
        }

        return data;
    }

    void mask(const sparse_matrix<bool>& b, sparse_matrix<T>& c) {
        if (this->size()[0] != b.size()[0] || this->size()[1] != b.size()[1]) {
            std::ostringstream stream;
            stream << "sparse_matrix mask failed, matrices are not the same size";
            std::cout << stream.str() << std::endl;
            return;
            // throw std::out_of_range(stream.str());
        }

        c.setSize(this->size()[0], this->size()[1]);
        for (int currentRow = 1; currentRow <= size()[0]; currentRow++) {
            for (int currentColumn = 1; currentColumn <= size()[1]; currentColumn++) {
                if (b.item_at(currentRow, currentColumn) && item_at(currentRow, currentColumn) != T()) {
                    c.insert(currentRow, currentColumn, this->item_at(currentRow, currentColumn));
                }
            }
        }
    }

    const int* size() const {
        return internalSize;
    }

    void setSize(const int& numRows, const int& numColumns) {
        delete[] rows;
        rows = new linked_list<Element<T> >*[numRows];

        for (int index = 0; index < numRows; index++) {
            rows[index] = new linked_list<Element<T> >();
        }

        internalSize[0] = numRows;
        internalSize[1] = numColumns;
    }

    void empty() {
        for (int index = 0; index < size()[0]; index++) {
            rows[index]->empty();
        }
    }

    bool isEmpty() const {
        for (int rowIndex = 0; rowIndex < size()[0]; rowIndex++) {
            if (rows->item_at(rowIndex)->size()) {
                return false;
            }
        }

        return true;
    }

    void print() {
        std::cout << "rows = " << size()[0] << " columns = " << size()[1] << std::endl;
        for (int rowIndex = 0; rowIndex < size()[0]; rowIndex++) {
            int consumedColumns = 0;
            std::cout << "row " << (rowIndex + 1) << "[";
            linked_list<Element<T> >* row = rows[rowIndex];
            for (int columnIndex = 1; columnIndex <= size()[1]; columnIndex++) {
                int index = findIndex(columnIndex, row);
                if (index != -1) {
                    std::cout << " col:" << row->item_at(index).index << " val= " << row->item_at(index).value;
                    consumedColumns++;
                    if (consumedColumns != row->size()) {
                        std::cout << ",";
                    }
                }

            }

            std::cout << "]" << std::endl;
        }

        // std::cout << std::endl;
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& os, const Element<T>& element) {
  os << element.index << " | " << element.value;
  return os;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, sparse_matrix<T>& list) {

    os << "[" << std::endl;
    for (int rowIndex = 1; rowIndex <= list.size()[0]; rowIndex++) {
        os << "    [";
        for (int columnIndex = 1; columnIndex <= list.size()[1]; columnIndex++) {
            os << list.item_at(rowIndex, columnIndex);
            if (columnIndex == list.size()[1]) {
                os << "]";

                if (rowIndex != list.size()[1]) {
                    os << ",";
                }

                os << std::endl;
            } else {
                os << ", ";
            }
        }
    }

    os << "]";

    return os;
}

#endif
