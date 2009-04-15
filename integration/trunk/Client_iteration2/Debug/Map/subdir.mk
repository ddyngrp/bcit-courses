################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Map/init.cpp \
../Map/statusbar.cpp \
../Map/user_map.cpp 

OBJS += \
./Map/init.o \
./Map/statusbar.o \
./Map/user_map.o 

CPP_DEPS += \
./Map/init.d \
./Map/statusbar.d \
./Map/user_map.d 


# Each subdirectory must supply rules for building sources it contributes
Map/%.o: ../Map/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


