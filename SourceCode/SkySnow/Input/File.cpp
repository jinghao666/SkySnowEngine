//
// Created by liuqian8 on 2018/10/23.
//
#include "File.h"
#include <sys/stat.h>

File::~File()
{

}

std::string File::getStringFromFile(const string filename, FileMode mode)
{
    std::string s;
    getContents(filename,&s);
    return s;
}

Status File::getContents(const std::string &filename, ResizableBuffer *buffer)
{
    if(filename.empty())
        return Status::NotExists;

    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp)
        return Status::OpenFailed;

#if defined(_MSC_VER)
    auto descriptor = _fileno(fp);
#else
    auto descriptor = fileno(fp);
#endif

    struct stat statBuf;
    if (fstat(descriptor, &statBuf) == -1) {
        fclose(fp);
        return Status::ReadFailed;
    }
    size_t size = statBuf.st_size;

    buffer->resize(size);
    size_t readsize = fread(buffer->buffer(), 1, size, fp);
    fclose(fp);

    if (readsize < size) {
        buffer->resize(readsize);
        return Status::ReadFailed;
    }

    return Status::OK;
}