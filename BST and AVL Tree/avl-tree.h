#ifndef SYDE223_A3_AVL_TREE_H
#define SYDE223_A3_AVL_TREE_H

#include "binary-search-tree.h"
#include <string>
using namespace std;

class AVLTree: public BinarySearchTree
{
public:
    int depth(Node* n) const;
    bool insert(DataType val);
    bool remove(DataType val);
};
#endif //SYDE223_A3_AVL_TREE_H
