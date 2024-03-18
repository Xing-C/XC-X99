################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/RF_PHY.c \
../APP/RF_main.c 

OBJS += \
./APP/RF_PHY.o \
./APP/RF_main.o 

C_DEPS += \
./APP/RF_PHY.d \
./APP/RF_main.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	@	riscv-none-elf-gcc -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -march=rv32imac_zicsr -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\Startup" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\Ld" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\RVMSIS" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\StdPeriphDriver\inc" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\APP\include" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\HAL\include" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\LIB" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

