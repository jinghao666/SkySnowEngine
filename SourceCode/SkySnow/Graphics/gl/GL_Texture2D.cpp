//
// Created by liuqian8 on 2018/10/5.
//

#include "Texture2D.h"

Texture2D::Texture2D(Context *context):
        GPUObject(getSubsystem<Graphics>()),
        Object(context),
        glTextureId_(0),
        isCreate(false)
{

}

Texture2D::~Texture2D()
{
    isCreate = false;
}


void Texture2D::bindTexture(GL_ShaderProgram* shaderProgram)
{
    shaderProgram_ = shaderProgram;
    if(!isCreate)
    {
        create();
        isCreate = true;
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, glTextureId_);
    glUniform1i(object_.name_, 0);//使用0号纹理
}

void Texture2D::create()
{
    object_.name_ = glGetUniformLocation(shaderProgram_->getGPUObjectName(), "sTexture");
}