#include <iostream>
#include "../includes/marked_bst.h"
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;

vector<int> make_sequence(int power);
int process1(int power);
int process2(int power);
int process3(int power);

int main() {
    srand(time(NULL));
    cout << process1(12) << endl;
}

vector<int> make_sequence(int power) {
    int N = pow(2, power) - 1;
    vector<int> v(N, 0);
    for (int i = 0; i < N; i++) {
        v[i] = i + 1;
    }
    return v;
}

// Performs process 1 on a standard balanced tree 
// of size pow(2, power) ten times, and then returns 
// the average number of sends.
int process1(int power) {
    marked_bst mbst(power);
    vector<int> keys = make_sequence(power);
    int N = pow(2, power) - 1;
    int num_accesses = 0;
    int access;
    for (int i = 0; i < 10; i++) {
        while (mbst.num_marked() != mbst.size()) {
            access = rand() % N;
            mbst.find(keys[access]);
            num_accesses++;
            if (num_accesses % 10000 == 0) {
                cout << "10000" << endl;
            }
        }
        mbst.unmark();
        cout << "unmarking" << endl;
    }
    return num_accesses / 10;
}

int process2(int power) {
    marked_bst mbst(power);
    int num_accesses = 0;
    for (int i = 0; i < 1; i++) {
        while (mbst.num_marked() != mbst.size()) {
            // generate access
            // perform access
            num_accesses++;
        }
    }
    return num_accesses / 1;
}

int process3(int power) {
    marked_bst mbst(power);
    int num_accesses = 0;
    for (int i = 0; i < 10; i++) {
        while (mbst.num_marked() != mbst.size()) {
            // generate access
            // perform access
            num_accesses++;
        }
    }
    return num_accesses / 10;
}
