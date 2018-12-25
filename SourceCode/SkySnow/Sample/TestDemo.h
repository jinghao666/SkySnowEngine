/**
    * auther: liuqian
    * Date: 2018/10/28
    * https://github.com/SkySnowEngine/SkySnowEngine
*/
#pragma once
#include "Application.h"
class TestDemo : public Application
{
ENGINE_OBJECT(TestDemo,Object);
public:
    TestDemo(Context* context);
    ~TestDemo();

protected:
    virtual void createScence();
    virtual void renderOneFrame(float frameTime);

private:
    Batch*          uiBatch_;
    Material*       material_;
    Geometry*       geometry_;
    vector<float*>  vertexData_;
    unsigned int    vbo_;
    unsigned        gProgram;
    int             vertexSize_;
    float           vertexCount_;
    Graphics*       graphics_;
};
