#include <iostream>
#include "circular_linked_list.cpp"
using namespace std;


int main() {
    circular_linked_list<int> test;

    cout << test << endl;
    test.insert(0, 1);
    test.insert(1, 2);
    test.insert(2, 3);
    test.insert(3, 4);
    test.insert(4, 5);
    test.insert(5, 6);  // Size = 6
    cout << test << endl;

    test.clear();
    cout << test << endl;

    test.insert(0, 1);
    test.insert(1, 2);
    test.insert(2, 3);
    test.insert(3, 4);
    test.insert(4, 5);
    test.insert(5, 6);  // Size = 6
    cout << test << endl;
    test.clear();



    test.insert(0, 5);
    test.insert(1, 15);
    cout << test.at(0) << endl;
    test.insert(1, 10);
    test.insert(0, 0);
    cout << test << endl;
    test.remove(0); // Remove head
    cout << test << endl;
    test.remove(1); // Remove mid
    cout << test << endl;
    test.remove(1); // Remove tail
    cout << test << endl;
    test.remove(0);
    cout << test << endl;

    test.insert(0, 1);
    test.insert(1, 2);
    test.insert(2, 3);
    test.insert(3, 4);
    test.insert(4, 5);
    cout << test << endl;
    circular_linked_list<int>::iterator it = test.getIterator(test.begin());
    for (; !it.endPassed();) {
        it.remove();
    }
    cout << test << endl;

}