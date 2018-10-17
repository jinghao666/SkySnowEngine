//
// Created by liuqian8 on 2018/10/16.
//

#pragma once

#include "Object.h"
#include "GPUObject.h"
#include "GraphicsDefs.h"

class VertexBuffer: public Object,public GPUObject
{
    ENGINE_OBJECT(VertexBuffer,Object);
public:
    VertexBuffer(Context* context,bool forceHeadless = false);

    ~VertexBuffer();
    unsigned getVertexSize()const
    {
        return vertexSize_;
    }

    bool setData(const void* data);

    bool setSize(unsigned vertexCount, unsigned vertexSize, bool dynamic = false);

    unsigned getVertexCount()
    {
        return vertexCount_;
    }

    bool isDynamic()
    {
        return dynamic_;
    }

    const vector<VertexElement>& getElements() const
    {
        return elements_;
    }

    void test();

private:
    void updateOffsets();
    bool create();

    vector<VertexElement> elements_;
    unsigned vertexCount_;
    unsigned vertexSize_;
    bool dynamic_;
};
