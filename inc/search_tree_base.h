//
// Created by Kaitlyn Archambault on 2023-11-19.
//

#ifndef ASSIGNMENT_3_SEARCH_TREE_BASE_H
#define ASSIGNMENT_3_SEARCH_TREE_BASE_H

#include <iostream>

template<class T>
class SearchTreeBase {
public:
    virtual void insert(T data) = 0;
    virtual void remove(T data) = 0;
    virtual bool is_empty() = 0;
    virtual bool find(T data) = 0;
    virtual T find_closest_value(T data) = 0;
    virtual void print_tree(std::ostream& output, int indent) = 0;
    virtual void build_balanced(std::vector<T> sorted_list, int left_bound, int right_bound) = 0;
    virtual SearchTreeBase* clone() const = 0;
};

#endif //ASSIGNMENT_3_SEARCH_TREE_BASE_H
