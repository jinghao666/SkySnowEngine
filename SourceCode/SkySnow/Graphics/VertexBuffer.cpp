//
// Created by liuqian8 on 2018/10/16.
//
#include "VertexBuffer.h"
#include "Graphics.h"

VertexBuffer::VertexBuffer(Context *context, bool forceHeadless):
        Object(context),
        GPUObject(forceHeadless?NULL:getSubsystem<Graphics>()),
        vertexCount_(0),
        dynamic_(false)
{

}

void VertexBuffer::test()
{
    VertexElement vertexElement(TYPE_VECTOR2,SEM_POSITION,ShaderVariation::elementSemanticNames[0]);
    vertexElement.offset_ = 0;
    elements_.push_back(vertexElement);

    VertexElement vertexElement1(TYPE_VECTOR2,SEM_TEXCOORD,ShaderVariation::elementSemanticNames[4]);
    vertexElement1.offset_ = 2 * sizeof(float);;
    elements_.push_back(vertexElement1);
}
bool VertexBuffer::setSize(unsigned vertexCount, unsigned vertexSize, bool dynamic)
{
    vertexCount_ = vertexCount;
    vertexSize_ = vertexSize;
    dynamic_ = dynamic;
    test();
    return create();
}

VertexBuffer::~VertexBuffer()
{

}