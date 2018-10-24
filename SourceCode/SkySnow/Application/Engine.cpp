//
// Created by liuqian8 on 2018/10/18.
//

//#include "File.h"
#include "Engine.h"
#include "Context.h"

Engine::Engine(Context *context) :
        Object(context),
        initialized_(false)
{
    context_->registerSubsystem(this);
}

Engine::~Engine()
{
//    delete renderer_;
    delete graphics_;
//    delete file;
}

bool Engine::initialize()
{
    //注册IO系统
//    file = new File(context_);
//    context_->registerSubsystem(file);
    //注册主渲染系统
//    renderer_ = new Renderer(context_);
//    context_->registerSubsystem(renderer_);
    //注册图形缓冲系统
    graphics_ = new Graphics(context_);
    context_->registerSubsystem(graphics_);

//    renderer_ -> onCreate();
    initialized_ = true;
    return true;
}

void Engine::onChanged(int width, int height)
{
//    renderer_->onChanged(width,height);
}

void Engine::runFrame()
{
//    renderer_->onDrawFrame();
}