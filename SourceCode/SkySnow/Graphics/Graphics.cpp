//
// Created by liuqian8 on 2018/10/10.
//
#include "Graphics.h"

void Graphics::setShaderParameter(string param, const Variant &value)
{
    switch (value.getType())
    {
        case VAR_BOOL:
            setShaderParameter(param,value.GetBool());
            break;
        case VAR_INT:
            setShaderParameter(param,value.GetInt());
            break;
        case VAR_FLOAT:
        case VAR_DOUBLE:
            setShaderParameter(param,value.GetFloat());
            break;
        case VAR_VECTOR2:
            setShaderParameter(param,value.GetVector2());
            break;
        case VAR_VECTOR4:
            setShaderParamter(param,value.GetVector4());
        default:
            break;
    }
}