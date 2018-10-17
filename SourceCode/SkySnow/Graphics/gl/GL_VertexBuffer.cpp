//
// Created by liuqian8 on 2018/10/12.
//

#include "VertexBuffer.h"
#include "Graphics.h"
bool VertexBuffer::setData(const void *data)
{
    if(!data)//打印异常日志
    {
        LOGE("Null pointer for vertex buffer data in GLESVertexBuffer.cpp");
    }

    if(!vertexSize_)//打印异常日志
    {
        LOGE("Vertex elements not defined, can not set vertex buffer data in GLESVertexBuffer.cpp");
    }

    if(object_.name_)//创建VBO，并绑定数据
    {
//        graphics_->设置VBO
        graphics_-> setVBO(object_.name_);
        glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    } else{
        LOGE("object_.name_ is NULL(Who is GL Shander Program) in GLESVertexBuffer.cpp");
    }
    return true;
}

bool VertexBuffer::create()
{
    if(!vertexCount_)
    {
        LOGE("vertexCount_ was 0, in GLESVertexBuffer.cpp");
        return true;
    }


    if(graphics_)
    {
        if(!object_.name_)
        {
            glGenBuffers(1, &object_.name_);
        }
        graphics_->setVBO(object_.name_);
        glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, nullptr, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
//        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    return true;
}
