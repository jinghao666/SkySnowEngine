//
// Created by liuqian on 2018/11/2.
//

#pragma once

#include "Common.h"
#include "Thread.h"

class WorkerThread: public Thread
{
public:
    WorkerThread()
    {

    }

    void threadFunction() override
    {
        while (1)
        {
            LOGE("是否在运行线程。");
        }

    }

private:
    unsigned index_;
};

