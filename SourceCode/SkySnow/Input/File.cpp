//
// Created by liuqian8 on 2018/10/23.
//
#include "File.h"
#include <sys/stat.h>
File::~File()
{

}

std::string File::getStringFromFile(const string filename)
{
    std::string s;
    getContents(filename,&s);
    return s;
}

std::string File::getStringFromFileAssets(const string filename)
{
    std::string s;
#if PLATFORM == PLATFORM_ANDROID
    AAssetManager* mgr_ = context_->getAAssetManager();
    AAsset *asset = AAssetManager_open(mgr_, filename.c_str(), AASSET_MODE_BUFFER);
    if(!asset){
        LOGE("asset not found");
        return NULL;
    }
    long size = AAsset_getLength(asset);
    ResizableBuffer *buffer = getResizableBuffer(&s);
    buffer->resize(size);
    int readsize = AAsset_read(asset, buffer->buffer(), size);
    AAsset_close(asset);
    if (readsize < size) {
        if (readsize >= 0)
            buffer->resize(readsize);
        LOGE("ReadFailed! --- File.cpp");
        return nullptr;
    }
    return s;
#endif
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