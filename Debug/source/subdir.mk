################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ad.c \
../source/console.c \
../source/i2c.c \
../source/keypad.c \
../source/lcd.c \
../source/main.c \
../source/rgb.c \
../source/so.c \
../source/ssd.c \
../source/timer.c 

OBJS += \
./source/ad.o \
./source/console.o \
./source/i2c.o \
./source/keypad.o \
./source/lcd.o \
./source/main.o \
./source/rgb.o \
./source/so.o \
./source/ssd.o \
./source/timer.o 

C_DEPS += \
./source/ad.d \
./source/console.d \
./source/i2c.d \
./source/keypad.d \
./source/lcd.d \
./source/main.d \
./source/rgb.d \
./source/so.d \
./source/ssd.d \
./source/timer.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -flto  -g3 -D"CPU_MK64FN1M0VDC12" -I../freertos/Source/include -I../startup -I../board -I../utilities -I../freertos/Source/portable/GCC/ARM_CM4F -I../CMSIS -I../source -I../drivers -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


