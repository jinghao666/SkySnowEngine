//
// Created by liuqian8 on 2018/10/3.
//

#include "ShaderVariation.h"

ShaderVariation::ShaderVariation(Graphics* graphics,ShaderType shaderType, string pSource) :
        GPUObject(graphics),
        type_(shaderType),
        pSource_(pSource)
{

}

ShaderVariation::~ShaderVariation()
{

}