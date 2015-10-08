#include <iostream>
#include "linked_list.cpp"
using namespace std;

int main() {

    linked_list<int> test;
    linked_list<int> test2;
    cout << test.isEmpty() << endl;

    cout << test << endl;
    test.insert(0, 1);
    test.insert(1, 2);
    test.insert(2, 3);
    test.insert(3, 4);
    test.insert(4, 5);
    test.insert(5, 6);  // Size = 6
    cout << test << endl;

    test.empty();
    cout << test << endl;

    test.insert(0, 1);
    test.insert(1, 2);
    test.insert(2, 3);
    test.insert(3, 4);
    test.insert(4, 5);
    test.insert(5, 6);  // Size = 6
    cout << test << endl;
    test.empty();



    test.insert(0, 5);
    cout << test << endl;
    test.insert(0, 0);
    // cout << test.item_at(0) << endl;
    cout << test << endl;
    test.insert(2, 15);
    cout << test << endl;
    test.insert(2, 10);
    cout << test << endl;
    test.remove(0);  // Remove head
    cout << test << endl;
    test.remove(1);  // Remove mid
    cout << test << endl;
    test.remove(1);  // Remove tail
    cout << test << endl;
    test.remove(0);
    cout << test << endl;

    test.insert(0, 1);
    test.insert(1, 2);
    test.insert(2, 3);
    test.insert(3, 4);
    test.insert(4, 5);
    cout << test << endl;
    test.empty();
    cout << test << endl;
    test.insert(0, 2);
    test.insert(1, 5);
    cout << test << endl;
    cout << test2 << endl;
    // test2 = linked_list<int>(test);
    test2 = test;
    cout << test << endl;
    cout << test2 << endl;
    test.empty();
    cout << test << endl;
    cout << test2 << endl;
}
