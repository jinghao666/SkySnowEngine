//
// Created by liuqian8 on 2018/10/7.
//

#include <cstdlib>
#include "ShaderVariation.h"

const char* ShaderVariation::elementSemanticNames[] =
        {
                "pos",//POS
                "normal",//NORMAL
                "binormal",//BINORMAL
                "tangent",//TANGENT
                "texCoords",//TEXCOORD
                "color",//COLOR
                "blendWeight",//BLENDWEIGHT
                "blendIndices",//BLENDINDICES
                "objectIndex"//OBJECTINDEX
        };

bool ShaderVariation::Create()
{
    bool isCompiled = false;
    GLuint shader = glCreateShader(type_ == VS ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    if (shader) {

        const char* temp = pSource_.c_str();
        glShaderSource(shader, 1, &temp,0);//pSource_
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        isCompiled = true;
        if (!compiled) {
            isCompiled = false;
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    object_.name_ = shader;
    return isCompiled;
}