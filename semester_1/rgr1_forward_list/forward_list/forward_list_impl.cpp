#include "forward_list_impl.h"

ForwardList::ForwardList(): first_(nullptr), size_(0) {}


ForwardList::ForwardList(const ForwardList& rhs): first_(nullptr), size_(0){
    Node* current = rhs.first_;
    Node* previous = nullptr;

    while(current){
        Node* new_node = new Node(current->value_);
        if (first_ == nullptr){
            first_ = new_node;
        }
        else{
            previous->next_ = new_node;
        }
        previous = new_node;
        current = current->next_;
    }

    size_ = rhs.size_;
}

ForwardList::ForwardList(size_t count, int32_t value): first_(nullptr), size_(0) {
    for (size_t i = 0; i < count; ++i) {
        Node* new_node = new Node(value);

        new_node->next_ = first_;
        first_ = new_node;
        ++size_;
    }
}


ForwardList::ForwardList(std::initializer_list<int32_t> list): first_(nullptr), size_(list.size()){
    Node* current = nullptr;

    for (int32_t value: list){
        Node* new_node = new Node(value);
        if (first_ == nullptr){
            first_ = new_node;
        }
        else{
            current->next_ = new_node;
        }
        current = new_node;
    }
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this != &rhs) {
        ForwardList temporary(rhs);
        std::swap(temporary.first_, first_);
        std::swap(temporary.size_, size_);
    }
    return *this;
}

ForwardList::~ForwardList() {
    while(first_) {
        Node* new_first = first_->next_;
        delete first_;
        first_ = new_first;
        size_--;
    };
}

void ForwardList::PushFront(int32_t value) {
    Node* new_node = new Node(value);
    new_node->next_ = first_;
    first_ = new_node;
    size_++;
}


void ForwardList::PopFront() {
    if (first_ == nullptr) {
        throw "List is empty";
    }
    Node* new_first = first_->next_;
    delete first_;
    first_ = new_first;
    size_--;
}

void ForwardList::Remove(int32_t value) {

    while (first_->value_ == value) {
        Node* new_first = first_->next_;
        delete first_;
        first_ = new_first;
        size_--;
    }
    if (!first_) {
        return;
    }

    Node* prev = first_;
    Node* current = prev->next_;

    while (current) {
        if (current->value_ == value) {
            --size_;
            prev->next_ = current->next_;
            delete current;
            current = prev->next_; 
        }
        else {
            prev = current;
            current = current->next_;
        }
    }
}


void ForwardList::Clear() {

    while(first_) {
        Node* new_first = first_->next_;
        delete first_;
        first_ = new_first;
        size_--;
    }
}


bool ForwardList::FindByValue(int32_t value) {
    Node* current = first_;

    while (current) {
        if (current->value_ == value) {
            return true;
        }
        current = current->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = first_;

    while(current) {
        if (current == first_) {
            out << current->value_;
        }
        else {
            out << " " << current->value_;;
        }
        current = current->next_;
    }
}

int32_t ForwardList::Front(){
    if (first_ == nullptr) {
        throw "List is empty";
    }
    return first_->value_;
}

size_t ForwardList::Size(){
    return size_;
}