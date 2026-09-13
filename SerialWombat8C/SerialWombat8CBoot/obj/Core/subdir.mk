################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

C_DEPS += \
./Core/core_riscv.d 

OBJS += \
./Core/core_riscv.o 

DIR_OBJS += \
./Core/*.o \

DIR_DEPS += \
./Core/*.d \

DIR_EXPANDS += \
./Core/*.271r.expand \


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	riscv32-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -gdwarf-4 -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/Debug" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/Core" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/User" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/Peripheral/inc" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombatCommon" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

