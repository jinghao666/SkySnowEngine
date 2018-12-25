//
// Created by liuqian8 on 2018/12/25.
//
#include "Batch.h"

Batch::Batch()
{
    //除去RGB顶点颜色数据，该数组是24个float类型的数据
    dataArry_ = new float[24];
}

Batch::~Batch()
{
    if(dataArry_)
    {
        delete[] dataArry_;
        dataArry_ = nullptr;
    }

}
/*2DUV坐标的在OpenGL 当中的规定
 *    T方向(竖)
 *      (0 ,1)           (1,1)
 *
 *      (0 ,0)           (1,0)   S方向（横）
 */
//组织顶点数据（包括顶点坐标数据，UV坐标数据），以三角形卷绕法进行组装
//offest 为 2 * sizeof(float)
void Batch::addQuad(const Rect& rect,vector<float*>* vertexData,float& vertexCount,int& vertexSize)
{
    dataArry_[0] = rect.left();
    dataArry_[1] = rect.top();
    dataArry_[2] = 0;
    dataArry_[3] = 1;

    dataArry_[4] = rect.left();
    dataArry_[5] = rect.bottom();
    dataArry_[6] = 0;
    dataArry_[7] = 0;

    dataArry_[8]  = rect.right();
    dataArry_[9]  = rect.bottom();
    dataArry_[10] = 1;
    dataArry_[11] = 0;

    dataArry_[12] = rect.left();
    dataArry_[13] = rect.top();
    dataArry_[14] = 0;
    dataArry_[15] = 1;

    dataArry_[16] = rect.right();
    dataArry_[17] = rect.bottom();
    dataArry_[18] = 1;
    dataArry_[19] = 0;

    dataArry_[20] = rect.right();
    dataArry_[21] = rect.top();
    dataArry_[22] = 1;
    dataArry_[23] = 1;
    vertexCount = 24;
    vertexSize = 4 * sizeof(float);
    vertexData->push_back(dataArry_);
}