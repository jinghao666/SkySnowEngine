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

#define DEBUG 1
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
#include <map>
#include <string>
#include <ext/hash_map>
#include <ext/hash_set>
#include <list>
#define LOGI(...)  if(DEBUG) __android_log_print(ANDROID_LOG_INFO,SKYSNOW_LOG_TAG,__VA_ARGS__)
#define LOGE(...)  if(DEBUG) __android_log_print(ANDROID_LOG_ERROR,SKYSNOW_LOG_TAG,__VA_ARGS__)
        using namespace __gnu_cxx;
        namespace __gnu_cxx
        {
            template<> struct hash<const string>
            {
                size_t operator()(const string& s) const
                { return hash<const char*>()( s.c_str() ); } //__stl_hash_string
            };
            template<> struct hash<string>
            {
                size_t operator()(const string& s) const
                { return hash<const char*>()( s.c_str() ); }
            };
        }
#       define SN_Map      map
#       define SN_List      list
#       define SN_HashMap ::__gnu_cxx::hash_map
#       define SN_HashMultiMap ::__gnu_cxx::hash_multimap
#       define SN_HashSet ::__gnu_cxx::hash_set
#       define SN_HashMultiSet ::__gnu_cxx::hash_multiset
#elif PLATFORM == PLATFORM_IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#       include  <map>
#       include <list>
#       include <vector>
#if __has_include(<simd/simd.h>)
#ifndef WBSIMD
#define WBSIMD
#endif
#endif
#include <cstdio>
#define  LOGI(...)   if(DEBUG) printf(SKYSNOW_LOG_TAG,__VA_ARGS__)
#define  LOGE(...)   if(DEBUG) printf(SKYSNOW_LOG_TAG,__VA_ARGS__)
#       define SN_Map      map
#       define SN_List      list
#       define SN_HashMap ::std::unordered_map
#       define SN_HashMultiMap ::std::unordered_multimap
#       define SN_HashSet ::std::unordered_set
#       define SN_HashMultiSet :: std::unordered_multiset
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
#define  LOGI(...)  if(DEBUG) printf(SKYSNOW_LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  if(DEBUG) printf(SKYSNOW_LOG_TAG,__VA_ARGS__)
#endif
#include <cstdint>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <string.h>