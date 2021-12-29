#include "sequential-list.h"
#include <iostream>

//constructor for the sequential list
SequentialList::SequentialList(unsigned int cap)
{
    data_ = new SequentialList::DataType [cap]; //allocate memory
    capacity_ = cap;//set the capacity to the given cap
    size_ = 0;//start the size of the list at 0
}

//destructor for the sequential list
SequentialList::~SequentialList()
{
    //deallocate the memory
    delete []data_;
    data_ = nullptr;
}

unsigned int SequentialList::size() const
{
    //return the size fo the list
    return size_;
}

unsigned int SequentialList::capacity() const
{
    //return the capacity of the list
    return capacity_;
}

bool SequentialList::empty() const
{
    //check if the list is empty by checking if the size is 0
    if (size_ == 0){
        return true;
    }
    else{
        return false;
    }
}

bool SequentialList::full() const
{
    //check if the list is full by checking if the size is equal to the capacity
    if (size_ == capacity_){
        return true;
    }
    else{
        return false;
    }
}

//find the value at a given index of the list
SequentialList::DataType SequentialList::select(unsigned int index) const
{
    //special case if the list is empty
    if (size_ == 0){
        return data_[0];
    }
    //if the index is invalid, return the last value in the list
    else if (index >= size_ || index < 0){
        return data_[size_-1];
    }
    //if the index is valid, return the value at the given index
    else{
        return data_[index];
    }
}

//find the index first occurrence of a given value
unsigned int SequentialList::search(DataType val) const
{
    //use a loop with the range of the size of the list to check every node in the list
    //at each iteration, check if the value is equal to the given value
    //if it is, return that index
    //if it escapes the loop, the value didn't occur, so return the size of the list
    for (int i = 0; i<size_; i++){
        if (data_[i] == val) {
            return i;
        }
    }
    return size_;
}
//format the output of the list
void SequentialList::print() const
{
    //iterate in the range of the capacity as to create one output per space in teh list
    for (int i = 0; i<capacity_; i++){
        if(i<size_){
            std::cout<<data_[i]<<" ";//output the value if there's a non-null value
        }
        else{
            std::cout<<"#"<<" ";//output # for null values
        }

    }
    std::cout << std::endl;

}

//method to insert a value into the list
bool SequentialList::insert(DataType val, unsigned int index)
{
    //special case for an empty list
    if(SequentialList::empty()){
        if (index == 0){
            data_[0] = val;
            return true;
        }
        else{
            return false;
        }
    }
    //check for invalid index values
    else if (index < 0){
        return false;
    }
    else if (index >= size_){
        return false;
    }
    //don't insert a value if the list is already full
    else if(SequentialList::full()){
        return false;
    }
    //general case
    else{
        size_++;//increase the size by one as you are inserting an element into the list
        //make two temps to shift the elements beside the inserted element
        DataType temp_1 = data_[index];
        DataType temp_2 = data_[index+1];
        data_[index] = val;//insert the element at the correct index
        for (int i = 0; i<size_; i++) {
            //after you reach the inserted element, push the elements in the list forward
            if (i>index){
                data_[i] = temp_1;
                temp_1 = temp_2;
                temp_2 = data_[i+1];
            }
        }
        return true;
    }
}

//special case to insert elements in the front of the list
bool SequentialList::insert_front(DataType val)
{
    //same logic as the general method, but the new element is always inserted at the zero-index position
    if(SequentialList::full()){
        return false;
    }
    else{
        size_++;
        DataType temp_1 = data_[0];
        DataType temp_2 = data_[1];
        data_[0] = val;
        for (int i = 1; i<size_; i++) {
            data_[i] = temp_1;
            temp_1 = temp_2;
            temp_2 = data_[i+1];
        }
        return true;
    }
}

//special case to insert an element to the back of the list
bool SequentialList::insert_back(DataType val)
{
    //same logic as the general method, but the new element is always inserted after the last pre-existing element in the list
    if(SequentialList::full()){
        return false;
    }
    else{
        data_[size_] = val;
        size_++;
        return true;
    }
}

//method to remove an element from the list
bool SequentialList::remove(unsigned int index)
{
    //check validity of the given index
    if (index >= size_){
        return false;
    }
    else if (index < 0){
        return false;
    }
    else{
        data_[index] = NULL; //remove the element at the given index
        //use a for loop to shift all of the following elements backwards in the list
        for (int i = index; i < size_; i++) {
            if (i == capacity_-1){
                break;
            }
            data_[i] = data_[i+1];
        }
        size_--;//decrease the size by one as you removed an element from the list
        return true;
    }
}

//special case to remove the first element in the list
bool SequentialList::remove_front()
{
    //same logic as the general method, but the new element is always removed from the zero-index position
    if (size_==0){
        return false;
    }
    else{
        data_[0] = NULL;
        for (int i = 0; i < size_; i++) {
            if (i == capacity_-1){
                break;
            }
            data_[i] = data_[i+1];
        }
    }
    size_--;
    return true;
}

//special case to remove the last element in the list
bool SequentialList::remove_back()
{
    //same logic as the general method, but the new element is always removed from the last defined position in the list
    if (size_==0){
        return false;
    }
    else{
        data_[size_-1] = NULL;
        size_--;
        return true;
    }
}

//method to replace a value in the list with a given value
bool SequentialList::replace(unsigned int index, DataType val)
{
    //check validity of the given index
    if (index >= size_){
        return false;
    }
    else if (index < 0){
        return false;
    }
    //if the index is valid, set the value of the list at the given index to the given value
    else{
        data_[index] = val;
        return true;
    }
}

