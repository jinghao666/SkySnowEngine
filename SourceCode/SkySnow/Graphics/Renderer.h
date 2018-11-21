//
// Created by liuqian8 on 2018/10/24.
//

#pragma once

#include <vector>
#include "Object.h"
#include "ShaderVariation.h"
#include "GraphicsDefs.h"

class Geometry;
class Graphics;
class Material;
class Pass;
class Renderer: public Object
{
ENGINE_OBJECT(Renderer,Object);
public:

    explicit Renderer(Context* context);
    virtual ~Renderer();


    void onChanged(int width,int height);

    void Update(float timeStep);

    void Render();

private:
    void Initial();
    //重新加载着色器。
    void LoadShaders();
    //重新加载材质通道的着色器。如果有额外的着色器编译定义，则提供相关的批处理队列。
    void LoadPassShaders(Pass* pass,vector<ShaderVariation> vertexShaders,vector<ShaderVariation> pixlShaders);
    //创建轻体积几何
    void CreateGeometries();
};
