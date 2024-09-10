################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/CAR/_2_WHEELS/MOVEMENT/MOVEMENT.c 

OBJS += \
./HAL/CAR/_2_WHEELS/MOVEMENT/MOVEMENT.o 

C_DEPS += \
./HAL/CAR/_2_WHEELS/MOVEMENT/MOVEMENT.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/CAR/_2_WHEELS/MOVEMENT/%.o: ../HAL/CAR/_2_WHEELS/MOVEMENT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


