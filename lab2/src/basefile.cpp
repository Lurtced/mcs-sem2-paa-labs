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


Base32::Base32()
    : BaseFile(), table_(nullptr), tableSize_(0) {
        std::cout << "Base32 default constructor called." << std::endl;
   }

Base32::Base32(const char* path, const char* mode, const char* table, int tableSize)
    : BaseFile(path, mode), table_(table), tableSize_(tableSize) {
        std::cout << "Base32 param constructor called." << std::endl;
}

Base32::Base32(FILE* existingFile, const char* mode, const char* table, int tableSize)
    : BaseFile(existingFile, mode), table_(table), tableSize_(tableSize) {
        std::cout << "Base32 FILE*-param constructor called." << std::endl;
}
    

int Base32::encoded32_size(int raw_size) {
    return (raw_size * 8 + 4) / 5;
}

int Base32::decoded32_size(int encoded_size) {
    return (encoded_size * 5) / 8;
}

int Base32::encode32(const void* raw_data, int raw_size, char* dst) {
    if (!raw_data || !dst || raw_size <= 0) return 1;

    const unsigned char *data = (const unsigned char *)raw_data;
    int bit_buffer = 0, bit_count = 0, dst_index = 0;

    for (int i = 0; i < raw_size; ++i) {
        bit_buffer = (bit_buffer << 8) | data[i];
        bit_count += 8;

        while (bit_count >= 5) {
            int index = (bit_buffer >> (bit_count - 5)) & 0x1F;
            dst[dst_index++] = table_[index];
            bit_count -= 5;
        }
    }

    if (bit_count > 0) {
        bit_buffer <<= (5 - bit_count);
        dst[dst_index++] = table_[bit_buffer & 0x1F];
    }

    dst[dst_index] = '\0';
    return 0;
}

int Base32::decode32(const char* encoded_data, int encoded_size, void* dst) {
    if (!encoded_data || !dst || encoded_size <= 0) return 1;

    unsigned char *data = (unsigned char *)dst;
    int bit_buffer = 0, bit_count = 0, raw_index = 0;

    for (int i = 0; i < encoded_size; ++i) {
        const char* ptr = strchr(table_, encoded_data[i]);
        if (!ptr) return 2;
        int value = ptr - table_;

        bit_buffer = (bit_buffer << 5) | value;
        bit_count += 5;

        while (bit_count >= 8) {
            data[raw_index++] = (bit_buffer >> (bit_count - 8)) & 0xFF;
            bit_count -= 8;
        }
    }

    return 0;
}

void Base32::reverse_bytes(void* data, int size) {
    unsigned char *ptr = (unsigned char *)data;
    for (int i = 0; i < size / 2; ++i) {
        unsigned char temp = ptr[i];
        ptr[i] = ptr[size - i - 1];
        ptr[size - i - 1] = temp;
    }
}

size_t Base32::read(void* decodedBuffer, size_t size) {
    /*
    It does:
    - read
    - decode
    result we will store in decodedBuffer (char[]) via void*.
    encoded info get from file.
    return: size of decoded data; -1 if fail
    */

    char encodedData[size*2]; // here we will store read encoded data

    size_t encodedSize = read_raw(encodedData, size);
    if (decode32(encodedData, encodedSize, decodedBuffer)) {
        printf("Error during decoding\n");
        return -1;
    }
    int decodedSize = decoded32_size(encodedSize);

    return decodedSize;
}

size_t Base32::write(const void* decodedBuffer, size_t decodedSize) {
    /*
    It does:
    - encode
    - write
    result is not stored anywhere: it's saved to a file.
    decoded info get via param.
    return: size of encoded data; -1 if fail
    */

    int encodedSize = encoded32_size(decodedSize);
    char encodedData[encodedSize];

    if (encode32(decodedBuffer, decodedSize, encodedData)) {
        printf("Error during encoding.");
        return -1;
    }
    
    write_raw(encodedData, encodedSize);
    return encodedSize;
}


// RleFile::RleFile() : BaseFile() {
//     std::cout << "RleFile default constructor called." << std::endl;
// }

// RleFile::RleFile(const char* path, const char* mode)
//     : BaseFile(path, mode) {
//         std::cout << "RleFile param constructor called." << std::endl;
// }

// RleFile::RleFile(FILE* existingFile, const char* mode)
//     : BaseFile(existingFile, mode) {
//         std::cout << "RleFile FILE*-param constructor called." << std::endl;
// }

RleFile::RleFile() : BaseFile(), inputBufferPos(0), inputBufferSize(0),
                     outputBufferPos(0), outputBufferSize(0) {}

RleFile::RleFile(const char* path, const char* mode)
    : BaseFile(path, mode), inputBufferPos(0), inputBufferSize(0),
      outputBufferPos(0), outputBufferSize(0) {}

RleFile::RleFile(FILE* existingFile, const char* mode)
    : BaseFile(existingFile, mode), inputBufferPos(0), inputBufferSize(0),
      outputBufferPos(0), outputBufferSize(0) {}

size_t RleFile::read(void* result, size_t size) {
    /*
    It does:
    - reads
    - decompresses
    - saves to result
    return: the length of the result; 0 if fail
    note: ignores \r
    */
    char* output = static_cast<char*>(result); // For simplicity in operations
    size_t totalRead = 0; // How much data read THIS time (including data from previous call (next block)).

    // If there is any data decompressed but not given, first, we give it.
    if (outputBufferPos < outputBufferSize) {
        size_t available = outputBufferSize - outputBufferPos;
        size_t toCopy = std::min(available, size);
        memcpy(output, outputBuffer + outputBufferPos, toCopy);
        output += toCopy; // Move to not overwrite just uploaded data.
        outputBufferPos += toCopy;
        totalRead += toCopy;
        size -= toCopy; // There is less free space.

        if (outputBufferPos == outputBufferSize) { // If we uploaded it all, just reset it.
            outputBufferPos = 0;
            outputBufferSize = 0;
        }
    }

    while (size > 0 && !feof(file_)) {
        if (inputBufferPos >= inputBufferSize) {
            inputBufferSize = read_raw(inputBuffer, sizeof(inputBuffer));
            inputBufferPos = 0;
            if (inputBufferSize == 0) break;
        }

        for (; inputBufferPos < inputBufferSize && outputBufferSize < sizeof(outputBuffer); ++inputBufferPos) {
            unsigned char c = inputBuffer[inputBufferPos];

            if (c == '\r') continue;

            int count = c - '0';
            if (inputBufferPos + 1 < inputBufferSize) {
                unsigned char ch = inputBuffer[++inputBufferPos];
                outputBuffer[outputBufferSize++] = ch;
                for (int i = 1; i < count && outputBufferSize < sizeof(outputBuffer); ++i) {
                    outputBuffer[outputBufferSize++] = ch;
                }
            }
        }

        size_t available = outputBufferSize - outputBufferPos;
        size_t toCopy = std::min(size, available);

        if (toCopy > 0) {
            memcpy(output, outputBuffer + outputBufferPos, toCopy);
            output += toCopy;
            outputBufferPos += toCopy;
            totalRead += toCopy;
            size -= toCopy;
        }
    }

    return totalRead;
}


size_t RleFile::write(const void* data, size_t dataSize) {
    const unsigned char* input = static_cast<const unsigned char*>(data);
    int bufferSize = dataSize * 3;
    unsigned char buffer[bufferSize];
    int bufferIndex = 0;

    if (dataSize == 0) {
        printf("Input data size is zero.\n");
        return 0;
    }

    int count = 1;
    unsigned char prevChar = input[0];

    for (size_t i = 1; i < dataSize; ++i) {
        if (input[i] == prevChar) {
            count++;
        } else {
            while (count > 0) {
                int chunk = std::min(count, 9);
                if (prevChar != '\r') {
                    if (bufferIndex + 2 >= bufferSize) {
                        printf("Buffer overflow detected.\n");
                        return 0;
                    }
                    buffer[bufferIndex++] = '0' + chunk;
                    buffer[bufferIndex++] = prevChar;
                }
                count -= chunk;
            }

            prevChar = input[i];
            count = 1;
        }
    }

    while (count > 0) {
        int chunk = std::min(count, 9);
        if (prevChar != '\r') {
            if (bufferIndex + 2 >= bufferSize) {
                printf("Buffer overflow detected.\n");
                return 0;
            }
            buffer[bufferIndex++] = '0' + chunk;
            buffer[bufferIndex++] = prevChar;
        }
        count -= chunk;
    }

    int writtenBytes = write_raw(buffer, bufferIndex);
    if (writtenBytes == 0) {
        printf("Failed to write to the file.\n");
        return 0;
    }

    return bufferIndex;
}


int write_int(IFile &file, int n) {
    char buffer[256];
    int length = sprintf(buffer, "%d", n);
    return file.write(buffer, length);
}


Base32File2::Base32File2(IFile* baseFile, const char* table, int tableSize)
    : baseFile_(*baseFile), table_(table), tableSize_(tableSize) {}

Base32File2::~Base32File2() {
    // delete &baseFile_;
}

bool Base32File2::can_read() { return baseFile_.can_read(); }
bool Base32File2::can_write() { return baseFile_.can_write(); }


int Base32File2::encoded32_size(int raw_size) {
    return (raw_size * 8 + 4) / 5;
}

int Base32File2::decoded32_size(int encoded_size) {
    return (encoded_size * 5) / 8;
}

int Base32File2::encode32(const void* raw_data, int raw_size, char* dst) {
    if (!raw_data || !dst || raw_size <= 0) return 1;

    const unsigned char *data = (const unsigned char *)raw_data;
    int bit_buffer = 0, bit_count = 0, dst_index = 0;

    for (int i = 0; i < raw_size; ++i) {
        bit_buffer = (bit_buffer << 8) | data[i];
        bit_count += 8;

        while (bit_count >= 5) {
            int index = (bit_buffer >> (bit_count - 5)) & 0x1F;
            dst[dst_index++] = table_[index];
            bit_count -= 5;
        }
    }

    if (bit_count > 0) {
        bit_buffer <<= (5 - bit_count);
        dst[dst_index++] = table_[bit_buffer & 0x1F];
    }

    dst[dst_index] = '\0';
    return 0;
}

int Base32File2::decode32(const char* encoded_data, int encoded_size, void* dst) {
    if (!encoded_data || !dst || encoded_size <= 0) return 1;

    unsigned char *data = (unsigned char *)dst;
    int bit_buffer = 0, bit_count = 0, raw_index = 0;

    for (int i = 0; i < encoded_size; ++i) {
        const char* ptr = strchr(table_, encoded_data[i]);
        if (!ptr) return 2;
        int value = ptr - table_;

        bit_buffer = (bit_buffer << 5) | value;
        bit_count += 5;

        while (bit_count >= 8) {
            data[raw_index++] = (bit_buffer >> (bit_count - 8)) & 0xFF;
            bit_count -= 8;
        }
    }

    return 0;
}

size_t Base32File2::read(void* decodedBuffer, size_t size) {
    char encodedData[encoded32_size(size)];
    size_t encodedSize = baseFile_.read(encodedData, sizeof(encodedData));

    if (decode32(encodedData, encodedSize, decodedBuffer)) {
        return 0; // decoding error
    }

    return decoded32_size(encodedSize);
}

size_t Base32File2::write(const void* decodedBuffer, size_t decodedSize) {
    int encodedSize = encoded32_size(decodedSize);
    char encodedData[encodedSize];

    if (encode32(decodedBuffer, decodedSize, encodedData)) {
        return 0; // Decoding error
    }

    return baseFile_.write(encodedData, encodedSize);
}

RleFile2::RleFile2(IFile* baseFile)
    : baseFile_(*baseFile),
      inputBufferSize_(0), inputBufferPos_(0),
      outputBufferSize_(0), outputBufferPos_(0) {}

RleFile2::~RleFile2() {
    // delete &baseFile_;
}

bool RleFile2::can_read() { return baseFile_.can_read(); }
bool RleFile2::can_write() { return baseFile_.can_write(); }

size_t RleFile2::read(void* result, size_t size) {
    char* output = static_cast<char*>(result);
    size_t totalRead = 0;

    // Сначала отдаем остатки из outputBuffer
    if (outputBufferPos_ < outputBufferSize_) {
        size_t available = outputBufferSize_ - outputBufferPos_;
        size_t toCopy = std::min(available, size);
        memcpy(output, outputBuffer_ + outputBufferPos_, toCopy);
        output += toCopy;
        outputBufferPos_ += toCopy;
        totalRead += toCopy;
        size -= toCopy;

        if (outputBufferPos_ == outputBufferSize_) {
            outputBufferPos_ = 0;
            outputBufferSize_ = 0;
        }
    }

    while (size > 0 && !feof()) {
        if (inputBufferPos_ >= inputBufferSize_) {
            inputBufferSize_ = baseFile_.read(inputBuffer_, sizeof(inputBuffer_));
            inputBufferPos_ = 0;
            if (inputBufferSize_ == 0) break;
        }

        while (inputBufferPos_ < inputBufferSize_ && outputBufferSize_ < sizeof(outputBuffer_)) {
            unsigned char c = inputBuffer_[inputBufferPos_];

            if (c == '\r') {
                ++inputBufferPos_;
                continue;
            }

            if (isdigit(c)) {
                int count = c - '0';
                if (inputBufferPos_ + 1 < inputBufferSize_) {
                    unsigned char val = inputBuffer_[++inputBufferPos_];
                    for (int i = 0; i < count && outputBufferSize_ < sizeof(outputBuffer_); ++i) {
                        outputBuffer_[outputBufferSize_++] = val;
                    }
                } else { // There is no pair (second char, not count). Break and load more next time.
                    break; // This will prevent memory loss.
                }
            } else {
                outputBuffer_[outputBufferSize_++] = c;
            }

            ++inputBufferPos_;
        }

        // Copy AMAP
        size_t available = outputBufferSize_ - outputBufferPos_;
        size_t toCopy = std::min(size, available);
        if (toCopy > 0) {
            memcpy(output, outputBuffer_ + outputBufferPos_, toCopy);
            output += toCopy;
            outputBufferPos_ += toCopy;
            totalRead += toCopy;
            size -= toCopy;
        }
    }

    return totalRead;
}

size_t RleFile2::write(const void* data, size_t dataSize) {
    const unsigned char* input = static_cast<const unsigned char*>(data);
    char buffer[dataSize * 2]; // worst case
    int bufferIndex = 0;

    int count = 1;
    unsigned char prevChar = input[0];

    for (size_t i = 1; i < dataSize; ++i) {
        if (input[i] == prevChar && count < 9) {
            count++;
        } else {
            buffer[bufferIndex++] = '0' + count;
            buffer[bufferIndex++] = prevChar;
            prevChar = input[i];
            count = 1;
        }
    }

    buffer[bufferIndex++] = '0' + count;
    buffer[bufferIndex++] = prevChar;

    return baseFile_.write(buffer, bufferIndex);
}

int RleFile2::encode_rle(const void* data, size_t size, void* dest) {
    if (!data || !dest || size == 0)
        return -1;

    const unsigned char* input = static_cast<const unsigned char*>(data);
    char* output = static_cast<char*>(dest);

    int out_index = 0;
    int count = 1;
    unsigned char prevChar = input[0];

    for (size_t i = 1; i < size && out_index < size * 2 - 2; ++i) {
        if (input[i] == prevChar) {
            count++;
        } else {
            output[out_index++] = '0' + count;
            output[out_index++] = prevChar;
            prevChar = input[i];
            count = 1;
        }
    }

    output[out_index++] = '0' + count;
    output[out_index++] = prevChar;

    return out_index;
}


int RleFile2::decode_rle(const void* data, size_t size, void* dest) {
    if (!data || !dest || size == 0)
        return -1;

    const char* input = static_cast<const char*>(data);
    char* output = static_cast<char*>(dest);

    int out_index = 0;

    for (int i = 0; i < size; i += 2) {
        if (i + 1 >= size)
            break;

        int count = input[i] - '0';
        char value = input[i + 1];

        for (int j = 0; j < count; ++j) {
            output[out_index++] = value;
        }
    }

    return out_index;
}

bool RleFile2::feof() const {
    return inputBufferPos_ >= inputBufferSize_ &&
           baseFile_.read(nullptr, 0) == 0;
}