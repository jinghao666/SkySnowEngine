//
// Created by liuqian8 on 2018/11/21.
//

#pragma once

#include "GraphicsDefs.h"
#include <string>
#include "Object.h"
using namespace std;

class ShaderVariation;

enum PassLightingMode
{
    LIGHTING_UNLIT = 0,//
    LIGHTING_PERVERTEX,
    LIGHTING_PERPIXEL
};

class Pass
{
public:
    Pass(const string& passName);

    virtual ~Pass();

    void SetBlendMode(BlendMode mode);
};


class Technique:public Object
{
    ENGINE_OBJECT(Technique,Object);
    friend class Renderer;
public:
    Technique(Context* context);

    virtual ~Technique();
};
