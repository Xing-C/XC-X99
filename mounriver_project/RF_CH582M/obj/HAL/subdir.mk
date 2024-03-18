################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/ISP.c \
../HAL/LED.c \
../HAL/MCU.c \
../HAL/RTC.c \
../HAL/SLEEP.c \
../HAL/USB.c 

OBJS += \
./HAL/ISP.o \
./HAL/LED.o \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o \
./HAL/USB.o 

C_DEPS += \
./HAL/ISP.d \
./HAL/LED.d \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d \
./HAL/USB.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@	@	riscv-none-elf-gcc -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -march=rv32imac_zicsr -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\Startup" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\Ld" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\RVMSIS" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\StdPeriphDriver\inc" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\APP\include" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\HAL\include" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\LIB" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

