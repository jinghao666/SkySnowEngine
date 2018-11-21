//
// Created by liuqian8 on 2018/10/4.
//

#pragma once

#include "Context.h"
#include "GPUObject.h"
#include "GL_ShaderProgram.h"

class Texture2D : public Object,public GPUObject
{
    ENGINE_OBJECT(Texture2D,Object)
public:
    Texture2D(Context* context);

    virtual ~Texture2D();

    void setTextureId(int textureId)
    {
        glTextureId_ = textureId;

    }

    int getGLTextureId()
    {
        return glTextureId_;
    }

    void bindTexture(GL_ShaderProgram* shaderProgram);

    int getWidth()
    {
        return width_;
    }

    int getHeight()
    {
        return height_;
    }
protected:
    int width_;
    int height_;
    int glTextureId_;
    GL_ShaderProgram* shaderProgram_;
private:
    void create();
    bool isCreate;
};
