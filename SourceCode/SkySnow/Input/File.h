//
// Created by liuqian8 on 2018/10/23.
//

#pragma once

#include "Object.h"
#include <string>
#include <vector>
#include "Data.h"
using namespace std;
enum FileMode
{
    FILE_READ = 0,
    FILE_WRITE,
    FILE_READWRITE
};

enum class Status
{
    OK = 0,
    NotExists = 1, // File not exists
    OpenFailed = 2, // Open file failed.
    ReadFailed = 3, // Read failed
    NotInitialized = 4, // File is not initializes
    TooLarge = 5, // The file is too large (great than 2^32-1)
    ObtainSizeFailed = 6 // Failed to obtain the file size.
};


class ResizableBuffer {
public:
    virtual ~ResizableBuffer() {}
    virtual void resize(size_t size) = 0;
    virtual void* buffer() const = 0;
};

template<typename T> class ResizableBufferAdapter { };


template<typename CharT, typename Traits, typename Allocator> class ResizableBufferAdapter< std::basic_string<CharT, Traits, Allocator> > : public ResizableBuffer {
    typedef std::basic_string<CharT, Traits, Allocator> BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        _buffer->resize((size + sizeof(CharT) - 1) / sizeof(CharT));
    }
    virtual void* buffer() const override {
        // can not invoke string::front() if it is empty

        if (_buffer->empty())
            return nullptr;
        else
            return &_buffer->front();
    }
};

template<typename T, typename Allocator> class ResizableBufferAdapter< std::vector<T, Allocator> > : public ResizableBuffer {
    typedef std::vector<T, Allocator> BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        _buffer->resize((size + sizeof(T) - 1) / sizeof(T));
    }
    virtual void* buffer() const override {
        // can not invoke vector::front() if it is empty

        if (_buffer->empty())
            return nullptr;
        else
            return &_buffer->front();
    }
};


template<> class ResizableBufferAdapter<Data> : public ResizableBuffer {
    typedef Data BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        size_t oldSize = static_cast<size_t>(_buffer->getSize());
        if (oldSize != size) {
            auto old = _buffer->getBytes();
            void* buffer = realloc(old, size);
            if (buffer)
                _buffer->fastSet((unsigned char*)buffer, size);
        }
    }
    virtual void* buffer() const override {
        return _buffer->getBytes();
    }
};

class File : public Object
{
ENGINE_OBJECT(File,Object);
public:
    File(Context *context):
            Object(context)
    {

    }

    virtual ~File();

    string getStringFromFile(const string filename,FileMode mode = FILE_READ);

protected:
    template <typename T,typename Enable = typename std::enable_if<std::is_base_of< ResizableBuffer, ResizableBufferAdapter<T> >::value>::type>
    Status getContents(const std::string& filename, T* buffer) {
        ResizableBufferAdapter<T> buf(buffer);
        return getContents(filename, &buf);
    }
    Status getContents(const std::string& filename,ResizableBuffer* buffer);
};
