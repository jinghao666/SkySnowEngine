//
// Created by liuqian8 on 2018/10/18.
//
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
    if(renderer_){
        delete renderer_;
        renderer_ = NULL;
    }

    if(graphics_){
        delete graphics_;
        graphics_ = NULL;
    }

    if(file){
        delete file;
        file = NULL;
    }

}

bool Engine::initialize()
{
    //注册IO系统
    file = new File(context_);
    context_->registerSubsystem(file);
    //注册主渲染系统
    renderer_ = new Renderer(context_);
    context_->registerSubsystem(renderer_);
    //注册图形缓冲系统
    graphics_ = new Graphics(context_);
    context_->registerSubsystem(graphics_);

    renderer_ -> onCreate();
    initialized_ = true;
    return true;
}

void Engine::onChanged(int width, int height)
{
    renderer_->onChanged(width,height);
}

void Engine::runFrame(float frameTime)
{
    renderer_->onDrawFrame();
}