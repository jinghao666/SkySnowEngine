#include <jni.h>
#include <string>
#include "File.h"

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_android_skysnow_com_myapplication_SkySnowNativeAPI_##method_name

static File* file = NULL;
#ifdef __cplusplus
extern "C" {
#endif

JNI_METHOD(jstring,stringFromJNI)(JNIEnv *env,jobject) {
    std::string hello = "Hello from C++";
    LOGI("data start");
    if(file = NULL)
        file = new File(NULL);
    std::string data = file->getStringFromFile("sdcard/lianpu/smoke.txt");
    LOGI("data:%s",data.c_str());
    LOGI("data size:%d",data.size());
    LOGI("data end");
    return env->NewStringUTF(data.c_str());
}

#ifdef __cplusplus
}
#endif
