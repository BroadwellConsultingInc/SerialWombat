################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/DMA_IO.c \
../User/ch32v00x_it.c \
../User/main.c \
../User/pinRegisters.c \
../User/protocol.c \
../User/queue.c \
../User/swmain.c \
../User/system_ch32v00x.c \
../User/timingResource.c 

OBJS += \
./User/DMA_IO.o \
./User/ch32v00x_it.o \
./User/main.o \
./User/pinRegisters.o \
./User/protocol.o \
./User/queue.o \
./User/swmain.o \
./User/system_ch32v00x.o \
./User/timingResource.o 

C_DEPS += \
./User/DMA_IO.d \
./User/ch32v00x_it.d \
./User/main.d \
./User/pinRegisters.d \
./User/protocol.d \
./User/queue.d \
./User/swmain.d \
./User/system_ch32v00x.d \
./User/timingResource.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Ofast -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DSW8B -I"../Debug" -I"../../../SerialWombatCommon" -I"F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_App\Core" -I"F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_App\User" -I"F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_App\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

