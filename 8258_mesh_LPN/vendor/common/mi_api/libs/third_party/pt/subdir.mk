################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/common/mi_api/libs/third_party/pt/pt_misc.c 

OBJS += \
./vendor/common/mi_api/libs/third_party/pt/pt_misc.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/common/mi_api/libs/third_party/pt/%.o: ../vendor/common/mi_api/libs/third_party/pt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Users\PC5\Documents\Rang_Dong\CODE_Telink_BLE\CODE_HUM_TEMP_SHT30\firmware" -I"C:\Users\PC5\Documents\Rang_Dong\CODE_Telink_BLE\CODE_HUM_TEMP_SHT30\firmware\vendor\common\mi_api\mijia_ble_api" -I"C:\Users\PC5\Documents\Rang_Dong\CODE_Telink_BLE\CODE_HUM_TEMP_SHT30\firmware\vendor\common\mi_api\libs" -D__PROJECT_MESH_LPN__=1 -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

