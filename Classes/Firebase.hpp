#ifndef Firebase_h
#define Firebase_h

#include "base/ccConfig.h"
#include "jsapi.h"
#include "jsfriendapi.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif
#include "firebase/app.h"

void register_all_firebase_framework(JSContext* cx, JS::HandleObject obj);
firebase::App* firebase_app();

#endif /* Firebase_h */
