//
// Created by liuqian8 on 2018/10/26.
//

#include "RenderEntry.h"

RenderEntry::RenderEntry(Context *context):
        context_(context)
{

}

void RenderEntry::onCreate()
{
    exampleObject_ ->initialize();
}

void RenderEntry::onChanged(int width, int height)
{
    exampleObject_->onChange(width,height);
}

void RenderEntry::onDraeFrame()
{
    exampleObject_->drawFrame();
}

RenderEntry::~RenderEntry()
{
    delete  exampleObject_;
}