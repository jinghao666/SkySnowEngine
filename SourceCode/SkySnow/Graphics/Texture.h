//
// Created by liuqian on 2018/10/11.
//

#pragma once
#include "SNObject.h"
//纹理的格式为2D纹理，3D纹理，2D纹理数组，立方体纹理
enum class TextureType
{
    NONE,
    _2D,
    CUBE,
    _3D,
    _2D_ARRAY
};

enum class Format
{

};

class Texture:public SNObject
{
public:
    Texture();
    virtual ~Texture();

    unsigned getWidth() const
    {
        return width_;
    }

    unsigned getHeight()const
    {
        return height_;
    }

    unsigned getDepth() const
    {
        return depth_;
    }

    unsigned getLayerCount()const
    {
        return layerCount_;
    }

    unsigned getMipCount() const
    {
        return mipCount_;
    }
protected:
    unsigned width_ = 0;
    unsigned height_ = 0;
    unsigned depth_ = 0;
    unsigned layerCount_ = 0;
    unsigned mipCount_ = 0;


};