//
// Created by liuqian8 on 2018/10/1.
//

#include "GPUObject.h"

GPUObject::GPUObject(Graphics *graphics):
        graphics_(graphics)
{
    object_.name_ = 0;
}

unsigned GPUObject::getGPUObjectName()
{
    return object_.name_;
}