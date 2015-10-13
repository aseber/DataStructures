#include <iostream>
#include <string>
#include "sparse_matrix.inl"
using namespace std;

int main()
{
    sparse_matrix<int>* a = new sparse_matrix<int>(3, 3);
    sparse_matrix<bool>* b = new sparse_matrix<bool>(3, 3);
    sparse_matrix<int>* c = new sparse_matrix<int>();
    a->insert(1, 1, 1);
    a->insert(1, 2, 2);
    a->insert(1, 3, 3);
    a->insert(2, 1, 4);
    a->insert(2, 2, 5);
    a->insert(2, 3, 6);
    a->insert(3, 1, 7);
    a->insert(3, 2, 8);
    a->insert(3, 3, 9);
    cout << "a = " << *a << endl;
    b->insert(1, 1, true);
    b->insert(2, 2, true);
    b->insert(3, 3, true);
    cout << "b = " << *b << endl;
    cout << "c = " << *c << endl;
    a->mask(*b, *c);
    cout << "c = " << *c << endl;

    try {
        cout << "should not be able to insert at 0, 0. Testing" << endl;
        a->insert(0,0,10);
    } catch (out_of_range& oor) {
        cout << oor.what() << endl;
    }

    try {
        cout << "should not be able to insert at 4, 4. Testing" << endl;
        a->insert(4,4,10);
    } catch (out_of_range& oor) {
        cout << oor.what() << endl;
    }

    cout << "Emptied B and C" << endl;
    b->empty();
    c->empty();
    cout << "a = " << *a << endl;
    cout << "b = " << *b << endl;
    cout << "c = " << *c << endl;
    a->mask(*b, *c);
    cout << "Mask B on C, C should be empty still" << endl;
    cout << "c = " << *c << endl;

    cout << "Filling B" << endl;
    b->insert(1, 1, 1);
    b->insert(1, 2, 1);
    b->insert(1, 3, 1);
    b->insert(2, 1, 1);
    b->insert(2, 2, 1);
    b->insert(2, 3, 1);
    b->insert(3, 1, 1);
    b->insert(3, 2, 1);
    b->insert(3, 3, 1);

    cout << "a = " << *a << endl;
    cout << "b = " << *b << endl;
    cout << "c = " << *c << endl;
    a->mask(*b, *c);
    cout << "C should be full because B is" << endl;
    cout << "c = " << *c << endl;

/*    a->read();
// cout << “Matrix A:” << endl;
    a->print();
    cout << "Reading Matrix B" << endl;
    b->read();
// cout << “Matrix B, the boolean mask matrix:” << endl;
    b->print();
// Masking
    a->mask(*b,*c);
// cout << “Matrix C, result:” << endl;
    c->print();*/

    delete a;
    delete b;
    delete c;

    return 0;
}
