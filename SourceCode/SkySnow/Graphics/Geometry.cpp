//
// Created by liuqian8 on 2018/10/14.
//
#include "Geometry.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Graphics.h"

Geometry::Geometry(Context *context) :
        Object(context),
        primitiveType_(TRIANGLE_LIST),
        indexStart_(0),
        vertexStart_(0),
        indexCount_(0),
        vertexCount_(0)
{

}

Geometry::~Geometry()
{

}

void Geometry::setIndexBuffer(IndexBuffer *buffer)
{
    indexBuffer_ = buffer;
}

void Geometry::setVertexBuffer(VertexBuffer *vertexBuffer)
{
    vertexBuffer_ = vertexBuffer;
    vertexCount_ = vertexBuffer_->getVertexCount();
}

void Geometry::draw(Graphics* graphics)
{
    if(indexBuffer_ && indexCount_ > 0)//索引法绘制
    {
        graphics->setIndexBuffer(indexBuffer_);
        graphics->setVertexBuffer(vertexBuffer_);
        graphics->draw(primitiveType_, indexStart_, indexCount_, vertexStart_, vertexCount_);
    }else if (vertexCount_ > 0)//三角形卷染法绘制
    {
        graphics->setVertexBuffer(vertexBuffer_);
        graphics->draw(primitiveType_, vertexStart_, vertexCount_);
    }

}
