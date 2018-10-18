//
// Created by Administrator on 2018/10/1.
//
#pragma once

#include <cassert>
#include "Common.h"

class Context;
//
class TypeInfo
{
public:
	//typeName 是常量指针， 指向常量，能改变指向，不能改变指向的对象，只能通过原来的声明来改变
	TypeInfo(const char* typeName , const TypeInfo* baseTypeInfo);

	~TypeInfo();
	// 检查当前类型是否是指定类型
	bool isTypeOf(const TypeInfo* typeInfo) const;//不管对象是不是用const限定的都可以调用，但是函数内部不允许修改对象的成员（用mutable限定的成员除外）
	//模板方法
	template <typename  T> bool isTypeOf() const
	{
		return isTypeOf(T::getTypeInfoStatic());
	}

	string getType() const
	{
		return type_;
	}

	const string& getTypeName() const
	{
		return typeName_;
	}

	const TypeInfo* getBaseTypeInfo() const
	{
		return baseTypeInfo_;
	}

private:
	string type_;
	string typeName_;
	const TypeInfo* baseTypeInfo_;
};
//宏定义函数，避免了重复在子类中写这些虚函数方法
#define ENGINE_OBJECT(typeName,baseTypeName)\
        public:\
            typedef typeName ClassName;\
            typedef baseTypeName BaseClassName;\
            virtual string getType() const{ return getTypeInfoStatic()->getType();}\
            virtual const string& getTypeName() const { return getTypeInfoStatic()->getTypeName(); }\
            virtual const TypeInfo* getTypeInfo() const { return getTypeInfoStatic(); }\
            static string GetTypeStatic() { return getTypeInfoStatic()->getType(); }\
            static const string& GetTypeNameStatic() { return getTypeInfoStatic()->getTypeName(); }\
            static const TypeInfo* getTypeInfoStatic(){static const TypeInfo typeInfoStatic(#typeName,BaseClassName::getTypeInfoStatic()); return &typeInfoStatic;};

class Object
{
	friend class Context;
public:
	Object(Context* context);
	virtual ~Object();

	/// Return type hash.
	virtual string getType() const = 0;
	/// Return type name.
	virtual const string& getTypeName() const = 0;
	/// Return type info.
	virtual const TypeInfo* getTypeInfo() const = 0;

	/// Return type info static.
	static const TypeInfo* getTypeInfoStatic() { return 0; }

	Object* getSubsystem(string typeName) const;
	Context* getContext() const
	{
		return context_;
	}
	template <class T> T* getSubsystem() const;
protected:
	Context* context_;
private:

};

template <class T> T* Object::getSubsystem() const
{
	return static_cast<T*>(getSubsystem(T::GetTypeNameStatic()));
}

