//
// Created by liuqian8 on 2018/10/26.
//

#include "File.h"
#include "Material.h"

Material::Material(Context *context):
        Object(context),
        mFile(0),
        graphics(0),
        shaderProgram(0),
        textureId_(0)
{

}
Material::~Material()
{
    delete shaderProgram;
    delete vs;
    delete fs;
}
int Material::setShaderVariation(string vsName,string fsName)
{
    mFile = this->getSubsystem<File>();
    graphics = this->getSubsystem<Graphics>();
    vs = new ShaderVariation(graphics,VS, mFile->getStringFromFile(vsName));
    fs = new ShaderVariation(graphics,FS,mFile->getStringFromFile(fsName));
    graphics->SetShaders(vs,fs);

    return graphics->getShaderProgram()->getGPUObjectName();
}

void Material::setTexture(Texture2D* textureId)
{
    textureId_ = textureId;
}

void Material::bindTexture()
{
    textureId_->bindTexture(shaderProgram);
}