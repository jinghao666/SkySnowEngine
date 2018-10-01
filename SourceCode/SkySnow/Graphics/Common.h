//
// Created by liuqian8 on 2018/9/30.
//
//Window  不太熟悉头文件，等到基础库写完了，在移植的时候进行添加   这件事情，Calence会去处理
#pragma once

#define PLATFORM_UNKOW 0
#define PLATFORM_ANDROID 1
#define PLATFORM_IOS 2
#define PLATFORM_WINDOW 3
#define PLATFORM_LINUX 4

#define DEBUG 0
#define PLATFORM PLATFORM_UNKOW

#include <string>
using namespace std;

#if defined(__ANDROID__) || defined(ANDROID)
#undef  PLATFORM
#define PLATFORM PLATFORM_ANDROID
#define GLSL_USE_ANDROID_OES 1
#define GLSL_SET_PRECISION 1
#elif defined(__APPLE__)
#undef  PLATFORM
#define PLATFORM PLATFORM_IOS
#define GLSL_SET_PRECISION 1
#elif defined(LINUX) || defined(__LINUX) || defined(__LINUX__) || defined(linux) || defined(__unix__)
#undef  PLATFORM
#define PLATFORM PLATFORM_LINUX
#endif

#define  SKYSNOW_LOG_TAG    "SkySnow:"

#if PLATFORM == PLATFORM_ANDROID
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2.h>
#include <android/log.h>
#define  LOGI(...)  if(DEBUG)__android_log_print(ANDROID_LOG_INFO,SKYSNOW_LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  if(DEBUG)__android_log_print(ANDROID_LOG_ERROR,SKYSNOW_LOG_TAG,__VA_ARGS__)
#elif PLATFORM == PLATFORM_IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#if __has_include(<simd/simd.h>)
#ifndef WBSIMD
#define WBSIMD
#endif
#endif
#include <cstdio>
#define  LOGI(...)   if(DEBUG)printf(SKYSNOW_LOG_TAG,__VA_ARGS__)
#define  LOGE(...)   if(DEBUG)printf(SKYSNOW_LOG_TAG,__VA_ARGS__)
#endif

#if PLATFORM == PLATFORM_LINUX
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <string>
#include <cstdio>
#include <algorithm>
#define  LOGI(...)  if(DEBUG)printf(SKYSNOW_LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  if(DEBUG)printf(SKYSNOW_LOG_TAG,__VA_ARGS__)
#endif
#include <cstdint>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <string.h>

//uint_fast32_t
const uint64_t MAX_SN_OBJECT_NAME_LENGTH = 15;
class SNBaseInitInfo
{
public:
    SNBaseInitInfo(string name)
    {

    }

    void setName(string name)
    {
        memset(&m_name[0],0, sizeof(m_name));
        if(name.size() > 0)
        {
            memcpy(&m_name[0],&name[0],name.size() + 1);
        }
    }

private:
    char m_name[MAX_SN_OBJECT_NAME_LENGTH + 1];
};