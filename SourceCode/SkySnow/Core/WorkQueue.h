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

    }

private:
    unsigned index_;
};

