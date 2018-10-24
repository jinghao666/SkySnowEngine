
#include "Application.h"
//#include "Context.h"
#include "Engine.h"
Application::Application(Context *context) :
        Object(context),
        initialized_(false),
        count_(0),
        fps_(0),
        frameTime_(0)
{
    engine_ = new Engine(context_);
}

Application::~Application()
{
    delete engine_;
}

bool Application::initialize()
{
    startTime_ = getCurrentTime();
    engine_->initialize();
    createScence();
    return true;
}

void Application::onChange(int width, int height)
{
    engine_->onChanged(width,height);
    windowSizeChange(width,height);
}

void Application::drawFrame()
{
    if(count_ == 9)
    {
        endTime_ = getCurrentTime();
        frameTime_ = (endTime_ - startTime_)/10;
        fps_ = 1000/frameTime_;
        LOGE("fps_   :%f\n",fps_);
        LOGE("Render One Frame Time:%f\n",frameTime_);
        count_ = 0;
        startTime_ = endTime_;
    }
    count_ = (count_ + 1) % 10;
    engine_ ->runFrame();
    render(frameTime_);
}

long long Application::getCurrentTime()
{
    gettimeofday(&tv,NULL);
    return (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
}
