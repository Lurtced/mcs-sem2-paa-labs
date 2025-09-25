#pragma once

#include <cstddef>
#include <cstdio>


class IFile {
public:
    virtual bool can_read() = 0;
    virtual bool can_write() = 0;
    virtual size_t read(void* buf, size_t max_bytes) = 0;
    virtual size_t write(const void* buf, size_t n_bytes) = 0;

    virtual ~IFile() {}
};


class BaseFile : public IFile {
protected:
    FILE* file_;
private:
    const char* mode_;

public:
    BaseFile();
    BaseFile(const char* path, const char* mode);
    BaseFile(FILE* existingFile, const char* mode);
    ~BaseFile() override;

    BaseFile(const BaseFile&) = delete;
    BaseFile& operator=(const BaseFile&) = delete;

    BaseFile(BaseFile&& other) noexcept;
    BaseFile& operator=(BaseFile&& other) noexcept;

    // IFile methods
    bool can_read() override;
    bool can_write() override;
    size_t read(void* buf, size_t max_bytes) override;
    size_t write(const void* buf, size_t n_bytes) override;

    // Other methods
    bool is_open();
    size_t read_raw(void* buf, size_t max_bytes);
    size_t write_raw(const void* buf, size_t n_bytes);
    long tell();
    bool seek(long offset);
};