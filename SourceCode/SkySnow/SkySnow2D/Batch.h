//
// Created by liuqian8 on 2018/12/25.
//

#pragma once

#include <string>
#include "Rect.h"

using namespace std;

class Batch
{
public:

    Batch();

    ~Batch();

    void addQuad(const Rect& rect,vector<float*>* vertexData,float& vertexCount,int& vertexSize);

private:
    //除去RGB顶点颜色数据，该数组是24个float类型的数据
    float* dataArry_;
    float* indexArry_;
};
