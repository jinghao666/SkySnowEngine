//
// Created by liuqian8 on 2018/9/30.
//

#pragma once

#include "Common.h"

enum SNobjectType:uint8_t
{
    BUFFER,
    COMMAND_BUFFER,
    FRAMEBUFFER,
    OCCLUSION_QUERY,
    SAMPLER,
    SHADER,
    TEXTURE,
    TEXTURE_VIEW,
    SHADER_PROGRAM,
    FENCE,
    RENDER_GRAPH,
    COUNT
};
//base of all graphics objects.
class SNObject
{
public:

    SNObject(SNobjectType type,string name);
    virtual ~SNObject();

    uint64_t  getUuid() const
    {
        return m_uuid;
    }

    SNobjectType  getType() const
    {
        return m_type;
    }

private:
    uint64_t m_uuid;
    SNobjectType m_type;
};
