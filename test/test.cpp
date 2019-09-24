#include <iostream>
#include "../includes/marked_bst.h"

using namespace std;

bool insert_test();
bool marking_test();

int main() {
    cout << "INSERT TEST:" << endl;
    if (insert_test()) {
        cout << "    INSERT TEST PASSED" << endl;
    }
    else {
        cout << "    INSERT TEST FAILED" << endl;
    }

    cout << "MARKING_TEST:" << endl;
    if (marking_test()) {
        cout << "    INSERT TEST PASSED" << endl;
    }
    else {
        cout << "    INSERT TEST FAILED" << endl;
    }

}

// needs more but seems generally okay
bool insert_test() {
    bool result = true;
    marked_bst mbst(3);
    int key_list[7] = {4, 2, 6, 1, 3, 5, 7};
    vector<int> keys = mbst.breadth_first_keyset();
    for (int i = 0; i < 7; i++) {
        if (key_list[i] != keys[i]) {
            result = false;
        }
    }
    if (mbst.find(7) == false) {
        result = false;
    }
    if (mbst.size() != 7) {
        result = false;
    }
    return result;
}

// seems okay
// tests find/mark
// tests unmark
bool marking_test() {
    bool result = true;
    marked_bst mbst(3);
    mbst.find(4);
    mbst.find(5);
    mbst.find(1);
    if (mbst.num_marked() != 3) { // should be 3
        result = false;
    }
    mbst.find(3);
    if (mbst.num_marked() != 7) {
        result = false;
    }
    mbst.unmark();
    if (mbst.num_marked() != 0) {
        result = false;
    }
    return result;
}

