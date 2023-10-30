#include <iostream>
#include "binary_search_tree.h"

using namespace std;

int main(int argc, char* argv[]) {

    BST<int> bst;

    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);
    bst.insert(9);

    cout << bst << endl;

    return 0;
}
