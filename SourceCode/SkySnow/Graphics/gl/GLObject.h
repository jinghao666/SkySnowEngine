//
// Created by liuqian8 on 2018/9/30.
//

#pragma once

#include "Common.h"

class GLObject
{
public:
    GLObject();

    virtual ~GLObject();

    GLuint getGLNmae() const
    {
        return m_glName;
    }

    bool isCreated() const
    {
        return m_glName != 0;
    }


protected:
    GLuint m_glName = 0;//OpenGL  name


};
