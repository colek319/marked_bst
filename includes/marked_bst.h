#ifndef MARKED_BST_H
#define MARKED_BST_H

#include <vector>

struct Node {
    Node *l;
    Node *r;
    Node *p;
    int key;
    bool marked;
};

class marked_bst {
 private:
    Node *root;
    int _size;
    void remove_subtree(Node *subroot);
    Node *stdBalancedBST(int l, int r);

 public:
    marked_bst();
    marked_bst(int arr[], int size);
    marked_bst(int power);
    ~marked_bst();
    bool find(const int key);   // says whether value is in the tree
    bool insert(const int key); 
    std::vector<int> breadth_first_keyset();
    void mark(Node *markee);
    bool to_mark(Node *temp);
    bool pattern1(Node *temp);
    bool pattern2(Node *temp);
    bool pattern3(Node *temp);
    int size();
    int num_marked();
    void unmark();
};

#endif
