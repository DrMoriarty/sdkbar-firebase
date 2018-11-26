#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import <Foundation/Foundation.h>
#endif
#include "Firebase.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/js_manual_conversions.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <sstream>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "utils/PluginUtils.h"

static firebase::App* app_ptr = NULL;

static void printLog(const char* str) {
    CCLOG("%s", str);
}

firebase::App* firebase_app()
{
    return app_ptr;
}

///////////////////////////////////////
//
//  Plugin Init
//
///////////////////////////////////////

static bool jsb_firebase_inited(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_admob_inited");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    if(argc == 0) {
        if(app_ptr != NULL) {
            rec.rval().set(JSVAL_TRUE);
        } else {
            rec.rval().set(JSVAL_FALSE);
        }
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        rec.rval().set(JSVAL_FALSE);
        return false;
    }
}

static void firebase_init()
    printLog("[Firebase] Init plugin");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // Initialize Firebase for Android.
    app_ptr = firebase::App::Create(firebase::AppOptions(), cocos2d::JniHelper::getEnv(), cocos2d::JniHelper::getActivity());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // Initialize Firebase for iOS.
    app_ptr = firebase::App::Create(firebase::AppOptions());
#endif
}

///////////////////////////////////////
//
//  Register JS API
//
///////////////////////////////////////

void register_all_admob_framework(JSContext* cx, JS::HandleObject obj) {
    printLog("[Firebase] register js interface");
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "firebase", &ns);

    JS_DefineFunction(cx, ns, "is_inited", jsb_firebase_inited, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    firebase_init();
}
