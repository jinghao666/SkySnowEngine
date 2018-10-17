//
// Created by liuqian8 on 2018/10/12.
//

#pragma once

#include "Common.h"
class Context
{

    friend class Object;
public:
    Context()
    {
        tempId_ = 0;
    }
    ~Context();

    void setTextureId(string nameType, int textureId) ;

    int getTextureId(string name) ;

    void registerSubsystem(Object* subsystem);

    Object* getSubsystem(string type) const;

    void removeSubsystem(string ObjectType);

    template <class T> T* getSubsystem() const;


protected:
    SN_HashMap<string ,Object*> subsystem_;
    SN_HashMap<string,int>   textureList_;
    int tempId_;
};

template <class T> T* Context::getSubsystem() const
{
    return static_cast<T*> (getSubsystem(T::GetTypeNameStatic()));
}
