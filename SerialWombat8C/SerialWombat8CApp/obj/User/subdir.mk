################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/DMA_IO.c \
../User/ch32v00X_it.c \
../User/main.c \
../User/pinRegisters.c \
../User/protocol.c \
../User/swmain.c \
../User/system_ch32v00X.c \
../User/timingResource.c 

C_DEPS += \
./User/DMA_IO.d \
./User/ch32v00X_it.d \
./User/main.d \
./User/pinRegisters.d \
./User/protocol.d \
./User/swmain.d \
./User/system_ch32v00X.d \
./User/timingResource.d 

OBJS += \
./User/DMA_IO.o \
./User/ch32v00X_it.o \
./User/main.o \
./User/pinRegisters.o \
./User/protocol.o \
./User/swmain.o \
./User/system_ch32v00X.o \
./User/timingResource.o 

DIR_OBJS += \
./User/*.o \

DIR_DEPS += \
./User/*.d \

DIR_EXPANDS += \
./User/*.271r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv32-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -gdwarf-4 -DSW8C -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CApp/Debug" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CApp/Core" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CApp/User" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CApp/Peripheral/inc" -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombatCommon" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

