#include <iostream>
#include "binary_search_tree.h"
#include "dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {

    Dictionary bst("../docs/dictionary.txt");

    cout << bst << endl;

    bst.save_to_file("../balanced_tree.txt");

    return 0;
}
