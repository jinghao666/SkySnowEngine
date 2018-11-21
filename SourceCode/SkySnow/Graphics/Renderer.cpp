//
// Created by liuqian8 on 2018/10/24.
//
#include "Renderer.h"

Renderer::Renderer(Context *context):
        Object(context)
{
    Initial();
}

Renderer::~Renderer()
{

}

void Renderer::Initial()
{

}

void Renderer::onChanged(int width, int height)
{

}

void Renderer::Update(float timeStep)
{

}

void Renderer::Render()
{

}


void Renderer::LoadShaders()
{
    LOGI("Reloading shaders.");

}

void Renderer::CreateGeometries()
{

}