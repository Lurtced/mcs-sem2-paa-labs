#include "basefile.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>


BaseFile::BaseFile() {
    file_ = nullptr;
    std::cout << "BaseFile default constructor called." << std::endl;
}

BaseFile::BaseFile(const char* path, const char* mode) {
    file_ = fopen(path, mode);
    mode_ = mode;
    std::cout << "BaseFile param constructor called." << std::endl;
}

BaseFile::BaseFile(FILE* existingFile, const char* mode) {
    file_ = existingFile;
    mode_ = mode;
    std::cout << "BaseFile FILE*-param constructor called." << std::endl;
}

BaseFile::~BaseFile() {
    if (file_ && is_open()) {
        fclose(file_);
    }
    std::cout << "BaseFile destructor called." << std::endl;
}

bool BaseFile::is_open() {
    return file_ != nullptr;
}

bool BaseFile::can_read() {
    if (!is_open()) return false;
    // "r", "r+", "w+", "a+" modes allow reading
    return strstr(mode_, "r") != nullptr || 
           strstr(mode_, "+") != nullptr;
}

bool BaseFile::can_write() {
    if (!is_open()) return false;
    // "w", "w+", "r+", "a", "a+" modes allow writing
    return strstr(mode_, "w") != nullptr ||
           strstr(mode_, "a") != nullptr ||
           strstr(mode_, "+") != nullptr;
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!file_) return 0;
    return fwrite(buf, 1, n_bytes, file_);
}

size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!is_open() || !can_read()) return 0;
    return fread(buf, 1, max_bytes, file_);
}

long BaseFile::tell() {
    if (!is_open()) return -1;
    return ftell(file_);
}

bool BaseFile::seek(long offset) {
    if (!is_open()) return 0;
    return fseek(file_, offset, SEEK_SET) == false;
}

size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes); // coming soon...
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes); // coming soon...
}


BaseFile::BaseFile(BaseFile&& other) noexcept
    : file_(other.file_), mode_(other.mode_) {
    std::cout << "BaseFile move constructor called." << std::endl;
    other.file_ = nullptr;
}


BaseFile& BaseFile::operator=(BaseFile&& other) noexcept {
    std::cout << "BaseFile move assignment operator called." << std::endl;
    if (this != &other) {
        if (file_ && is_open()) {
            fclose(file_);
        }
        file_ = other.file_;
        mode_ = other.mode_;
        other.file_ = nullptr;
    }
    return *this;
}