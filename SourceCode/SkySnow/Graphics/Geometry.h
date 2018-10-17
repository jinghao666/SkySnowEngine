//
// Created by liuqian8 on 2018/10/11.
//
#pragma once


#include "Object.h"
#include "GraphicsDefs.h"

class IndexBuffer;
class VertexBuffer;
class Graphics;
class Geometry : public Object
{
    ENGINE_OBJECT(Geometry,Object);
public:
    Geometry(Context* context);

    virtual ~Geometry();

    void setIndexBuffer(IndexBuffer* buffer);
    void setVertexBuffer(VertexBuffer* vertexBuffer);
    void draw(Graphics* graphics);

private:
    VertexBuffer* vertexBuffer_;
    IndexBuffer* indexBuffer_;
    unsigned indexCount_;
    unsigned vertexCount_;
    PrimitiveType primitiveType_;
    unsigned indexStart_;
    unsigned vertexStart_;
};
