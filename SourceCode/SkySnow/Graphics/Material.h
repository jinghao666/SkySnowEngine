//
// Created by liuqian8 on 2018/10/26.
//

#pragma once

#include "File.h"
#include "Object.h"
#include "Texture2D.h"

class Material: public Object
{
ENGINE_OBJECT(Material,Object);
public:
    Material(Context* context);
    ~Material();
    int setShaderVariation(string vsName,string fsName);
    void setTexture(Texture2D* textureId);
    void bindTexture();
private:
    File* mFile = NULL;
    Graphics* graphics;
    GL_ShaderProgram* shaderProgram;
    Texture2D* textureId_;
    ShaderVariation* vs;
    ShaderVariation* fs;
};
