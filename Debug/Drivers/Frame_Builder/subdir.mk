################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/Frame_Builder/FrameBuilder.cpp 

OBJS += \
./Drivers/Frame_Builder/FrameBuilder.o 

CPP_DEPS += \
./Drivers/Frame_Builder/FrameBuilder.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Frame_Builder/%.o Drivers/Frame_Builder/%.su Drivers/Frame_Builder/%.cyclo: ../Drivers/Frame_Builder/%.cpp Drivers/Frame_Builder/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Frame_Builder

clean-Drivers-2f-Frame_Builder:
	-$(RM) ./Drivers/Frame_Builder/FrameBuilder.cyclo ./Drivers/Frame_Builder/FrameBuilder.d ./Drivers/Frame_Builder/FrameBuilder.o ./Drivers/Frame_Builder/FrameBuilder.su

.PHONY: clean-Drivers-2f-Frame_Builder

