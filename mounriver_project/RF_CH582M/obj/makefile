################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
RF_CH582M.hex \

SECONDARY_LIST += \
RF_CH582M.lst \

SECONDARY_SIZE += \
RF_CH582M.siz \


# 所有目标
all: RF_CH582M.elf secondary-outputs

# 工具调用
RF_CH582M.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-elf-gcc -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -march=rv32imac_zicsr -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\StdPeriphDriver" -L"E:\Personal\Personal\GitHub\XC-X99\mounriver_project\RF_CH582M\LIB" -Xlinker --print-memory-usage -Wl,-Map,"RF_CH582M.map" --specs=nano.specs --specs=nosys.specs -o "RF_CH582M.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
RF_CH582M.hex: RF_CH582M.elf
	@	riscv-none-elf-objcopy -O ihex "RF_CH582M.elf"  "RF_CH582M.hex"
	@	@
RF_CH582M.lst: RF_CH582M.elf
	@	riscv-none-elf-objdump --source --all-headers --demangle --line-numbers --wide "RF_CH582M.elf" > "RF_CH582M.lst"
	@	@
RF_CH582M.siz: RF_CH582M.elf
	@	riscv-none-elf-size --format=berkeley "RF_CH582M.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) RF_CH582M.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
