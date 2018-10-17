//
// Created by liuqian8 on 2018/10/17.
//

#include "IndexBuffer.h"
#include "Graphics.h"

void IndexBuffer::release()
{

}

bool IndexBuffer::setData(const void *data)
{
    if(!data)
    {
        LOGI("NUll pointer for index buffer data in GLESIndexBuffer!");
        return false;
    }

    if(object_.name_)//着色器程序链接成功
    {
        graphics_->setIndexBuffer(this);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indexCount_ * indexSize_,data,dynamic_?GL_DYNAMIC_DRAW:GL_STATIC_DRAW);
    }
    return true;
}

bool IndexBuffer::create()
{
    if(!indexCount_)
    {
        release();
        return true;
    }

    if(graphics_)
    {
        if(!object_.name_)
            glGenBuffers(1,&object_.name_);
        if(!object_.name_)
        {
            LOGE("Failed to create index buffer in GLESIndexBuffer.cpp!");
            return false;
        }
        graphics_ ->setIndexBuffer(this);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, nullptr, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }
    return true;
}
