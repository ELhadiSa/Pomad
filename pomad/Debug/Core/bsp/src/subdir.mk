################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/bsp/src/bsp.c 

OBJS += \
./Core/bsp/src/bsp.o 

C_DEPS += \
./Core/bsp/src/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/bsp/src/bsp.o: ../Core/bsp/src/bsp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I"C:/Users/pc/Documents/travail perso/pomad_remote/pomad/Core/bsp/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/bsp/src/bsp.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

