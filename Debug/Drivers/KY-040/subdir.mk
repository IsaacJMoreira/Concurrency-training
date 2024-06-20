################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/KY-040/KY040.cpp 

OBJS += \
./Drivers/KY-040/KY040.o 

CPP_DEPS += \
./Drivers/KY-040/KY040.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/KY-040/%.o Drivers/KY-040/%.su Drivers/KY-040/%.cyclo: ../Drivers/KY-040/%.cpp Drivers/KY-040/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-KY-2d-040

clean-Drivers-2f-KY-2d-040:
	-$(RM) ./Drivers/KY-040/KY040.cyclo ./Drivers/KY-040/KY040.d ./Drivers/KY-040/KY040.o ./Drivers/KY-040/KY040.su

.PHONY: clean-Drivers-2f-KY-2d-040

