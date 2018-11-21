//
// Created by liuqian8 on 2018/10/1.
//
#pragma once

#include "Variant.h"
#include "Object.h"
#include "ShaderVariation.h"

class IndexBuffer;
class VertexBuffer;
class GL_GraphicsImpl;
class GL_ShaderProgram;
class Graphics: public Object
{
    ENGINE_OBJECT(Graphics,Object);
public:
    Graphics(Context* context);
    virtual ~Graphics();
    void SetShaders(ShaderVariation* vs,ShaderVariation* fs);
    void setIndexBuffer(IndexBuffer* buffer);
    void setVertexBuffer(VertexBuffer* vertexBuffer);
    bool setVertexBuffers(const vector<VertexBuffer*>& buffers, unsigned instanceOffset = 0);
    VertexBuffer* getVertexBuffer(unsigned index)const;
    void setShaderParameter(string param, const Variant& value);
    /// Set shader float constant.
    void setShaderParameter(string parm,float value);
    /// Set shader integer constant.
    void setShaderParameter(string param,int value);
    /// Set shader boolean constant.
    void setShaderParameter(string param,bool value);
    /// Set shader 2D vector constant.
    void setShaderParameter(string param,const glm::vec2& vector);
    ///Set shader 4D vector constant.
    void setShaderParamter(string param, const glm::vec4& vector);
    void setVBO(unsigned object);
    //卷绕法
    void draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount);
    //索引法绘制 GL是右手坐标系。
    void draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex,
              unsigned vertexCount);

    GL_ShaderProgram* getShaderProgram() const;

private:
    void ResetCachedState();//reset cached rendering state

    void prepareDraw();
    ShaderVariation* vertexShader_;
    ShaderVariation* fragShader_;
    IndexBuffer* indexBuffer_;
//    VertexBuffer* vertexBuffer_;
    VertexBuffer* vertexBuffers_[MAX_VERTEX_STREAMS];
    GL_GraphicsImpl* impl_;
};
