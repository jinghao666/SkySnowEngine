//
// Created by liuqian8 on 2018/10/18.
//

#pragma once
#include "Object.h"
#include "Graphics.h"
#include "File.h"
class Engine: public Object
{
    ENGINE_OBJECT(Engine,Object);
public:
    Engine(Context* context);
    ~Engine();

    bool initialize();

    void runFrame();

    void onChanged(int width,int height);

private:
    bool initialized_ ;
//    Renderer* renderer_;
    File* file;
    Graphics* graphics_;
};
