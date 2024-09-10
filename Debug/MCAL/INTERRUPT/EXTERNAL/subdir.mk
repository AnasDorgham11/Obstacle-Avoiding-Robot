################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/INTERRUPT/EXTERNAL/EXTERNAL.c 

OBJS += \
./MCAL/INTERRUPT/EXTERNAL/EXTERNAL.o 

C_DEPS += \
./MCAL/INTERRUPT/EXTERNAL/EXTERNAL.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/INTERRUPT/EXTERNAL/%.o: ../MCAL/INTERRUPT/EXTERNAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


