################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Funcs.cpp \
../source/InputOkCancel.cpp \
../source/MainMenu.cpp \
../source/OkCancel.cpp \
../source/POptMenu.cpp \
../source/logic.cpp \
../source/main.cpp \
../source/n_network.cpp \
../source/network.cpp \
../source/s_player.cpp \
../source/session.cpp \
../source/statusbar.cpp \
../source/textbox.cpp \
../source/user_map.cpp 

OBJS += \
./source/Funcs.o \
./source/InputOkCancel.o \
./source/MainMenu.o \
./source/OkCancel.o \
./source/POptMenu.o \
./source/logic.o \
./source/main.o \
./source/n_network.o \
./source/network.o \
./source/s_player.o \
./source/session.o \
./source/statusbar.o \
./source/textbox.o \
./source/user_map.o 

CPP_DEPS += \
./source/Funcs.d \
./source/InputOkCancel.d \
./source/MainMenu.d \
./source/OkCancel.d \
./source/POptMenu.d \
./source/logic.d \
./source/main.d \
./source/n_network.d \
./source/network.d \
./source/s_player.d \
./source/session.d \
./source/statusbar.d \
./source/textbox.d \
./source/user_map.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


