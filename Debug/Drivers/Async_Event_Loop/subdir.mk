################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/Async_Event_Loop/AsyncEventLoop.cpp 

OBJS += \
./Drivers/Async_Event_Loop/AsyncEventLoop.o 

CPP_DEPS += \
./Drivers/Async_Event_Loop/AsyncEventLoop.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Async_Event_Loop/%.o Drivers/Async_Event_Loop/%.su Drivers/Async_Event_Loop/%.cyclo: ../Drivers/Async_Event_Loop/%.cpp Drivers/Async_Event_Loop/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Async_Event_Loop

clean-Drivers-2f-Async_Event_Loop:
	-$(RM) ./Drivers/Async_Event_Loop/AsyncEventLoop.cyclo ./Drivers/Async_Event_Loop/AsyncEventLoop.d ./Drivers/Async_Event_Loop/AsyncEventLoop.o ./Drivers/Async_Event_Loop/AsyncEventLoop.su

.PHONY: clean-Drivers-2f-Async_Event_Loop

