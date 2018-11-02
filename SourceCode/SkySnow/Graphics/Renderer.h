//
// Created by liuqian8 on 2018/10/24.
//

#pragma once

#include "Object.h"

class Renderer: public Object
{
ENGINE_OBJECT(Renderer,Object);
public:

    Renderer(Context* context);
    virtual ~Renderer();

    void onCreate();
    void onChanged(int width,int height);
    void onDrawFrame();
};
