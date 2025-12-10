#include "vector_impl.h"

Vector::Vector() {}

Vector::Vector(size_t size): size_(size), capacity_(size), array_(new int[size_]) {
    for (size_t i=0; i < size_; ++i){
        array_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<int> list): size_ (list.size()), capacity_ (list.size()), array_ (new int[size_]) {
    for (size_t i=0; i < size_; ++i){
        array_[i] = *(list.begin() + i);
    }
}

Vector::Vector(const Vector& other): size_(other.size_), capacity_(other.capacity_), array_(new int[size_]){
    std::copy(other.array_, other.array_ + size_, array_);
}

Vector& Vector::operator= (const Vector& other){
    if (this == &other)
        return *this;

    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] array_;
    array_ = new int[size_];
    std::copy(other.array_, other.array_ + size_, array_);
    return *this;
}

Vector::~Vector(){
    delete[] array_;
};

void Vector::Swap(Vector& other){
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(array_, other.array_);
}

int& Vector::operator[] (size_t index){
    return array_[index];
}

const int& Vector::operator[](size_t index) const {
    return array_[index];
}

int& Vector::At(size_t index){
    if (index >= size_)
        throw std::out_of_range("Ошибка! Выход за границу возможных индексов.");
    return array_[index];
}

const int& Vector::At(size_t index) const{
    if (index >= size_)
        throw std::out_of_range("Ошибка! Выход за границу возможных индексов.");
    return array_[index];
}

const int Vector::Size() const {
    return size_;
}

const int Vector::Capacity() const{
    return capacity_;
}

void Vector::PushBack(int number){
    if (capacity_ == size_){
        if (capacity_ == 0){
            ++capacity_;
        }
        else{
            capacity_  *= 2;
        }
        int* arr = new int[capacity_];
        std::copy(array_, array_ + size_, arr);
        delete[] array_;
        array_ = new int[capacity_];
        array_ = arr;
        delete[] arr;
    }
    array_[size_++] = number;
}

void Vector::PopBack(){
    if (size_ == 0){
        throw std::out_of_range("Ошибка! Невозможно удалить элемент из вектора с неположительным размером.");
    size_--;
    }
}

void Vector::Clear(){
    size_ = 0;
}

void Vector::Reserve(size_t new_capacity){
    if (capacity_ < new_capacity){
        int* arr = new int[new_capacity];
        std::copy(array_, array_ + size_, arr);
        delete[] array_;
        array_ = arr;
        delete[] arr;
        capacity_ = new_capacity;
    }
}

std::ostream& operator<< (std::ostream& os, const Vector& vector){
    os << "[";
    for (size_t i = 0; i < vector.size_; ++i){
        os << vector.array_[i];
        if (i + 1 < vector.size_){
            os << ",";
        }
    }
    os << "]";
    return os;
}