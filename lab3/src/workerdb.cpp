#include "workerdb.hpp"
#include <stdexcept>


// ========== WorkerData ==========
WorkerData::WorkerData() : name_(), age_(0) {}

WorkerData::WorkerData(const MyString& name, int age)
    : name_(name), age_(age) {}


// ========== Pair ==========
WorkerDb::Pair::Pair() : surname_(), data_() {}

WorkerDb::Pair::Pair(const MyString& surname, const WorkerData& data)
    : surname_(surname), data_(data) {}


// ========== WorkerDb ==========
WorkerDb::WorkerDb()
    : data_(new Pair[4]), size_(0), capacity_(4) {}

WorkerDb::~WorkerDb() {
    delete[] data_;
}

int WorkerDb::find_index_(const MyString& surname) const {
    for (int i = 0; i < size_; ++i) {
        if (data_[i].surname_ == surname) {
            return i;
        }
    }
    return -1;
}

WorkerData& WorkerDb::operator[](const MyString& surname) {
    int idx = find_index_(surname);
    if (idx != -1) {
        return data_[idx].data_;
    }

    if (size_ == capacity_) {
        int new_capacity = capacity_ * 2;
        Pair* new_data = new Pair[new_capacity];

        for (int i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    data_[size_] = Pair(surname, WorkerData());
    return data_[size_++].data_;
}

// const WorkerData* WorkerDb::find(const MyString& surname) const {
//     int idx = find_index_(surname);
//     if (idx != -1) {
//         return &(data_[idx].data_);
//     }
//     return nullptr;
// }

// ========== Iterator ==========
WorkerDb::Iterator WorkerDb::begin() const {
    return Iterator(data_);
}

WorkerDb::Iterator WorkerDb::end() const {
    return Iterator(data_ + size_);
}


// ========== External Functions ==========
void print_db(WorkerDb& db) {
    for (auto it = db.begin(); it != db.end(); ++it) {
        std::cout << it.key() << " -> Name: " << it->name_.get_data()
                  << ", Age: " << it->age_ << "\n";
    }
}

double get_avg_age(WorkerDb& db) {
    if (db.getSize() == 0)
        return 0; // Empty

    int total_age = 0;

    for (auto it = db.begin(); it != db.end(); ++it)
        total_age += it->age_;

    return static_cast<double>(total_age) / db.getSize();
}