EXECUTABLE = bump

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/Counter.cpp \
        ../Classes/BgLayer.cpp \
        ../Classes/MenuLayer.cpp \
        ../Classes/MainLayer.cpp \
        ../Classes/FinishLayer.cpp \
        ../Classes/Ball.cpp 

COCOS_ROOT = ../../../..

SHAREDLIBS = -lcocos2d -lcocosdenshion -lcurl -lpthread
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

INCLUDES +=	 -I../ \
	-I../../ \
	-I../Classes \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I$(COCOS_ROOT)/extensions/ \
	-I$(COCOS_ROOT)/external/ \
	-I$(COCOS_ROOT)/external/chipmunk/include/chipmunk

STATICLIBS += \
	$(LIB_DIR)/libextension.a \
	$(LIB_DIR)/libbox2d.a \
	$(LIB_DIR)/libchipmunk.a
	
$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
