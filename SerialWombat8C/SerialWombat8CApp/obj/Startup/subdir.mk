################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Startup/startup_ch32v00X.S 

S_UPPER_DEPS += \
./Startup/startup_ch32v00X.d 

OBJS += \
./Startup/startup_ch32v00X.o 

DIR_OBJS += \
./Startup/*.o \

DIR_DEPS += \
./Startup/*.d \

DIR_EXPANDS += \
./Startup/*.271r.expand \


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.S
	@	riscv32-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -gdwarf-4 -x assembler-with-cpp -I"f:/keep/github/broadwellconsultinginc/SerialWombat/SerialWombat8C/SerialWombat8CApp/Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

