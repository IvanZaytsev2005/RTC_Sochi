################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/Encoder.c \
../Application/User/Core/Func.c \
C:/STM32/Projects/RTC_Sochi/Sochi/Core/Src/main.c \
../Application/User/Core/stm32f4xx_hal_msp.c \
../Application/User/Core/stm32f4xx_it.c \
../Application/User/Core/system_stm32f4xx.c 

OBJS += \
./Application/User/Core/Encoder.o \
./Application/User/Core/Func.o \
./Application/User/Core/main.o \
./Application/User/Core/stm32f4xx_hal_msp.o \
./Application/User/Core/stm32f4xx_it.o \
./Application/User/Core/system_stm32f4xx.o 

C_DEPS += \
./Application/User/Core/Encoder.d \
./Application/User/Core/Func.d \
./Application/User/Core/main.d \
./Application/User/Core/stm32f4xx_hal_msp.d \
./Application/User/Core/stm32f4xx_it.d \
./Application/User/Core/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/%.o Application/User/Core/%.su: ../Application/User/Core/%.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../../Core/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/STM32/Projects/RTC_Sochi/Sochi/Core/Src" -I"C:/STM32/Projects/RTC_Sochi/Sochi/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/main.o: C:/STM32/Projects/RTC_Sochi/Sochi/Core/Src/main.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../../Core/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/STM32/Projects/RTC_Sochi/Sochi/Core/Src" -I"C:/STM32/Projects/RTC_Sochi/Sochi/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core

clean-Application-2f-User-2f-Core:
	-$(RM) ./Application/User/Core/Encoder.d ./Application/User/Core/Encoder.o ./Application/User/Core/Encoder.su ./Application/User/Core/Func.d ./Application/User/Core/Func.o ./Application/User/Core/Func.su ./Application/User/Core/main.d ./Application/User/Core/main.o ./Application/User/Core/main.su ./Application/User/Core/stm32f4xx_hal_msp.d ./Application/User/Core/stm32f4xx_hal_msp.o ./Application/User/Core/stm32f4xx_hal_msp.su ./Application/User/Core/stm32f4xx_it.d ./Application/User/Core/stm32f4xx_it.o ./Application/User/Core/stm32f4xx_it.su ./Application/User/Core/system_stm32f4xx.d ./Application/User/Core/system_stm32f4xx.o ./Application/User/Core/system_stm32f4xx.su

.PHONY: clean-Application-2f-User-2f-Core

