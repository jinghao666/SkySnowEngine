/**
    * auther: liuqian
    * Date: 2018/10/28
    * https://github.com/SkySnowEngine/SkySnowEngine
*/
#include "WorkQueue.h"
#include "Thread.h"
#include "TestDemo.h"
#include <vector>
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

}

