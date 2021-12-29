#include "binary-search-tree.h"
#include <iostream>

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    int left = 0, right = 0;
    if(n == nullptr)
        return 0;
    left = getNodeDepth(n->left);
    right = getNodeDepth(n->right);
    if(left > right)
        return left + 1;
    else
        return right + 1;
}

BinarySearchTree::BinarySearchTree()
{
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const
{
    Node* temp = root_;
    while(temp->right != nullptr){
        temp = temp->right;
    }
    return temp->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const
{
    Node* temp = root_;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    return temp->val;
}

unsigned int BinarySearchTree::depth() const
{
    if (size_ == 0) {
    return -1;
    }
    else{
        return getNodeDepth(root_)-1;
    }
}

void BinarySearchTree::print() const
{
}

bool BinarySearchTree::exists(DataType val) const
{
    Node* temp = root_;
    while(temp != nullptr){
        if(val == temp->val){
            return true;
        }
        else{
            if(val < temp->val){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    if(root_ == nullptr){
        root_ = new Node(val);
        size_++;
        return true;
    }
    else{
        Node* insertNode = new Node(val);
        Node* temp = root_;
        Node* prev = root_;
        while(temp != nullptr){
            if(val == temp->val){
                return false;
            }
            else{
                prev = temp;
                if(val < temp->val){
                    temp = temp->left;
                }
                else{
                    temp = temp->right;
                }
            }
        }
        if(val <= prev->val){
            prev->left = insertNode;
        }
        else{
            prev->right = insertNode;
        }
        size_++;
        return true;
    }
}


bool BinarySearchTree::remove(DataType val)
{
    if(root_ == nullptr){
        return false;
    }
    else if(size_ == 1){
        if (root_->val == val){
            delete root_;
            root_ = nullptr;
            size_--;
            return true;
        }
        else{
            return false;
        }
    }
    else{
        Node* temp = root_;
        Node* prev = root_;
        bool wentLeft = true;

        while(temp != nullptr){
            if(val == temp->val){
                if(temp->left == nullptr && temp->right == nullptr){
                    if (wentLeft){
                        delete prev->left;
                        prev->left = nullptr;
                    }
                    else{
                        delete prev->right;
                        prev->right = nullptr;
                    }
                    size_--;
                }
                else if(temp->left == nullptr || temp->right == nullptr){
                    if (val == root_->val) {
                        if (temp->left != nullptr) {
                            root_ = temp->left;
                        }
                        else {
                            root_ = temp->right;
                        }
                    }
                    else{
                        if (wentLeft){
                            if (temp->left != nullptr){
                                prev->left = temp->left;
                            }
                            else{
                                prev->left = temp->right;
                            }
                        }
                        else{
                            if (temp->left != nullptr){
                                prev->right = temp->left;
                            }
                            else{
                                prev->right = temp->right;
                            }
                        }
                        delete temp;
                        temp = nullptr;
                        size_--;
                    }
                }
                else{
                    Node* moveHere = temp;
                    temp = temp->left;
                    while (temp->right != nullptr){
                        temp = temp->right;
                    }
                    remove(temp->val);
                    moveHere->val = temp->val;
                }
                return true;
            }
            else{
                prev = temp;
                if(val < temp->val){
                    temp = temp->left;
                    wentLeft = true;
                }
                else{
                    temp = temp->right;
                    wentLeft = false;
                }
            }
        }
        return false;
    }
}