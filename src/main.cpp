#include <iostream>
#include "binary_search_tree.h"

using namespace std;

int main(int argc, char* argv[]) {

    BST<std::string> bst;

    bst.insert("c");
    bst.insert("a");
    bst.insert("b");
    bst.insert("d");
    bst.insert("e");
    bst.insert("ab");

    cout << "original tree: " << endl;

    cout << bst << endl;

    bst.remove("b");

    cout << "after removing b" << endl;

    cout << bst << endl;

    bst.insert("z");
    bst.insert("*");

    cout << "adding z and *" << endl;

    cout << bst << endl;

    return 0;
}
