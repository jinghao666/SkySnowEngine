//
// Created by liuqian8 on 2018/10/13.
//

#include "GL_ShaderProgram.h"

//static unsigned numberPostfix(const string& str)
//{
//    for (unsigned i = 0; i < str.length(); ++i)
//    {
//        if (isdigit(str[i]))//IsDigit
//            return (unsigned)strtoul(str.c_str() + i, nullptr, 10);
//    }
//    return M_MAX_UNSIGNED;
//}
GL_ShaderProgram::GL_ShaderProgram(Graphics* graphics,ShaderVariation* vs ,ShaderVariation* fs) :
        GPUObject(graphics),
        vertex_(vs),
        frag_(fs)
{
}
GL_ShaderProgram::~GL_ShaderProgram()
{
    glDeleteProgram(object_.name_);
    shaderParameters_.clear();
    vertexAttributes_.clear();
    delete vertex_;
    delete frag_;
}

unsigned GL_ShaderProgram::Link()
{
    if(!vertex_ || !frag_ || !vertex_->GetGPUObjectName() || !frag_->GetGPUObjectName())
        return 0;
    object_.name_ = glCreateProgram();
    if(!object_.name_)
    {
        LOGE("Could not create shader program");
        return 0;
    }
    glAttachShader(object_.name_,vertex_->GetGPUObjectName());
    glAttachShader(object_.name_,frag_->GetGPUObjectName());
    glLinkProgram(object_.name_);

    int linked,length;
    glGetProgramiv(object_.name_,GL_LINK_STATUS,&linked);
    if(!linked)//如果链接着色器程序失败，那么打印信息。
    {
        glGetProgramiv(object_.name_,GL_INFO_LOG_LENGTH,&length);
        if(length)
        {
            char* buf = (char*)malloc(length);
            glGetProgramInfoLog(object_.name_, length, NULL, buf);
            LOGE("Could not link program:\n%s\n", buf);
            free(buf);
        }
        glDeleteProgram(object_.name_);
        object_.name_ = 0;
    }
    glUseProgram(object_.name_);

    //对着色器程序进行状态查询
    const int MAX_NAME_LENGTH = 256;
    char nameBuffer[MAX_NAME_LENGTH];
    int attributeCount, uniformCount,elementCount,nameLength;
    GLenum type;
    glGetProgramiv(object_.name_,GL_ACTIVE_ATTRIBUTES,&attributeCount);
    LOGI("attributeCount： %d",attributeCount);
    for(int i = 0;i < attributeCount; ++i)
    {
        glGetActiveAttrib(object_.name_,i,(GLsizei)MAX_NAME_LENGTH,&nameLength, &elementCount, &type, nameBuffer);
        string name = string(nameBuffer,nameLength);
        LOGI("attribute name:%s",name.c_str());
        VertexElementSemantic semantic = MAX_VERTEX_ELEMENT_SEMANTICS;
        unsigned char semanticIndex = 0;
        for(unsigned j = MAX_VERTEX_ELEMENT_SEMANTICS - 1;j < MAX_VERTEX_ELEMENT_SEMANTICS; -- j)
        {
            int flag = name.find(ShaderVariation::elementSemanticNames[j]);
            if(flag >= 0)//name.find("p")
            {
                semantic = (VertexElementSemantic)j;
                LOGE("semantic:%d",semantic);
                LOGE("semanticIndex:%s",name.c_str());
                LOGE("j:%d",j);
                break;
            }
        }

        int location = glGetAttribLocation(object_.name_, name.c_str());

        vertexAttributes_[make_pair(semantic,name)] = location;
        LOGI("location:%d",location);
    }

    //获取uniforms 变量

    glGetProgramiv(object_.name_, GL_ACTIVE_UNIFORMS, &uniformCount);
    LOGE("uniformCount:%d",uniformCount);
    for(int i = 0; i < uniformCount; ++i)
    {
        glGetActiveUniform(object_.name_,(GLuint)i,MAX_NAME_LENGTH,nullptr, &elementCount, &type, nameBuffer);
        int location = glGetUniformLocation(object_.name_, nameBuffer);
        string name(nameBuffer);
        if(name[0] == 'c')
        {
            //将c打头的字符截掉
            string paramName = name.substr(1);
            ShaderParameter parameter;
            parameter.name_ = paramName;
            parameter.glType_ = type;
            parameter.location_ = location;

            if(location >= 0)
                shaderParameters_[paramName] = parameter;
        }else if(location >= 0 && name[0] == 's'){//处理Sample2D类型的统一变量
            LOGE("Sample2D name:%s",name.c_str());
        }
    }

    return object_.name_;
}

const ShaderParameter* GL_ShaderProgram::getParameter(string param) const
{
    LOGI("shaderParameters_.size():%d",shaderParameters_.size());
    SN_HashMap<string,ShaderParameter>::const_iterator i = shaderParameters_.find(param);
    if(i != shaderParameters_.end())
        return &i->second;
    else
        return NULL;
}

ShaderVariation* GL_ShaderProgram::getVertexShader() const
{
    return vertex_;
}

ShaderVariation* GL_ShaderProgram::getPixelShader() const
{
    return frag_;
}