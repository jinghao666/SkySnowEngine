//
// Created by liuqian8 on 2018/11/2.
//

#pragma once
#include <pthread.h>

using ThreadID = unsigned ;

class Thread
{
public:
    //构造方法
    Thread();
    //析构方法
    virtual ~Thread();
    //在线程内运行的函数
    virtual void threadFunction() = 0;
    //开始运行的线程，如果线程已经运行或不能创建线程，则返回false
    bool run();
    //将运行的标志设置为false，并等待线程完成
    void stop();
    //设置线程的优先级
    void setPriority(int priority);
    //返回线程是否存在
    bool isStarted() const { return handle_ != NULL;}
    //设置当前的线程到主线程里面
    static void setMainThread();
    //返回当前线程的id
    static ThreadID getCurrentThreadID();
    //是否返回主线程运行
    static bool isMainThread();
    //线程休眠
    void sleep(int sec,int nsec);
    //获取当前时间
    long long getCurrentTime();
protected:
    void* handle_;
    //线程运行的标志位
    volatile bool shouldRun_;
    //主线程的线程id
    static ThreadID mainThreadID;
};
