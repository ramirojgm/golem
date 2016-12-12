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
../engine/golemcompiled.c \
../engine/golemcontext.c \
../engine/golemdebugobject.c \
../engine/golemexpresion.c \
../engine/golemfunc.c \
../engine/golemjit.c \
../engine/golemparser.c \
../engine/golemsentence.c 

OBJS += \
./engine/golem.o \
./engine/golemblock.o \
./engine/golembuilderclass.o \
./engine/golembuilderextern.o \
./engine/golemclass.o \
./engine/golemcompiled.o \
./engine/golemcontext.o \
./engine/golemdebugobject.o \
./engine/golemexpresion.o \
./engine/golemfunc.o \
./engine/golemjit.o \
./engine/golemparser.o \
./engine/golemsentence.o 

C_DEPS += \
./engine/golem.d \
./engine/golemblock.d \
./engine/golembuilderclass.d \
./engine/golembuilderextern.d \
./engine/golemclass.d \
./engine/golemcompiled.d \
./engine/golemcontext.d \
./engine/golemdebugobject.d \
./engine/golemexpresion.d \
./engine/golemfunc.d \
./engine/golemjit.d \
./engine/golemparser.d \
./engine/golemsentence.d 


# Each subdirectory must supply rules for building sources it contributes
engine/%.o: ../engine/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c11 -I/usr/lib/i386-linux-gnu/glib-2.0/includ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


