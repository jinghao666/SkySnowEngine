//
// Created by liuqian8 on 2018/10/12.
//

#include "Graphics.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "GL_GraphicsImpl.h"

static const unsigned glCmpFunc[] =
{
        GL_ALWAYS,
        GL_EQUAL,
        GL_NOTEQUAL,
        GL_LESS,
        GL_LEQUAL,
        GL_GREATER,
        GL_GEQUAL
};

static const unsigned glSrcBlend[] =
{
        GL_ONE,
        GL_ONE,
        GL_DST_COLOR,
        GL_SRC_ALPHA,
        GL_SRC_ALPHA,
        GL_ONE,
        GL_ONE_MINUS_DST_ALPHA,
        GL_ONE,
        GL_SRC_ALPHA
};

static const unsigned glDestBlend[] =
{
        GL_ZERO,
        GL_ONE,
        GL_ZERO,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_ONE,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_ALPHA,
        GL_ONE,
        GL_ONE
};

static const unsigned glBlendOp[] =
{
        GL_FUNC_ADD,
        GL_FUNC_ADD,
        GL_FUNC_ADD,
        GL_FUNC_ADD,
        GL_FUNC_ADD,
        GL_FUNC_ADD,
        GL_FUNC_ADD,
        GL_FUNC_REVERSE_SUBTRACT,
        GL_FUNC_REVERSE_SUBTRACT
};

static const unsigned glStencilOps[] =
{
        GL_KEEP,
        GL_ZERO,
        GL_REPLACE,
        GL_INCR_WRAP,
        GL_DECR_WRAP
};
static const unsigned glElementTypes[] =
{
        GL_INT,
        GL_FLOAT,
        GL_FLOAT,
        GL_FLOAT,
        GL_FLOAT,
        GL_UNSIGNED_BYTE,
        GL_UNSIGNED_BYTE
};

static const unsigned glElementComponents[] =
{
        1,
        1,
        2,
        3,
        4,
        4,
        4
};
static void getGLPrimitiveType(unsigned elementCount, PrimitiveType type, unsigned& primitiveCount, GLenum& glPrimitiveType)
{
    switch(type)
    {
        case TRIANGLE_LIST:
            primitiveCount = elementCount / 3;
            glPrimitiveType = GL_TRIANGLES;
            break;

        case LINE_LIST:
            primitiveCount = elementCount / 2;
            glPrimitiveType = GL_LINES;
            break;

        case POINT_LIST:
            primitiveCount = elementCount;
            glPrimitiveType = GL_POINTS;
            break;

        case TRIANGLE_STRIP:
            primitiveCount = elementCount - 2;
            glPrimitiveType = GL_TRIANGLE_STRIP;
            break;

        case LINE_STRIP:
            primitiveCount = elementCount - 1;
            glPrimitiveType = GL_LINE_STRIP;
            break;

        case TRIANGLE_FAN:
            primitiveCount = elementCount - 2;
            glPrimitiveType = GL_TRIANGLE_FAN;
            break;
    }
}
Graphics::Graphics(Context *context):
        Object(context),
        impl_(new GL_GraphicsImpl())
{
    ResetCachedState();
}

Graphics::~Graphics()
{
    delete  impl_;
    impl_ = NULL;
}
void Graphics::SetShaders(ShaderVariation *vs, ShaderVariation *fs)
{
    // compile the shaders now if not yet compiled. if already attemted, do not retry
    if(vs && !vs->GetGPUObjectName())
    {
        bool success = vs->Create();
        if(success){
            LOGI("Compiled vertex shader success! in GLESGraphics");
        }else{
            LOGE("Failed to compile vertex shader!  in GLESGraphics");
            vs = 0;
        }
    }

    if(fs && !fs->GetGPUObjectName())
    {
        bool success = fs -> Create();
        if(success){
            LOGI("Compiled frag shader success! in GLESGraphics");
        }else{
            LOGE("Compiled frag shader Failed! in GLESGraphics");
        }
    }
    // if vs is 0 and fs is 0 ,use program null
    if(!vs || ! fs)//如果编译顶点着色器与片元着色器失败，那么使用空着色器对象
    {
        glUseProgram(0);
        vertexShader_ = 0;
        fragShader_ = 0;
    }else{
        //根据设置，来初始化与GPU着色器交互的句柄
        vertexShader_ = vs;
        fragShader_ = fs;

        pair<ShaderVariation*,ShaderVariation*> combination(vs,fs);
        ShaderProgramMap::iterator i = impl_->shaderPrograms_.find(combination);

        if(i != impl_->shaderPrograms_.end())
        {
            //使用已经存在的着色器程序
            if(i ->second->getGPUObjectName())
            {
                glUseProgram(i->second->getGPUObjectName());
                impl_->shaderProgram_ = i->second;
            }else{
                glUseProgram(0);
                impl_->shaderProgram_ = NULL;
            }
        }else{
            //链接一个新的着色器对象
            GL_ShaderProgram* newProgram(new GL_ShaderProgram(this,vs,fs));
            if(newProgram ->Link())
            {
                impl_->shaderProgram_ = newProgram;
            }else{
                glUseProgram(0);
                impl_->shaderProgram_ = nullptr;
            }
            impl_->shaderPrograms_[combination] = newProgram;
        }
    }

    if(impl_ ->shaderProgram_)
    {
        impl_->vertexAttributes_ = &impl_->shaderProgram_->getVertexAttributes();
    } else{
        impl_->vertexAttributes_ = NULL;
    }
    impl_->vertexBuffersDirty_ = true;
}
void Graphics::ResetCachedState()
{
    vertexShader_ = 0;
    fragShader_ = 0;
    impl_->boundVBO_ = 0;
//    indexBuffer_ = 0;
//    depthTestMode_ = CMP_ALWAYS;
}

void Graphics::setIndexBuffer(IndexBuffer *buffer)
{
    if(indexBuffer_ == buffer)
        return;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer?buffer->getGPUObjectName():0);

    indexBuffer_ = buffer;
}

void Graphics::setVertexBuffer(VertexBuffer *buffer)
{
    static vector<VertexBuffer*> vertexBuffers(1);
    vertexBuffers[0] = buffer;
    setVertexBuffers(vertexBuffers);
}

bool Graphics::setVertexBuffers(const vector<VertexBuffer *> &buffers, unsigned instanceOffset)
{
    if(buffers.size() > MAX_VERTEX_STREAMS)
    {
#if !RENDER_EFFECT_PLATFORM
        LOGE("Too many vertex buffers at GLESGraphics.cpp");
#else
        printf("Too many vertex buffers at GLESGraphics.cpp\n");
#endif
    }

    for(unsigned i = 0; i <MAX_VERTEX_STREAMS; ++ i)
    {
        VertexBuffer* buffer = NULL;
        if(i < buffers.size())
            buffer = buffers[i];
        if(buffer != vertexBuffers_[i])
        {
            vertexBuffers_[i] = buffer;
        }
    }
    return true;
}

void Graphics::setShaderParameter(string parm, float value)
{
    if(impl_->shaderProgram_)
    {
        const ShaderParameter* info = impl_->shaderProgram_->getParameter(parm);
        if(info)
        {
            glUniform1fv(info->location_,1,&value);
        }
    }
}

void Graphics::setShaderParameter(string param, int value)
{
    if(impl_->shaderProgram_)
    {
        const ShaderParameter* info = impl_->shaderProgram_->getParameter(param);
        if(info)
        {
            glUniform1i(info->location_,value);
        }
    }
}

void Graphics::setShaderParameter(string param, bool value)
{
    if(impl_->shaderProgram_)
    {
        const ShaderParameter* info = impl_->shaderProgram_->getParameter(param);
        if(info)
        {
            glUniform1i(info->location_,(int)value);
        }
    }
}

void Graphics::setShaderParameter(string param, const glm::vec2 &vector)
{
    const ShaderParameter* info = impl_->shaderProgram_->getParameter(param);
    if(info)
    {
        // Check the uniform type to avoid mismatch
        switch (info->glType_) {
            case GL_FLOAT:
//                glUniform1fv(info->location_, 1,vector.Data());
                glUniform1f(info->location_, vector.x);
                break;

            case GL_FLOAT_VEC2:
//                glUniform2fv(info->location_,1, vector.Data());
                glUniform2f(info->location_, vector.x,vector.y);
                break;

            default:
                break;
        }
    }
}

void Graphics::setShaderParamter(string param, const glm::vec4& vector)
{
    if(impl_->shaderProgram_)
    {
        const ShaderParameter* info = impl_->shaderProgram_->getParameter(param);
        if(info)
        {
            switch (info->glType_)
            {
                case GL_FLOAT:
//                    glUniform1fv(info->location_,1,vector);
                    glUniform1f(info->location_,vector.x);
                    break;
                case GL_FLOAT_VEC2:
//                    glUniform2fv(info->location_,1,vector.Data());
                    glUniform2f(info->location_,vector.x,vector.y);
                    break;
                case GL_FLOAT_VEC3:
//                    glUniform3fv(info->location_,1,vector.Data());
                    glUniform3f(info->location_,vector.x,vector.y,vector.z);
                    break;
                case GL_FLOAT_VEC4:
//                    glUniform4fv(info->location_,1,vector.Data());
                    glUniform4f(info->location_,vector.x,vector.y,vector.z,vector.w);
                    break;
                default:
                    break;
            }
        }
    }
}

VertexBuffer* Graphics::getVertexBuffer(unsigned index) const
{
    return index < MAX_VERTEX_STREAMS? vertexBuffers_[index]:NULL;
}
//卷绕法
void Graphics::draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount)
{
    if(!vertexCount)
        return;
    prepareDraw();

    unsigned primitiveCount;
    GLenum glPrimitiveType;

    getGLPrimitiveType(vertexCount,type,primitiveCount,glPrimitiveType);

    glDrawArrays(glPrimitiveType,0,vertexCount);
}
//索引法绘制 GL是右手坐标系。
void Graphics::draw(PrimitiveType type, unsigned indexStart, unsigned indexCount,
                    unsigned minVertex, unsigned vertexCount)
{
    if (!indexCount || !indexBuffer_ || !indexBuffer_->getGPUObjectName())
        return;

    prepareDraw();

    unsigned indexSize = indexBuffer_->getIndexSize();
    unsigned primitiveCount;
    GLenum glPrimitiveType;

    getGLPrimitiveType(indexCount, type, primitiveCount, glPrimitiveType);
    GLenum indexType = indexSize == sizeof(unsigned short) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
    glDrawElements(glPrimitiveType, indexCount, indexType, reinterpret_cast<const GLvoid*>(indexStart * indexSize));
}

void Graphics::setVBO(unsigned object)
{
//    if(impl_->boundVBO_ != object)
//    {
//        LOGE("======bound VBO======");
    if(object)
        glBindBuffer(GL_ARRAY_BUFFER,object);
//        impl_ ->boundVBO_ = object;
//    }

}
//可以拥有多个顶点缓冲区，但是一个索引缓冲区,该部分，理解不到位，务必加深印象
void Graphics::prepareDraw()
{

    if(impl_->vertexBuffersDirty_)
    {
        glUseProgram(impl_->shaderProgram_->getGPUObjectName());
        for(unsigned i = MAX_VERTEX_STREAMS - 1; i < MAX_VERTEX_STREAMS; --i)
        {
            VertexBuffer* buffer = vertexBuffers_[i];
            if(!buffer || !buffer->getGPUObjectName() || !impl_->vertexAttributes_)
                continue;
            const vector<VertexElement>& elements = buffer ->getElements();//获取顶点数组的属性
            //遍历顶点属性
            for(vector<VertexElement>::const_iterator j = elements.begin();j != elements.end();++j)
            {
                const VertexElement& element = *j;//获取到顶点的属性结构体引用
                //迭代着色器顶点属性存储map,并查询到对应的顶点相关属性
                SN_Map<pair<char ,string>,unsigned>::const_iterator k =
                                                                            impl_->vertexAttributes_->find(make_pair((char)element.semantic_,element.index_));
                if(k != impl_->vertexAttributes_->end())
                {
                    //获取顶点数组属性（VBO）的句柄ID
                    unsigned location = k->second;
                    glEnableVertexAttribArray(location);
                    //获取顶点数组的偏移量
                    unsigned dataStart = element.offset_;

                    setVBO(buffer->getGPUObjectName());
                    glVertexAttribPointer(location,glElementComponents[element.type_],glElementTypes[element.type_],
                                          element.type_ == TYPE_UBYTE4_NORM ? GL_TRUE : GL_FALSE,buffer->getVertexSize(),
                                          reinterpret_cast<void*>(dataStart));// reinterpret_cast<void*>(dataStart) (const void *)(size_t)dataStart
                }
            }
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER,0);
//    impl_->vertexBuffersDirty_ = false;
}



GL_ShaderProgram* Graphics::getShaderProgram() const
{
    return impl_->shaderProgram_;
}


