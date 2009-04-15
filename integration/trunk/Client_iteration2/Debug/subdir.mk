################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DPlaya.cpp \
../logic.cpp \
../network.cpp \
../session.cpp 

OBJS += \
./DPlaya.o \
./logic.o \
./network.o \
./session.o 

CPP_DEPS += \
./DPlaya.d \
./logic.d \
./network.d \
./session.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


