#include "dynamic-stack.h"
#include <string>
#include <iostream>
using namespace std;

const int DynamicStack::EMPTY_STACK = -99999;

DynamicStack::DynamicStack() {
    capacity_ = 16;
    init_capacity_ = 16;
    size_ = 0;
    items_ = new StackItem[init_capacity_]();
}

DynamicStack::DynamicStack(unsigned int capacity){
    capacity_ = capacity;
    init_capacity_ = capacity;
    size_ = 0;
    items_ = new StackItem[init_capacity_]();
}

DynamicStack::~DynamicStack() {
    delete[] items_;
    items_ = nullptr;
}

bool DynamicStack::empty() const {
    if(size_ == 0){
        return true;
    }
    return false;
}

int DynamicStack::size() const {
    return size_;
}

void DynamicStack::push(StackItem value) {
    if(size_ == capacity_){
        StackItem* temp_items_ = new StackItem[2*capacity_]();
        for (int i = 0; i<size_; i++){
            temp_items_[i] = items_[i];
        }
        items_ = temp_items_;
        capacity_*=2;
    }
    items_[size_] = value;
    size_++;
}

DynamicStack::StackItem DynamicStack::pop() {
    if(size_ == 0){
        return EMPTY_STACK;
    }
    else if(size_-1 <= capacity_/4 && capacity_/2 >= init_capacity_){
        StackItem* temp_items_ = new StackItem[capacity_/2]();
        for (int i = 0; i<size_; i++){
            temp_items_[i] = items_[i];
        }
        items_ = temp_items_;
        capacity_/=2;
    }
    items_[size_] = 0;
    size_--;
    int returnValue = items_[size_];
    return returnValue;
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (size_ == 0){
        return EMPTY_STACK;
    }
    return items_[size_-1];
}

void DynamicStack::print() const {
    for(int i = 0; i<size_; i++){
        cout << items_[i]<<" ";
    }
    cout<<endl;
}