//
// Created by liuqian8 on 2018/10/3.
//

#pragma once
#include "GPUObject.h"
#include "GraphicsDefs.h"
struct ShaderParameter
{
    ShaderParameter()
    {

    }
    ShaderType type_;
    string name_;

    union
    {
        unsigned offset_;
        int location_;
    };
    unsigned glType_;
};


class ShaderVariation:public GPUObject
{
public:
    ShaderVariation(Graphics* graphics,ShaderType shaderType,string pSource);
    bool Create();
    ~ShaderVariation();
    unsigned GetGPUObjectName() //const
    {
        return object_.name_;
    }
    static const char* elementSemanticNames[];
private:
    ShaderType type_;
    const string pSource_;
};

