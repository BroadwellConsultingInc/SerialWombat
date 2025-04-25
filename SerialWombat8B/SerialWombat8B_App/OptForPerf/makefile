################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/SerialWombatPinModes/subdir.mk
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
SerialWombat8B.hex \

SECONDARY_LIST += \
SerialWombat8B.lst \

SECONDARY_SIZE += \
SerialWombat8B.siz \


# All Target
all: SerialWombat8B.elf secondary-outputs

# Tool invocations
SerialWombat8B.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Ofast -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_App\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"SerialWombat8B.map" --specs=nano.specs --specs=nosys.specs -o "SerialWombat8B.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
	@	@
SerialWombat8B.hex: SerialWombat8B.elf
	@	riscv-none-embed-objcopy -O ihex "SerialWombat8B.elf"  "SerialWombat8B.hex"
	@	@
SerialWombat8B.lst: SerialWombat8B.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "SerialWombat8B.elf" > "SerialWombat8B.lst"
	@	@
SerialWombat8B.siz: SerialWombat8B.elf
	@	riscv-none-embed-size --format=berkeley "SerialWombat8B.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) SerialWombat8B.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
