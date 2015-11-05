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

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include "min_priority_tree_queue.h"
using namespace std;

int main() {

    min_priority_tree_queue<int> min_tree = min_priority_tree_queue<int>();
    // cout << min_tree.size() << endl;
    // cout << min_tree.isEmpty() << endl;
    min_tree.push(8);
    cout << min_tree.top() << endl;
    min_tree.push(7);
    cout << min_tree.top() << endl;
    min_tree.push(6);
    cout << min_tree.top() << endl;
    min_tree.push(5);
    cout << min_tree.top() << endl;
    min_tree.push(4);
    cout << min_tree.top() << endl;
    min_tree.push(3);
    cout << min_tree.top() << endl;
    min_tree.push(2);
    cout << min_tree.top() << endl;
    min_tree.push(1);
    cout << min_tree.top() << endl;

    cout << "-----------------------------" << endl;

    cout << min_tree.pop() << endl;
    cout << min_tree.top() << endl << endl;
    cout << min_tree.pop() << endl;
    cout << min_tree.top() << endl << endl;
    cout << min_tree.pop() << endl;
    cout << min_tree.top() << endl << endl;
    cout << min_tree.pop() << endl;
    cout << min_tree.top() << endl << endl;
    cout << min_tree.pop() << endl;
    cout << min_tree.top() << endl << endl;
    cout << min_tree.pop() << endl;
    cout << min_tree.top() << endl << endl;
    cout << min_tree.pop() << endl;
    cout << min_tree.top() << endl << endl;
    cout << min_tree.pop() << endl;
    // cout << min_tree.top() << endl << endl;
    cout << min_tree.size() << endl;
    return 0;
}