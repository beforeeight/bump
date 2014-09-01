################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include obj/release/Classes/subdir.mk
-include obj/release/subdir.mk
-include obj/debug/Classes/subdir.mk
-include obj/debug/subdir.mk
-include Classes/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pre-build main-build

# Main-build Target
main-build: HelloCpp

# Tool invocations
HelloCpp: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L../../../../../cocos2dx/proj.linux/Debug -L../../../../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib -L../../../../../CocosDenshion/proj.linux/Debug -L../../../../../CocosDenshion/third_party/fmod/api/lib -o bin/"HelloCpp" $(OBJS) $(USER_OBJS) $(LIBS) -Wl,-rpath,/home/zhangchen/development/cocos2d-x-2.2.3/samples/Cpp/HelloCpp/proj.linux/../../../../cocos2dx/proj.linux/Debug -Wl,-rpath,/home/zhangchen/development/cocos2d-x-2.2.3/samples/Cpp/HelloCpp/proj.linux/../../../../CocosDenshion/proj.linux/Debug -Wl,-rpath,/home/zhangchen/development/cocos2d-x-2.2.3/samples/Cpp/HelloCpp/proj.linux/../../../../CocosDenshion/third_party/fmod/api/lib  -Wl,-rpath,../../../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) HelloCpp
	-@echo ' '

pre-build:
	-mkdir -p bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

-include ../makefile.targets
