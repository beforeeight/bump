################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/zhangchen/development/cocos2d-x-2.2.3/samples/Cpp/HelloCpp/Classes/AppDelegate.cpp \
/home/zhangchen/development/cocos2d-x-2.2.3/samples/Cpp/HelloCpp/Classes/HelloWorldScene.cpp 

OBJS += \
./Classes/AppDelegate.o \
./Classes/HelloWorldScene.o 

CPP_DEPS += \
./Classes/AppDelegate.d \
./Classes/HelloWorldScene.d 


# Each subdirectory must supply rules for building sources it contributes
Classes/AppDelegate.o: /home/zhangchen/development/cocos2d-x-2.2.3/samples/Cpp/HelloCpp/Classes/AppDelegate.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I../../Classes -I../../../ -I../../../../../cocos2dx -I../../../../../cocos2dx/include -I../../../../../cocos2dx/kazmath/include -I../../../../../cocos2dx/platform/linux -I../../../../../cocos2dx/platform/third_party/linux -I../../../../../CocosDenshion/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Classes/HelloWorldScene.o: /home/zhangchen/development/cocos2d-x-2.2.3/samples/Cpp/HelloCpp/Classes/HelloWorldScene.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I../../Classes -I../../../ -I../../../../../cocos2dx -I../../../../../cocos2dx/include -I../../../../../cocos2dx/kazmath/include -I../../../../../cocos2dx/platform/linux -I../../../../../cocos2dx/platform/third_party/linux -I../../../../../CocosDenshion/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


