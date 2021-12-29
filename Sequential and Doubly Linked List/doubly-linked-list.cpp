#include "doubly-linked-list.h"
#include <iostream>
using namespasce std;

//define the doubly linked list with the given data
DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
}

//constructor
DoublyLinkedList::DoublyLinkedList()
{
    //start with nothing meaning that the head/tail are null and the size is 0
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

//destructor
DoublyLinkedList::~DoublyLinkedList()
{
    //run a while loop starting at the head that goes until there isn't a following node (the tail)
    while (head_ != nullptr){
        //make and delete a temp head that gets advanced to the next node with every iteration
        //do this to reallocate memory
        Node *temp = head_;
        head_ = head_ -> next;
        delete temp;
        temp = nullptr;
    }
}


unsigned int DoublyLinkedList::size() const
{
    //returns the variable that counts the size of the list
    //this value changes as there are nodes added and removed
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    //returns the static capacity of the list
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    //check if the list is empty by seeing of the size is 0
    if (size_ == 0){
        return true;
    }
    else{
        return false;
    }
}

bool DoublyLinkedList::full() const
{
    //check if the list is at capacity by checking if the size variable is equal to the capacity variable
    if (size_ == CAPACITY){
        return true;
    }
    else{
        return false;
    }
}

//find the value at a given index of the list
DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    //special case for empty list
    if (size_ == 0){
        return DataType(34);
    }
    //if the index is invalid, return the value of the tail node
    else if (index>=size_){
        return tail_->value;
    }
    //if the index is valid, return the value at that index
    else{
        return getNode(index)->value;
    }

}

//find the index first occurrence of a given value
unsigned int DoublyLinkedList::search(DataType value) const
{
    //use a loop with the range of the size of the list to check every node in the list
    //at each iteration, check if the value of the node is equal to the given value
    //if it is, return that index
    //if it escapes the loop, the value didn't occur, so return the size of the list
    Node *temp = head_;
    for (int i = 0; i < size_; i++){
        if (temp->value == value){
            return i;
        }
        temp=temp->next;
    }
    return size_;
}

//format the output of the list
void DoublyLinkedList::print() const
{
    //start printing at the head
    Node *temp = head_;
    //use a counter to check when the output loop is at the final node
    int counter = 0;

    //check if the list is empty
    if (head_ == nullptr){
        std::cout << "<empty>"<<std::endl;
        return;
    }
    while (temp != nullptr){
        //make the left side of head node point to null and the right side of the tail node point to null
        //otherwise, the values should point to the other nodes
        if (size_ == 1){
            std::cout << "null <-" << temp->value<<"-> null";
        }
        else if (counter == size_-1 ){
            std::cout << " <-" << temp->value<<"-> null";
        }
        else if (counter == 0){
            std::cout << "null <-" <<temp->value<<"->";
        }
        else{
            std::cout<< " <-" << temp->value<<"->";
        }
        temp = temp->next;
        counter++;
    }
    std::cout<<std::endl;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    //check if the index is invalid
    if(index > size_ || index < 0) {
        return NULL;
    }
    //for loop that iterates until it reaches the index
    //at the index, return the node
    else{
        Node *temp = head_;
        for (int i = 0; i < index; i++){
            temp=temp->next;
        }
        return temp;
    }
}

//method to insert a node into the list
bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    //check if there's space in the list for another node
    if (size_<CAPACITY){
        //check validity of inputs
        if(index > size_ || index < 0) {
            return false;
        }
        else{
            Node *newNode = new Node(value);
            if(index == 0) {
                //empty list
                if (size_ == 0) {
                    tail_ = newNode;
                }
                //insert new head
                else{
                    newNode->next = head_;
                    head_->prev = newNode;
                }
                newNode->value = value;
                head_ = newNode;
            }
            else{
                //new tail
                if (index == size_ && size_ > 0){
                    tail_->next = newNode;
                    newNode->prev = tail_;
                    tail_ = newNode;
                    newNode->value = value;
                }
                //general case
                else if (index > 0 && index < size_){
                    Node *temp = getNode(index); //use the helper method to get the node
                    newNode->value = value; //assign the value to the node
                    newNode->next = temp; //make the inserted node point to the node that was at the given index
                    newNode->prev = temp->prev;//make the inserted node point backwards to the node that the former index node points to
                    newNode->prev->next = newNode;//make that node point forward to the inserted node
                    temp->prev = newNode;//make the node that was at the given index point backwards to the inserted node
                }

            }
            //increase size since you just added a new node
            size_++;
            return true;
        }
    }
    else{
        return false;
    }
}

//special insert method for a new head node
bool DoublyLinkedList::insert_front(DataType value)
{
    //same process as the 'new head node' special case in the insert method
    if (size_<CAPACITY){
        Node *newNode = new Node(value);
        if (size_ == 0) {
            tail_ = newNode;
        }
        else{
            newNode->next = head_;
            head_->prev = newNode;
        }
        newNode->value = value;
        head_ = newNode;
        size_++;
        return true;
    }
    else{
        return false;
    }

}

//special insert method for a new tail node
bool DoublyLinkedList::insert_back(DataType value)
{
    //same process as the 'new tail node' special case in the insert method
    if (size_<CAPACITY){
        Node *newNode = new Node(value);
        if (size_==0){
            head_ = newNode;
            tail_ = newNode;
        }
        else{
            tail_->next = newNode;
            newNode->prev = tail_;
            tail_ = newNode;
            newNode->value = value;
        }
        size_++;
        return true;
    }
    else{
        return false;
    }
}

//method to remove a node from the list
bool DoublyLinkedList::remove(unsigned int index) {
    //check validity
    if (index >= size_ || index < 0 || size_ < 1) {
        return false;
    }
    else {
        //removing the only node special case
        if(size_ == 1){
            Node *temp = head_;
            delete temp;
            temp = nullptr;
            head_ = nullptr;//point the tail and head to null
            tail_ = nullptr;
            size_--;
            return true;
        }
        else{
            //removing head node special case
            if(index == 0){
                Node *temp = head_;
                head_ = temp->next;
                delete temp;
                temp = nullptr;
            }
            //removing tail node special case
            else if(index == size_-1){
                    Node *temp = tail_;
                    tail_ = temp->prev;
                    tail_->next = nullptr;
                delete temp;
                temp = nullptr;
            }
            //general case
            else {
                Node *previous = head_;
                Node *current = head_->next;
                int i = 1;
                //iterate through until you get to the index node
                while (i < index) {
                    //safety net to catch if you are trying to interate past the tail node
                    if (current->next == nullptr) {
                        break;
                    }
                    previous = current;
                    current = current->next;
                    i++;
                }
                previous->next = current->next;//make the previous node point to node that the current node points to
                current->next->prev = current->prev;//make the node in front of the current node point back towards the node that the current node points to
                delete current;
                current = nullptr;//reallocate memory
            }
        }
        //decrease size because you just removed a node
        size_--;
        return true;
    }
}

//special case for removing the head node
bool DoublyLinkedList::remove_front()
{
    //same logic as the special case from the remove method
    if (size_ < 1){
        return false;
    }
    else if(size_ == 1){
        Node *temp = head_;
        delete temp;
        temp = nullptr;
        head_ = nullptr;
        tail_ = nullptr;
        size_--;
        return true;
    }
    else{
        Node *temp = head_;
        head_ = temp->next;
        head_->prev = nullptr;
        delete temp;
        temp = nullptr;
        size_--;
        return true;
    }
}

//special case for removing the tail node
bool DoublyLinkedList::remove_back()
{
    //same logic as the special case from the remove method
    if (size_<1){
        return false;
    }
    else if(size_ == 1){
        Node *temp = tail_;
        delete temp;
        temp = nullptr;
        head_ = nullptr;
        tail_ = nullptr;
        size_--;
        return true;
    }
    else{
        Node *temp = tail_;
        tail_ = temp->prev;
        tail_->next = nullptr;
        delete temp;
        temp = nullptr;
        size_--;
        return true;
    }
}

//method to replace the value of a node at a given index in the list
bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    //check validity
    if (index >= size_ || index < 0 || size_ < 1) {
        return false;
    }
    else{
        Node *temp = getNode(index);//use the helper method to get the node at the index
        temp->value = value;//set the value of that node to the given value
        return true;
    }
}

#include <iostream>
#include <algorithm>
using namespace std;


// Representation of node
struct Node {
    int data;
    Node* next;
};


// Function to generate the required
// linked list and return its head
Node* newList(Node* root1, Node* root2)
{
    Node *ptr1 = root1, *ptr2 = root2;
    Node* root = NULL;

    // While there are nodes left
    while (ptr1 != NULL) {

// write your lines of code below
// graders will manually grade this part
// you can have some flexibility regarding the format,
// as long as the code is correct.
// please add comments to explain your logic
// partial credits will be given
//////////////////////////////////////////////

        //check if its the first iteration to set the head node
        if (root == nullptr){
            //check which pointer contains the greater value
            //then starting at the root node, set that node in the list equal to the greater value
            //after setting that value, advance the root to the next value
            if (ptr1->data >= ptr2->data){
                root = ptr1;
            }
            else{
                root = ptr2;
            }
        }
        //otherwise connect the following list nodes (not as the head variable)
        else{
            //same comparison logic but use root->next because you want the nodes after the root
            if (ptr1->data >= ptr2->data){
                root->next = ptr1;
            }
            else{
                root->next = ptr2;
            }
            //if root->next was updated, advance root->next to the next node in the list
            //don't advance it if root==nullptr because we changed the head variable there, not head->next
            root->next = root->next->next;//can't change the root, so advance the list element after the root
        }

        //advance the lists to the next node in the list regardless of if the root was updated or the following nodes were updated
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;


//////////////////////////////////////////////

    } //end of while loop

    // Return the head of the
    // generated linked list
    return root;
}

int main(){
    DoublyLinkedList a;
    a.insert(2,0);
    a.insert(3,1);
    a.insert(400,2);

    DoublyLinkedList b;
    b.insert(10,0);
    b.insert(11,1);
    b.insert(40,2);
    cout<<newList(a, b);
}

