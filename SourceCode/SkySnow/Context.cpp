//
// Created by liuqian8 on 2018/10/12.
//
#include "Context.h"
#include "Object.h"
Context::~Context()

{
    subsystem_.clear();
    textureList_.clear();
}

void Context::registerSubsystem(Object* subsystem)
{
    if(!subsystem)
        return;
    subsystem_[subsystem->getType()] = subsystem;
}

void Context::setTextureId(string nameType, int textureId)
{
    if(nameType.size() == 0)
        return;
    textureList_[nameType] = textureId;
}

int Context::getTextureId(string name)
{
    SN_HashMap<string ,int >::const_iterator i = textureList_.find(name);
    if(i!=textureList_.end())
        return i->second;
    else
        return -1;
}

Object* Context::getSubsystem(string type) const
{
    SN_HashMap<string,Object*>::const_iterator i = subsystem_.find(type);
    if(i != subsystem_.end())
        return i ->second;
    else
        return 0;
}

void Context::removeSubsystem(string ObjectType)
{
    SN_HashMap<string , Object*>::iterator i = subsystem_.find(ObjectType);
    if(i != subsystem_.end())
        subsystem_.erase(i);
}