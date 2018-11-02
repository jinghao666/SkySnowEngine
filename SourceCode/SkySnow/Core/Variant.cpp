//
// Created by liuqian8 on 2018/10/22.
//

#include "Variant.h"
#include "vec4.hpp"
#include "vec2.hpp"

void Variant::setType(VariantType newType)
{
    if (type_ == newType)
        return;
    type_ = newType;
    switch (type_)
    {

    }
}

template <> int Variant::Get<int>() const
{
    return GetInt();
}

template <> unsigned Variant::Get<unsigned>() const
{
    return GetUInt();
}

template <> long long Variant::Get<long long>() const
{
    return GetInt64();
}

template <> bool Variant::Get<bool>() const
{
    return GetBool();
}

template <> float Variant::Get<float>() const
{
    return GetFloat();
}

template <> double Variant::Get<double>() const
{
    return GetDouble();
}

template <> const glm::vec2& Variant::Get<const glm::vec2&>() const
{
    return GetVector2();
}

template <> const glm::vec4& Variant::Get<const glm::vec4&>() const
{
    return GetVector4();
}

template <> glm::vec2 Variant::Get<glm::vec2>() const
{
    return GetVector2();
}

template <> glm::vec4 Variant::Get<glm::vec4>() const
{
    return GetVector4();
}