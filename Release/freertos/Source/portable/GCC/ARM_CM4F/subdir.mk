################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/Source/portable/GCC/ARM_CM4F/fsl_tickless_lptmr.c \
../freertos/Source/portable/GCC/ARM_CM4F/fsl_tickless_systick.c \
../freertos/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./freertos/Source/portable/GCC/ARM_CM4F/fsl_tickless_lptmr.o \
./freertos/Source/portable/GCC/ARM_CM4F/fsl_tickless_systick.o \
./freertos/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./freertos/Source/portable/GCC/ARM_CM4F/fsl_tickless_lptmr.d \
./freertos/Source/portable/GCC/ARM_CM4F/fsl_tickless_systick.d \
./freertos/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/Source/portable/GCC/ARM_CM4F/%.o: ../freertos/Source/portable/GCC/ARM_CM4F/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -flto  -g -D"CPU_MK64FN1M0VDC12" -I../freertos/Source/include -I../startup -I../board -I../utilities -I../freertos/Source/portable/GCC/ARM_CM4F -I../CMSIS -I../source -I../drivers -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


