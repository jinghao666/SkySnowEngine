#include <jni.h>
#include <string>
#include "Application.h"
#include "Object.h"
extern "C"
JNIEXPORT jstring

JNICALL
Java_android_skysnow_com_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
