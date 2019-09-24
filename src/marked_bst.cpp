#include "../includes/marked_bst.h"
#include<iostream>
#include <queue>
#include <math.h>

using namespace std;

marked_bst::marked_bst() {
    root = nullptr;
    _size = 0;
}

marked_bst::marked_bst(int arr[], int size) {
    root = nullptr;
    _size = size;
    for (int i = 0; i < size; i++) {
        insert(arr[i]);
    }
}

marked_bst::marked_bst(int power) {
    root = nullptr;
    _size = pow(2, power) - 1;
    root = stdBalancedBST(1, _size);
}

marked_bst::~marked_bst() {
    remove_subtree(root);
}

// postcondition: (subroot is nullptr)
void marked_bst::remove_subtree(Node *subroot) {
    if (subroot->l != nullptr) {
        remove_subtree(subroot->l);
    }
    if (subroot->r != nullptr) {
        remove_subtree(subroot->r);
    }
    delete subroot;
    subroot = nullptr;
}

// add marking model logic
bool marked_bst::find(const int key) {
    Node *temp = root;
    while (temp != nullptr) {
        if (key < temp->key) {
            temp = temp->l;
        }
        else if (key > temp->key){
            temp = temp->r;
        }
        else {
            temp->marked = true;
            mark(temp);
            return true;
        }
    }
    return false;
}

bool marked_bst::insert(const int key) {
    Node *temp = root;
    Node *temps_parent = nullptr;
    bool temp_is_left_child = false;
    while (temp != nullptr) {
        temps_parent = temp;
        if (key < temp->key) {
            temp = temp->l;
            temp_is_left_child = true;
        }
        else if (key > temp->key){
            temp = temp->r;
            temp_is_left_child = false;
        }
        else {
            return false;
        }
    }
    if (temp != root) {
        Node *new_node = new Node{
                        nullptr,
                        nullptr,
                        temps_parent,
                        key, 
                        false};
        if (temp_is_left_child) {
           temps_parent->l = new_node;
        }
        else {
            temps_parent->r = new_node;
        }
    }
    else {
        Node *new_node = new Node{
                        nullptr,
                        nullptr,
                        nullptr,
                        key, 
                        false};
        root = new_node;
    }
    return true;
}

vector<int> marked_bst::breadth_first_keyset() {
    vector<int> v;
    queue<Node *> q;
    Node *temp = root;
    if (temp != nullptr) {
        q.push(temp);
    }
    while (not q.empty()) {
        temp = q.front();
        q.pop();
        v.push_back(temp->key);
        if (temp->l != nullptr) {
            q.push(temp->l);
        }
        if (temp->r != nullptr) {
            q.push(temp->r);
        }
    }
    return v;
}

void marked_bst::mark(Node *markee) {
    queue<Node *> q;
    q.push(markee);
    Node *temp = nullptr;
    while (not q.empty()) {
        temp = q.front();
        q.pop();
        temp->marked = true;
        // parent and sibling logic
        if (temp->p != nullptr) {
            if (to_mark(temp->p)) {
                q.push(temp->p);
            }
            if (temp->p->l != temp and temp->p->l != nullptr) {
                if (to_mark(temp->p->l)) {
                    q.push(temp->p->l);
                }
            }
            if (temp->p->r != temp and temp->p->r != nullptr) {
                if (to_mark(temp->p->r)) {
                    q.push(temp->p->r);
                }
            }
        }
        // children logic
        if (temp->l != nullptr and to_mark(temp->l)) {
            q.push(temp->l);
        }
        if (temp->r != nullptr and to_mark(temp->r)) {
            q.push(temp->r);
        }
    }
}

bool marked_bst::to_mark(Node *temp) {
    if ((pattern1(temp) or pattern2(temp) or pattern3(temp)) and 
         not temp->marked) {
        return true;
    }
    return false;
}


/*
 *  Parent and right sibling marked
 * 
 *          x
 *         / \
 *        o   x
 */
bool marked_bst::pattern1(Node *temp) {
    if (temp == root or temp->p->r == nullptr) {
        return false;
    }
    if (temp->p->marked and temp->p->r->marked) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * parent and left sibling marked
 * 
 *          x
 *         / \
 *        x   o
 */
bool marked_bst::pattern2(Node *temp) {
    if (temp == root or temp->p->l == nullptr) {
        return false;
    }
    if (temp->p->marked and temp->p->l->marked) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * both children are marked
 * 
 *          o
 *         / \
 *        x   x
 */
bool marked_bst::pattern3(Node *temp) {
    if (temp->l == nullptr or temp->r == nullptr) {
        return false;
    }
    if (temp->l->marked and temp->r->marked) {
        return true;
    }
    else {
        return false;
    }
}

int marked_bst::size() {
    return _size;
}

int marked_bst::num_marked() {
    queue<Node *> q;
    Node *temp = root;
    int count = 0;
    if (temp != nullptr) {
        q.push(temp);
    }
    while (not q.empty()) {
        temp = q.front();
        q.pop();
        if (temp->marked) {
            count++;
        }
        if (temp->l != nullptr) {
            q.push(temp->l);
        }
        if (temp->r != nullptr) {
            q.push(temp->r);
        }
    }
    return count;
}

Node *marked_bst::stdBalancedBST(int l, int r) {
    if (l > r) {
        return nullptr;
    }
    int median = (l + r)/2;
    Node *new_node = new Node{
                            nullptr,
                            nullptr,
                            nullptr,
                            median, 
                            false};

    new_node->l = stdBalancedBST(l, median - 1);
    if (new_node->l != nullptr) {
        new_node->l->p = new_node;
    }

    new_node->r = stdBalancedBST(median + 1, r);
    if (new_node->r != nullptr) {
        new_node->r->p = new_node;
    }
    return new_node;
}

// makes all nodes marked set to unmarked
void marked_bst::unmark() {
    queue<Node *> q;
    Node *temp = root;
    if (temp != nullptr) {
        q.push(temp);
    }
    while (not q.empty()) {
        temp = q.front();
        q.pop();
        temp->marked = false;
        if (temp->l != nullptr) {
            q.push(temp->l);
        }
        if (temp->r != nullptr) {
            q.push(temp->r);
        }
    }
}