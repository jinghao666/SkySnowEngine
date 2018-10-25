#include <jni.h>
#include <string>
#include "File.h"
static File* file = NULL;
extern "C"
JNIEXPORT jstring
JNICALL Java_android_skysnow_com_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    LOGI("data start");
    if(file = NULL)
        file = new File(NULL);
    std::string data = file->getStringFromFile("sdcard/lianpu/smoke.txt");
    LOGI("data:%s",data.c_str());
    LOGI("data size:%d",data.size());
    LOGI("data end");
    return env->NewStringUTF(hello.c_str());
}
