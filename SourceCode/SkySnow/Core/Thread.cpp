//
// Created by liuqian8 on 2018/11/2.
//
#include "Thread.h"
static void* threadFunctionStatic(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    thread->threadFunction();
    pthread_exit((void*)0);
    return 0;
}

ThreadID Thread::mainThreadID;

Thread::Thread():
        handle_(NULL),
        shouldRun_(false)
{

}

Thread::~Thread()
{
    stop();
}

bool Thread::run()
{
    if(handle_)
        return false;
    shouldRun_ = true;

    handle_ = new pthread_t;
    pthread_attr_t type;
    pthread_attr_init(&type);
    pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);
    pthread_create((pthread_t*)handle_, &type, threadFunctionStatic,this);
    return  handle_ != nullptr;
}

void Thread::stop()
{
    if(!handle_)
        return;
    shouldRun_ = false;

    pthread_t* thread = (pthread_t*)handle_;
    if (thread)
        pthread_join(*thread, 0);
    delete thread;
    handle_ = nullptr;
}

void Thread::setPriority(int priority)
{
    pthread_t* thread = (pthread_t*)handle_;
    struct sched_param sched;
    if (thread)
        pthread_setschedparam(*thread,priority,&sched);
}

void Thread::setMainThread()
{
    mainThreadID = getCurrentThreadID();
}

ThreadID Thread::getCurrentThreadID()
{
    return pthread_self();
}

bool Thread::isMainThread()
{
    return getCurrentThreadID() == mainThreadID;
}

void Thread::sleep(int sec, int nsec)
{
    struct timespec sleepTime;
    struct timespec returnTime;
    sleepTime.tv_sec = sec;
    sleepTime.tv_nsec = nsec;
    nanosleep(&sleepTime, &returnTime);
}

long long Thread::getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
}

