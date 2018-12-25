/**
    * auther: liuqian
    * Date: 2018/10/28
    * https://github.com/SkySnowEngine/SkySnowEngine
*/
#include "WorkQueue.h"
#include "Thread.h"
#include "TestDemo.h"
#include <vector>
#include "Geometry.h"
#include "VertexBuffer.h"
#include "Material.h"
using namespace std;
TestDemo::TestDemo(Context *context) :
Application(context)
{
}

TestDemo::~TestDemo()
{

}

void TestDemo::createScence()
{
    LOGI("Child is create scence!");

    uiBatch_ = new Batch();

    uiBatch_->addQuad(Rect(-1,1,1,-1),&vertexData_,vertexCount_,vertexSize_);
    material_ = new Material(context_);
    gProgram = material_->setShaderVariation("ui_vertices.glsl","ui_frag.glsl");

    geometry_ = new Geometry(context_);
    VertexBuffer* vertexBuffer = new VertexBuffer(context_);

    vertexBuffer ->setSize(vertexCount_,vertexSize_);
    vertexBuffer->setData(vertexData_[0]);

    geometry_->setVertexBuffer(vertexBuffer);
    graphics_ = getSubsystem<Graphics>();
    context_->registerSubsystem(geometry_);
}

void TestDemo::renderOneFrame(float frameTime)
{
    geometry_->draw(graphics_);
}

