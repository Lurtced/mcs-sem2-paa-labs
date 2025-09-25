#pragma once
#include <cstdio>


class IFile {
public:
    virtual bool can_read() = 0;
    virtual bool can_write() = 0;
    virtual size_t read(void* buf, size_t max_bytes) = 0;
    virtual size_t write(const void* buf, size_t n_bytes) = 0;

    virtual ~IFile() { }; // It is important for safe delete via pointer
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


class Base32 : public BaseFile {
private:
    const char* table_; // cipher table
    const int tableSize_;

public:
    Base32();
    Base32(const char* path, const char* mode, const char* table, int tableSize);
    Base32(FILE* existingFile, const char* mode, const char* table, int tableSize);
    
    int encoded32_size(int raw_size);
    int decoded32_size(int encoded_size);
    int encode32(const void* raw_data, int raw_size, char* dst);
    int decode32(const char* encoded_data, int encoded_size, void* dst);
    void reverse_bytes(void* data, int size);
    size_t read(void* decodedBuffer, size_t size) override;
    size_t write(const void* decodedBufer, size_t decodedSize) override;
};
// TODOne☑: одинаковый интерфейс; 
// TODOne☑: чтобы работала так, что когда считывается по частям, всё работает ок

class RleFile : public BaseFile {
private:
    // Compressed data read from file
    unsigned char inputBuffer[512];
    size_t inputBufferSize; // How much compressed data actually stored
    size_t inputBufferPos;  

    // Decompressed data ready to return
    unsigned char outputBuffer[512];
    size_t outputBufferSize; // how much decompressed data actually stored
    size_t outputBufferPos;

public:
    RleFile();
    RleFile(const char* path, const char* mode);
    RleFile(FILE* existingFile, const char* mode);
    
    size_t read(void* result, size_t size) override;
    size_t write(const void* data, size_t dataSize) override;
};


int write_int(IFile &file, int n);


class Base32File2 : public IFile {
private:
    IFile& baseFile_; // Composition
    const char* table_;
    int tableSize_;

public:
    Base32File2(IFile* baseFile, const char* table, int tableSize);
    ~Base32File2() override;

    bool can_read() override;
    bool can_write() override;

    size_t read(void* buffer, size_t size) override;
    size_t write(const void* buffer, size_t size) override;

    // These methods we already have
    int encoded32_size(int raw_size);
    int decoded32_size(int encoded_size);
    int encode32(const void* raw_data, int raw_size, char* dst);
    int decode32(const char* encoded_data, int encoded_size, void* dst);
};


class RleFile2 : public IFile {
private:
    unsigned char inputBuffer_[512];
    size_t inputBufferSize_;
    size_t inputBufferPos_;

    unsigned char outputBuffer_[512];
    size_t outputBufferSize_;
    size_t outputBufferPos_;

    IFile& baseFile_;

public:
    RleFile2(IFile* baseFile);
    ~RleFile2() override;

    bool can_read() override;
    bool can_write() override;

    size_t read(void* buffer, size_t size) override;
    size_t write(const void* buffer, size_t size) override;
private:
// we already have them
    int encode_rle(const void* data, size_t size, void* dest);
    int decode_rle(const void* data, size_t size, void* dest);
// new for check
    bool feof() const;
};