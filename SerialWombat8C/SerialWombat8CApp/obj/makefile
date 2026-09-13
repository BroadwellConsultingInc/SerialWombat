################################################################################
# MRS Version: 2.5.0
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
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
SerialWombat8CApp.hex \

SECONDARY_LIST += \
SerialWombat8CApp.lst \

SECONDARY_SIZE += \
SerialWombat8CApp.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: SerialWombat8CApp.elf secondary-outputs

# Tool invocations
SerialWombat8CApp.elf: $(OBJS) $(USER_OBJS_ESCAPE)
	@	riscv32-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -gdwarf-4 -T "f:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8C\SerialWombat8CApp\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"SerialWombat8CApp.map" --specs=nano.specs --specs=nosys.specs -o "SerialWombat8CApp.elf" $(OBJS) $(LIBS) -lprintf
SerialWombat8CApp.hex: SerialWombat8CApp.elf
	@	riscv32-wch-elf-objcopy -O ihex "SerialWombat8CApp.elf" "SerialWombat8CApp.hex"
SerialWombat8CApp.lst: SerialWombat8CApp.elf
	@	riscv32-wch-elf-objdump --all-headers --demangle --disassemble -M xw "SerialWombat8CApp.elf" > "SerialWombat8CApp.lst"
SerialWombat8CApp.siz: SerialWombat8CApp.elf
	riscv32-wch-elf-size --format=berkeley "SerialWombat8CApp.elf"

# Other Targets
clean:
	-$(RM) $(DIR_OBJS) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE) SerialWombat8CApp.elf
	-$(RM) $(DIR_EXPANDS) $(CALLGRAPH_DOT)
	-$(RM) $(DIR_DEPS)
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets