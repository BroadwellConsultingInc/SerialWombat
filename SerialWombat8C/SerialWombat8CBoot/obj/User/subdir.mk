################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/DMA_IO.c \
../User/ch32v00X_it.c \
../User/main.c \
../User/system_ch32v00X.c 

C_DEPS += \
./User/DMA_IO.d \
./User/ch32v00X_it.d \
./User/main.d \
./User/system_ch32v00X.d 

OBJS += \
./User/DMA_IO.o \
./User/ch32v00X_it.o \
./User/main.o \
./User/system_ch32v00X.o 

DIR_OBJS += \
./User/*.o \

DIR_DEPS += \
./User/*.d \

DIR_EXPANDS += \
./User/*.271r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv32-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -gdwarf-4 -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/Debug" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/Core" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/User" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CBoot/Peripheral/inc" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombatCommon" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

