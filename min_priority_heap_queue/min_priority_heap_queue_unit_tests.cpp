#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include "min_priority_heap_queue.h"
using namespace std;

int main() {

    min_priority_heap_queue<int> min_heap = min_priority_heap_queue<int>(10);
    // cout << min_heap.isEmpty() << endl;
    min_heap.push(8);
    cout << min_heap.top() << endl;
    min_heap.push(7);
    cout << min_heap.top() << endl;
    min_heap.push(6);
    cout << min_heap.top() << endl;
    min_heap.push(5);
    cout << min_heap.top() << endl;
    min_heap.push(4);
    cout << min_heap.top() << endl;
    min_heap.push(3);
    cout << min_heap.top() << endl;
    min_heap.push(2);
    cout << min_heap.top() << endl;
    min_heap.push(1);
    cout << min_heap.top() << endl;
    // cout << min_heap.size() << endl;
    cout << min_heap.pop() << endl;
    cout << min_heap.top() << endl << endl;
    cout << min_heap.pop() << endl;
    cout << min_heap.top() << endl << endl;
    cout << min_heap.pop() << endl;
    cout << min_heap.top() << endl << endl;
    cout << min_heap.pop() << endl;
    cout << min_heap.top() << endl << endl;
    cout << min_heap.pop() << endl;
    cout << min_heap.top() << endl << endl;
    cout << min_heap.pop() << endl;
    cout << min_heap.top() << endl << endl;
    cout << min_heap.pop() << endl;
    cout << min_heap.top() << endl << endl;
    cout << min_heap.pop() << endl;
    // cout << min_heap.top() << endl << endl;
    cout << min_heap.size() << endl;

    return 0;
}