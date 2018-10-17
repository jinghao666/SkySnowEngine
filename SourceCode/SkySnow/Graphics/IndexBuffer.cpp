//
// Created by liuqian8 on 2018/10/3.
//
#include "IndexBuffer.h"
#include "Graphics.h"

IndexBuffer::IndexBuffer(Context* context,bool forceHeadless) :
        Object(context),
        GPUObject(forceHeadless? NULL:getSubsystem<Graphics>()),
        indexCount_(0),
        indexSize_(0),
        dynamic_(false)
{

}

IndexBuffer::~IndexBuffer()
{
    indexCount_ = 0;
    indexSize_ = 0;
}

bool IndexBuffer::setSize(unsigned indexCount, bool largeIndices, bool dynamic)
{
    indexCount_ = indexCount;
    indexSize_  = (unsigned)(largeIndices? sizeof(unsigned): sizeof(unsigned short));
    dynamic_ = dynamic;
    return create();
}