//
// Created by liuqian8 on 2018/10/1.
//

#pragma once
#include "Common.h"
using namespace std;
class Graphics;
union GPUObjectHandle
{
    unsigned name_;
};

class GPUObject
{
public:
    GPUObject(Graphics* graphics);
    unsigned getGPUObjectName();

protected:
    GPUObjectHandle object_;
    Graphics* graphics_;
};
