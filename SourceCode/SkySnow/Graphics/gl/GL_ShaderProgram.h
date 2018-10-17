//
// Created by liuqian8 on 2018/10/7.
//

#pragma once

#include "Graphics.h"
#include "GPUObject.h"

class GL_ShaderProgram: public GPUObject
{
public:
    GL_ShaderProgram(Graphics* graphics,ShaderVariation* vs,ShaderVariation* fs);

    ~GL_ShaderProgram();

    unsigned Link();

    const SN_Map<pair<char ,string>,unsigned >& getVertexAttributes() const
    {
        return vertexAttributes_;
    }

    /// Return the info for a shader parameter, or null if does not exist.
    const ShaderParameter* getParameter(string param) const;
    ShaderVariation* getVertexShader() const ;

    ShaderVariation* getPixelShader() const;

protected:
    ShaderVariation* vertex_;
    ShaderVariation* frag_;
    SN_HashMap<string,ShaderParameter> shaderParameters_;
//    SN_HashMap<string ,int> vertexAttributes_;

    SN_Map<pair<char ,string>,unsigned > vertexAttributes_;
    pair<char,string> test;
};
