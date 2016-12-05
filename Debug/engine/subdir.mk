################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../engine/golem.c \
../engine/golemblock.c \
../engine/golembuilderclass.c \
../engine/golembuilderextern.c \
../engine/golemclass.c \
../engine/golemcontext.c \
../engine/golemdebugobject.c \
../engine/golemfunc.c \
../engine/golemparser.c \
../engine/golemsentence.c \
../engine/golemvm.c 

OBJS += \
./engine/golem.o \
./engine/golemblock.o \
./engine/golembuilderclass.o \
./engine/golembuilderextern.o \
./engine/golemclass.o \
./engine/golemcontext.o \
./engine/golemdebugobject.o \
./engine/golemfunc.o \
./engine/golemparser.o \
./engine/golemsentence.o \
./engine/golemvm.o 

C_DEPS += \
./engine/golem.d \
./engine/golemblock.d \
./engine/golembuilderclass.d \
./engine/golembuilderextern.d \
./engine/golemclass.d \
./engine/golemcontext.d \
./engine/golemdebugobject.d \
./engine/golemfunc.d \
./engine/golemparser.d \
./engine/golemsentence.d \
./engine/golemvm.d 


# Each subdirectory must supply rules for building sources it contributes
engine/%.o: ../engine/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c11 -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


