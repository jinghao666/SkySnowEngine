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
public:
    virtual void createScence();

};
