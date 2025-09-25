#pragma once

#include "Node.hpp"
#include <iostream>

class List {
/*
+ List ← dynamic memory usage; elements in dynamic memory, and we have their ptrs.
| + Node
| | + Circle
| | | + Point
*/
private:
    Node* Head_;
    Node* Tail_;
    size_t m_size_;

public:
    class Iterator {
    private:
        Node* ptr_;

    public:
        explicit Iterator(Node* node) : ptr_(node) {}

        const Circle& operator*() const { return ptr_->getData(); }
        const Circle* operator->() const { return &(ptr_->getData()); }

        Iterator& operator++() {
            ptr_ = ptr_->getNext();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    
        friend std::ostream& operator<<(std::ostream& os, const List::Iterator& iterator);
    };

    List();
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    void addFront(const Circle& circle);
    void addBack(const Circle& circle);
    bool remove(const Circle& circle);
    int removeAll(const Circle& circle);
    void clear();
    size_t size() const;

    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);

    Iterator begin() const { return Iterator(Head_->getNext()); }
    Iterator end() const { return Iterator(Tail_); }

    void sortByArea();
    Circle get(int index) const;

    friend std::ostream& operator<<(std::ostream& os, const List& list);
};