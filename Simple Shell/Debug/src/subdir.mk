################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Simple\ Shell.c 

OBJS += \
./src/Simple\ Shell.o 

C_DEPS += \
./src/Simple\ Shell.d 


# Each subdirectory must supply rules for building sources it contributes
src/Simple\ Shell.o: ../src/Simple\ Shell.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Simple Shell.d" -MT"src/Simple\ Shell.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


