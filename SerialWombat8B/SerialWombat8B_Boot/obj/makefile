################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
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
SerialWombat8B_Boot.hex \

SECONDARY_LIST += \
SerialWombat8B_Boot.lst \

SECONDARY_SIZE += \
SerialWombat8B_Boot.siz \


# All Target
all: SerialWombat8B_Boot.elf secondary-outputs

# Tool invocations
SerialWombat8B_Boot.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_Boot\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"SerialWombat8B_Boot.map" -Xlinker --print-map --specs=nano.specs --specs=nosys.specs -o "SerialWombat8B_Boot.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
	@	@
SerialWombat8B_Boot.hex: SerialWombat8B_Boot.elf
	@	riscv-none-embed-objcopy -O ihex "SerialWombat8B_Boot.elf"  "SerialWombat8B_Boot.hex"
	@	@
SerialWombat8B_Boot.lst: SerialWombat8B_Boot.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "SerialWombat8B_Boot.elf" > "SerialWombat8B_Boot.lst"
	@	@
SerialWombat8B_Boot.siz: SerialWombat8B_Boot.elf
	@	riscv-none-embed-size --format=berkeley "SerialWombat8B_Boot.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) SerialWombat8B_Boot.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
