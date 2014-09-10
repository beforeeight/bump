LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := bump_shared

LOCAL_MODULE_FILENAME := libbump

LOCAL_SRC_FILES := bump/main.cpp \
	../../Classes/AppDelegate.cpp \
        ../../Classes/Counter.cpp \
        ../../Classes/BgLayer.cpp \
        ../../Classes/MenuLayer.cpp \
        ../../Classes/MainLayer.cpp \
        ../../Classes/FinishLayer.cpp \
        ../../Classes/Ball.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)
$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
