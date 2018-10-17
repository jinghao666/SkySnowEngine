//
// Created by liuqian8 on 2018/10/13.
//
#pragma once
#include "GL_ShaderProgram.h"

using ShaderProgramMap = SN_Map<pair<ShaderVariation*,ShaderVariation*>,GL_ShaderProgram*>;
class GL_GraphicsImpl
{
    friend class Graphics;

public:
    GL_GraphicsImpl();

private:

//    const SN_HashMap<string ,int>* vertexAttributes_;
    const SN_Map<pair<char ,string>,unsigned >* vertexAttributes_;
    /// Shader program in use.
    GL_ShaderProgram* shaderProgram_;
    /// Linked shader programs.
    ShaderProgramMap shaderPrograms_;
    /// Enabled vertex attributes bitmask.
    unsigned  enabledVertexAttributes_;
    bool vertexBuffersDirty_;

    //当前绑定的顶点数组属性ID
    unsigned boundVBO_;
};
