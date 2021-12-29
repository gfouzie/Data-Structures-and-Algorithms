#include "avl-tree.h"
#include <iostream>
using namespace std;

//declaring the global functions
void SingleRightRotation (BinarySearchTree::Node **root, BinarySearchTree::Node *alpha);
void SingleLeftRotation (BinarySearchTree::Node **root, BinarySearchTree::Node *alpha);
void LeftRightRotation (BinarySearchTree::Node **root, BinarySearchTree::Node *alpha);
void RightLeftRotation (BinarySearchTree::Node **root, BinarySearchTree::Node *alpha);

int AVLTree::depth(Node* n) const
{
    int left = 0, right = 0;
    if(n == nullptr)
        return 0;
    left = depth(n->left);
    right = depth(n->right);
    if(left > right)
        return left + 1;
    else
        return right + 1;
}

void SingleRightRotation (BinarySearchTree::Node **root, BinarySearchTree::Node *alpha){
    BinarySearchTree::Node  *A = alpha->left;
    alpha->left = A->right;
    A->right = alpha;

    if (*root == alpha) {
        *root = A;
    }
    else {
        BinarySearchTree::Node  *temp = *root;
        BinarySearchTree::Node  **parentPointerToAlpha = NULL;
        while (temp->val != alpha->val){
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        *parentPointerToAlpha = A;
    }
}


void SingleLeftRotation (BinarySearchTree::Node  **root, BinarySearchTree::Node  *alpha){
    BinarySearchTree::Node *A = alpha->right;
    alpha->right = A->left;
    A->left = alpha;

    if (*root == alpha) {
        *root = A;
    }
    else {
        BinarySearchTree::Node  *temp = *root;
        BinarySearchTree::Node  **parentPointerToAlpha = NULL;
        while (temp->val != alpha->val){
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        *parentPointerToAlpha = A;
    }
}

void LeftRightRotation (BinarySearchTree::Node  **root, BinarySearchTree::Node  *alpha){
    BinarySearchTree::Node  *A = alpha->left;
    SingleLeftRotation(root, A);
    SingleRightRotation(root, alpha);
}

void RightLeftRotation (BinarySearchTree::Node  **root, BinarySearchTree::Node  *alpha){
    BinarySearchTree::Node  *A = alpha->right;
    SingleRightRotation(root, A);
    SingleLeftRotation(root, alpha);
}

bool AVLTree::insert(DataType val){
    bool result = BinarySearchTree::insert(val);

    if(result == false){
        return false;
    }
    BinarySearchTree::Node **rootAddress;
    rootAddress = BinarySearchTree::getRootNodeAddress();
    Node* root = *rootAddress;

    if(root->val == val){
        return true;
    }

    BinarySearchTree::Node *temp;
    temp = root;
    BinarySearchTree::Node *temp_parent;
    BinarySearchTree::Node *alpha = nullptr;

    while (temp->val != val){
        temp_parent = temp;

        if(val > temp->val){
            temp = temp->right;
        }
        else if(val < temp->val){
            temp =  temp->left;
        }

        int leftHeight = depth(temp_parent->left);
        int rightHeight = depth(temp_parent->right);

        if(abs(leftHeight - rightHeight)>= 2 ){
            alpha = temp_parent;
        }
    }

    if(alpha == nullptr){
        return true;
    }

    if(val < alpha->val && val < alpha->left->val){
        SingleRightRotation (rootAddress, alpha);
    }
    else if(val > alpha->val && val > alpha->right->val){
        SingleLeftRotation(rootAddress, alpha);
    }
    else if(val < alpha->val && val > alpha->left->val){
        LeftRightRotation(rootAddress, alpha);
    }
    else if(val > alpha->val && val < alpha->right->val){
        RightLeftRotation(rootAddress, alpha);
    }
    return true;
}

bool AVLTree::remove(DataType val){

    BinarySearchTree::Node **rootAddress;
    rootAddress = BinarySearchTree::getRootNodeAddress();
    Node* root = *rootAddress;

    if(root->val == val){
        return true;
    }

    BinarySearchTree::Node *temp;
    temp = root;
    BinarySearchTree::Node *temp_parent;
    BinarySearchTree::Node *alpha = nullptr;


    bool result = BinarySearchTree::remove(val);
    if(result == false){
        return false;
    }


    while (temp!= nullptr){
        temp_parent = temp;
        if(val > temp->val){
            temp = temp->right;
        }
        else if (val < temp->val){
            temp =  temp->left;
        }

        int leftHeight = depth(temp_parent->left);
        int rightHeight = depth(temp_parent->right);

        if(abs(leftHeight - rightHeight)>= 2 ){
            alpha = temp_parent;
        }
    }

    if(alpha == nullptr){
        return true;
    }

    Node * alphaLeft = alpha->left;
    Node * alphaRight = alpha->right;

    if(val > alpha->val && depth(alphaLeft->left) - depth(alphaLeft->right) >= 0){
        SingleRightRotation (rootAddress, alpha);
    }
    else if(val < alpha->val && depth(alphaRight->left) - depth(alphaRight->right) <= 0){
        SingleLeftRotation(rootAddress, alpha);
    }
    else if(val > alpha->val && depth(alphaLeft->left) - depth(alphaLeft->right) < 0){
        LeftRightRotation(rootAddress, alpha);
    }
    else if(val < alpha->val && depth(alphaRight->left) - depth(alphaRight->right) > 0){
        RightLeftRotation(rootAddress, alpha);
    }
    return true;
}
