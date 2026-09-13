################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

C_DEPS += \
./Debug/debug.d 

OBJS += \
./Debug/debug.o 

DIR_OBJS += \
./Debug/*.o \

DIR_DEPS += \
./Debug/*.d \

DIR_EXPANDS += \
./Debug/*.271r.expand \


# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c
	@	riscv32-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -gdwarf-4 -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/Debug" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/Core" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/User" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/Peripheral/inc" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombatCommon" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

