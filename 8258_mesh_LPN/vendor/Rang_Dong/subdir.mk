################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/Rang_Dong/RD_BL55072A_LCD.c \
../vendor/Rang_Dong/RD_Light_Sensor.c \
../vendor/Rang_Dong/RD_SHTC3_Sensor.c \
../vendor/Rang_Dong/Sensor_Flash.c 

OBJS += \
./vendor/Rang_Dong/RD_BL55072A_LCD.o \
./vendor/Rang_Dong/RD_Light_Sensor.o \
./vendor/Rang_Dong/RD_SHTC3_Sensor.o \
./vendor/Rang_Dong/Sensor_Flash.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/Rang_Dong/%.o: ../vendor/Rang_Dong/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Users\PC5\Documents\Rang_Dong\CODE_Telink_BLE\CODE_HUM_TEMP_SHT30\firmware" -I"C:\Users\PC5\Documents\Rang_Dong\CODE_Telink_BLE\CODE_HUM_TEMP_SHT30\firmware\vendor\common\mi_api\mijia_ble_api" -I"C:\Users\PC5\Documents\Rang_Dong\CODE_Telink_BLE\CODE_HUM_TEMP_SHT30\firmware\vendor\common\mi_api\libs" -D__PROJECT_MESH_LPN__=1 -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


