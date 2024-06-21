################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Profile/battservice.c \
../Profile/devinfoservice.c \
../Profile/hiddev.c \
../Profile/hidkbmservice.c \
../Profile/scanparamservice.c 

OBJS += \
./Profile/battservice.o \
./Profile/devinfoservice.o \
./Profile/hiddev.o \
./Profile/hidkbmservice.o \
./Profile/scanparamservice.o 

C_DEPS += \
./Profile/battservice.d \
./Profile/devinfoservice.d \
./Profile/hiddev.d \
./Profile/hidkbmservice.d \
./Profile/scanparamservice.d 


# Each subdirectory must supply rules for building sources it contributes
Profile/%.o: ../Profile/%.c
	@	@	riscv-none-elf-gcc -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -march=rv32imac_zicsr -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DCLK_OSC32K=1 -DLOW_MEM=1 -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Packages\FatFs" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Packages\FatFs\port" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\StdPeriphDriver\inc" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Packages\CherryUSB" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Packages\CherryUSB\class\hid" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Packages\CherryUSB\class\msc" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Packages\CherryUSB\common" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Packages\CherryUSB\core" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Startup" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\HAL\include" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\APP\include" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Profile\include" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\Ld" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\LIB" -I"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\KEYBOARD_CH582M\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

