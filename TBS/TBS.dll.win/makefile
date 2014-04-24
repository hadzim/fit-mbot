################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/json/subdir.mk
-include src/TBS/Task/subdir.mk
-include src/TBS/subdir.mk
-include bin/gcc-mingw-4.8.1/release/device-win/src/json/subdir.mk
-include bin/gcc-mingw-4.8.1/release/device-win/src/TBS/subdir.mk
-include bin/gcc-mingw-4.8.1/release/device-win/link-static/src/json/subdir.mk
-include bin/gcc-mingw-4.8.1/release/device-win/link-static/src/TBS/subdir.mk
-include bin/gcc-mingw-4.5.2/release/device-win/src/json/subdir.mk
-include bin/gcc-mingw-4.5.2/release/device-win/src/TBS/subdir.mk
-include bin/gcc-mingw-4.5.2/release/device-win/link-static/src/json/subdir.mk
-include bin/gcc-mingw-4.5.2/release/device-win/link-static/src/TBS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TBS.dll

# Tool invocations
TBS.dll: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MinGW C++ Linker'
	g++ -shared -Wl,--output-def=TBS.def -o "TBS.dll" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(LIBRARIES)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS) TBS.dll
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
