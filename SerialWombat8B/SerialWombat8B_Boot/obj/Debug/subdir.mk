################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"../Debug" -I"../../../SerialWombatCommon" -I"F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_Boot\Core" -I"F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_Boot\User" -I"F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_Boot\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

