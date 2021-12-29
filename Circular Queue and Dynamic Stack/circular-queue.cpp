#include "circular-queue.h"
#include <iostream>
using namespace std;

const int CircularQueue::EMPTY_QUEUE = -99999;

CircularQueue::CircularQueue() {
    capacity_ = 16;
    size_ = 0;
    items_ = new QueueItem[capacity_]();
    head_ = 0;
    tail_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {
    capacity_ = capacity;
    size_ = 0;
    items_ = new QueueItem[capacity_]();
    head_ = 0;
    tail_ = 0;
}

CircularQueue::~CircularQueue() {
    delete[] items_;
    items_ = nullptr;
}

bool CircularQueue::empty() const {
    if(size_ == 0){
        return true;
    }
    return false;
}

bool CircularQueue::full() const {
    if(size_ == capacity_){
        return true;
    }
    return false;
}

int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::enqueue(QueueItem value) {
    if(full()){
        return false;
    }
    else{
        items_[tail_] = value;
        if(tail_ == capacity_-1){
            tail_ = 0;
        }
        else{
            tail_++;
        }
        size_++;
        return true;
    }
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    if(empty()){
        return EMPTY_QUEUE;
    }
    else{
        QueueItem returnValue = items_[head_];
        items_[head_] = 0;
        if(head_ == capacity_-1){
            head_ = 0;
        }
        else{
            head_++;
        }
        size_--;
        return returnValue;
    }
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if (size_ == 0){
        return EMPTY_QUEUE;
    }
    return items_[head_];
}

void CircularQueue::print() const {
    for(int i = 0; i<size_; i++){
        cout << items_[i]<<" ";
    }
    cout<<endl;
}
