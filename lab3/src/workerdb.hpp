#pragma once

#include "mystring.hpp"


struct WorkerData {
    MyString name_;
    int age_;

    WorkerData();
    WorkerData(const MyString& name, int age);
};


class WorkerDb {
/*
+ WorkerDb
| + Pair
| | + WorkerData
| | | + MyString ← dynamic memory usage
| + Iterator
*/
private:
    struct Pair {
        MyString surname_;
        WorkerData data_;

        Pair();
        Pair(const MyString& surname, const WorkerData& data);
    };

    Pair* data_;
    int size_;
    int capacity_;

    int find_index_(const MyString& surname) const;

public:
    class Iterator {
    private:
        Pair* ptr_;

    public:
        Iterator(Pair* ptr) : ptr_(ptr) {}

        WorkerData& operator*() const { return ptr_->data_; }
        WorkerData* operator->() const { return &ptr_->data_; }

        MyString key() const { return ptr_->surname_; }

        Iterator& operator++() { ++ptr_; return *this; }
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    WorkerDb();
    ~WorkerDb(); // WorkerDb → Pair → WorkerData → MyString ← dynamic memory

    WorkerData& operator[](const MyString& surname);
    size_t getSize() { return size_; };

    Iterator begin() const;
    Iterator end() const;
};


void print_db(WorkerDb& db);
double get_avg_age(WorkerDb& db);