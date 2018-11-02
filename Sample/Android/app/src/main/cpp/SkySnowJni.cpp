#include <jni.h>
#include <string>
#include "TestDemo.h"
#include "Application.h"
#include "Context.h"

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_android_skysnow_com_myapplication_SkySnowBase_SkySnowNativeAPI_##method_name

#ifdef __cplusplus
extern "C" {
#endif

JNI_METHOD(jlong,createSkySnow)(JNIEnv *env,jobject)
{
    Context* context = new Context();
    Application* app = new (std::nothrow)TestDemo(context);
    if(app == NULL)
        return -1;
    app->initialize();
    return (uintptr_t)(app);
}

JNI_METHOD(jboolean,changeSkySnow)(JNIEnv *env,jobject,jlong classId,jint viewWidth,jint viewHeight)
{
    Application* app = ((Application*)classId);
    if(app == NULL)
        return false;
    app->onChange(viewWidth,viewHeight);
    return true;
}

JNI_METHOD(jboolean,drawOneFrameSkySnow)(JNIEnv *env,jobject,jlong classId)
{
    Application* app = ((Application*)classId);
    if(app == NULL)
        return false;
    app->drawFrame();
    return true;
}

JNI_METHOD(jboolean,releaseSkySnow)(JNIEnv *env,jobject,jlong classId)
{
    Application* app = ((TestDemo*)classId);
    if(app){
        delete app;
        app = NULL;
    }else{
        LOGE("Application  Pointer null！at SkySnowJni.cpp.");
    }
    return true;
}

#ifdef __cplusplus
}
#endif
