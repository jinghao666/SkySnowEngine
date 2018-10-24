#pragma once

#include "Engine.h"
#include "Object.h"
#include <sys/time.h>


class Application : public Object
{
ENGINE_OBJECT(Application,Object);
public:
    Application(Context* context);
    ~Application();

    bool  initialize();

    void onChange(int width,int height);

    void drawFrame();

    virtual void createScence(){};

    virtual void windowSizeChange(int width,int height){};

    virtual void render(float frameTime){};
protected:
    Engine* engine_;

private:
    long long getCurrentTime();
    bool initialized_;
    long long startTime_;
    long long  endTime_;
    float frameTime_;
    int count_;
    float fps_;
    struct timeval tv;
};
