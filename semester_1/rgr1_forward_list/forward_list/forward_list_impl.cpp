#include "forward_list_impl.h"

ForwardList::ForwardList() : front_(nullptr), size_(0) {}


ForwardList::ForwardList(const ForwardList& rhs) : front_(nullptr), size_(0) {

}

ForwardList::ForwardList(size_t count, int32_t value) : front_(nullptr), size_(0) {
    for (size_t i = 0; i < count; i++) {
        PushFront(value);
    }
}

ForwardList::ForwardList(std::initializer_list<int32_t> list):  front_(nullptr), size_(0) {

}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Clear();
    Node* cur = rhs.front_;
    Node* prev = nullptr;
    while(cur) {
        Node* new_node = new Node(cur->value_);
        if (front_) {
            prev->next_ = new_node;
        }
        else {
            front_ = new_node;
        }
        cur = cur->next_;
        prev = new_node;
        ++size_;
    }
    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

void ForwardList::PushFront(int32_t value) {
    Node* new_node = new Node(value);
    new_node->next_ = front_;
    front_ = new_node;
    size_++;
}


void ForwardList::PopFront() {
    if (front_ == nullptr) {
        throw "List is empty";
    }
    Node* new_front = front_->next_;
    delete front_;
    front_ = new_front;
    size_--;
}

void ForwardList::Remove(int32_t value) {
    while (front_ && front_->value_ == value) {
        PopFront();
    }
    if (!front_) {
        return;
    }
    Node* prev = front_;
    Node* cur = prev->next_;
    while (cur) {
        if (cur->value_ == value) {
            --size_;
            prev->next_ = cur->next_;
            delete cur;
            cur = prev->next_; 
        }
        else {
            prev = cur;
            cur = cur->next_;
        }
    }
}


void ForwardList::Clear() {
    while(front_) {
        PopFront();
    }
}


bool ForwardList::FindByValue(int32_t value) {
    Node* cur = front_;
    while (cur) {
        if (cur->value_ == value) {
            return true;
        }
        cur = cur->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* cur = front_;
    while(cur) {
        if (cur == front_) {
            out << cur->value_;
        }
        else {
            out << " " << cur->value_;;
        }
        cur = cur->next_;
    }
}

int32_t ForwardList::Front() const {
    if (front_ == nullptr) {
        throw "List is empty";
    }
    return front_->value_;
}

size_t ForwardList::Size() const {
    return size_;
}