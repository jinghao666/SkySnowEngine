//
// Created by liuqian8 on 2018/10/3.
//

#pragma once

#include "Object.h"
#include "GPUObject.h"

class IndexBuffer:public Object,public GPUObject
{
    ENGINE_OBJECT(IndexBuffer,Object);
public:
    IndexBuffer(Context* context,bool forceHeadless = false);
    virtual ~IndexBuffer();
    //重置状态
    virtual void release();
    //设置数据
    bool setData(const void* data);

    unsigned getIndexCount() const
    {
        return indexCount_;
    }

    unsigned getIndexSize()
    {
        return indexSize_;
    }

    bool setSize(unsigned indexCount, bool largeIndices,bool dynamic = false);

private:
    bool create();
    unsigned indexCount_;
    unsigned indexSize_;
    bool dynamic_;
};
