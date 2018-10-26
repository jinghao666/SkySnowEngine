//
// Created by liuqian8 on 2018/10/26.
//

#pragma once

#include "Application.h"
#include "Context.h"

class RenderEntry
{
public:
    RenderEntry(Context* context);

    virtual ~RenderEntry();

    void onCreate();

    void onChanged(int width,int height);

    void onDraeFrame();

    template <class T> void createApplication()
    {
        exampleObject_ = new T(context_);
    }

    template <class T> T* getApplication()
    {
        return static_cast<T*>(exampleObject_);
    }

private:
    Context* context_;
    Application* exampleObject_;
};
