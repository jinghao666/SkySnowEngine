//
// Created by liuqian8 on 2018/10/13.
//

#include "GL_GraphicsImpl.h"

GL_GraphicsImpl::GL_GraphicsImpl():
        shaderProgram_(NULL),
        vertexAttributes_(NULL),
        enabledVertexAttributes_(0),
        vertexBuffersDirty_(false)
{

}