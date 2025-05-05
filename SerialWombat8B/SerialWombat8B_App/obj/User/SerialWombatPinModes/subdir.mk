################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/SerialWombatPinModes/Font5x7.c \
../User/SerialWombatPinModes/MAX7219Matrix.c \
../User/SerialWombatPinModes/PS2Keyboard.c \
../User/SerialWombatPinModes/TM1637.c \
../User/SerialWombatPinModes/analogInput.c \
../User/SerialWombatPinModes/asciiConversion.c \
../User/SerialWombatPinModes/debounce.c \
../User/SerialWombatPinModes/digitalIO.c \
../User/SerialWombatPinModes/frequencyOutput.c \
../User/SerialWombatPinModes/hBridge.c \
../User/SerialWombatPinModes/inputProcess.c \
../User/SerialWombatPinModes/liquidCrystal.c \
../User/SerialWombatPinModes/matrixKeypad.c \
../User/SerialWombatPinModes/outputScale.c \
../User/SerialWombatPinModes/pinInputProcessor.c \
../User/SerialWombatPinModes/protectedOutput.c \
../User/SerialWombatPinModes/pulseOnChange.c \
../User/SerialWombatPinModes/pulseTimer.c \
../User/SerialWombatPinModes/pwm.c \
../User/SerialWombatPinModes/quadEnc.c \
../User/SerialWombatPinModes/queuedPulseOutput.c \
../User/SerialWombatPinModes/servo.c \
../User/SerialWombatPinModes/swI2cRoutines.c \
../User/SerialWombatPinModes/swMath.c \
../User/SerialWombatPinModes/throughputConsumer.c \
../User/SerialWombatPinModes/uartHw8B.c \
../User/SerialWombatPinModes/uartSw.c \
../User/SerialWombatPinModes/ultrasonicDistance.c \
../User/SerialWombatPinModes/watchdog.c 

OBJS += \
./User/SerialWombatPinModes/Font5x7.o \
./User/SerialWombatPinModes/MAX7219Matrix.o \
./User/SerialWombatPinModes/PS2Keyboard.o \
./User/SerialWombatPinModes/TM1637.o \
./User/SerialWombatPinModes/analogInput.o \
./User/SerialWombatPinModes/asciiConversion.o \
./User/SerialWombatPinModes/debounce.o \
./User/SerialWombatPinModes/digitalIO.o \
./User/SerialWombatPinModes/frequencyOutput.o \
./User/SerialWombatPinModes/hBridge.o \
./User/SerialWombatPinModes/inputProcess.o \
./User/SerialWombatPinModes/liquidCrystal.o \
./User/SerialWombatPinModes/matrixKeypad.o \
./User/SerialWombatPinModes/outputScale.o \
./User/SerialWombatPinModes/pinInputProcessor.o \
./User/SerialWombatPinModes/protectedOutput.o \
./User/SerialWombatPinModes/pulseOnChange.o \
./User/SerialWombatPinModes/pulseTimer.o \
./User/SerialWombatPinModes/pwm.o \
./User/SerialWombatPinModes/quadEnc.o \
./User/SerialWombatPinModes/queuedPulseOutput.o \
./User/SerialWombatPinModes/servo.o \
./User/SerialWombatPinModes/swI2cRoutines.o \
./User/SerialWombatPinModes/swMath.o \
./User/SerialWombatPinModes/throughputConsumer.o \
./User/SerialWombatPinModes/uartHw8B.o \
./User/SerialWombatPinModes/uartSw.o \
./User/SerialWombatPinModes/ultrasonicDistance.o \
./User/SerialWombatPinModes/watchdog.o 

C_DEPS += \
./User/SerialWombatPinModes/Font5x7.d \
./User/SerialWombatPinModes/MAX7219Matrix.d \
./User/SerialWombatPinModes/PS2Keyboard.d \
./User/SerialWombatPinModes/TM1637.d \
./User/SerialWombatPinModes/analogInput.d \
./User/SerialWombatPinModes/asciiConversion.d \
./User/SerialWombatPinModes/debounce.d \
./User/SerialWombatPinModes/digitalIO.d \
./User/SerialWombatPinModes/frequencyOutput.d \
./User/SerialWombatPinModes/hBridge.d \
./User/SerialWombatPinModes/inputProcess.d \
./User/SerialWombatPinModes/liquidCrystal.d \
./User/SerialWombatPinModes/matrixKeypad.d \
./User/SerialWombatPinModes/outputScale.d \
./User/SerialWombatPinModes/pinInputProcessor.d \
./User/SerialWombatPinModes/protectedOutput.d \
./User/SerialWombatPinModes/pulseOnChange.d \
./User/SerialWombatPinModes/pulseTimer.d \
./User/SerialWombatPinModes/pwm.d \
./User/SerialWombatPinModes/quadEnc.d \
./User/SerialWombatPinModes/queuedPulseOutput.d \
./User/SerialWombatPinModes/servo.d \
./User/SerialWombatPinModes/swI2cRoutines.d \
./User/SerialWombatPinModes/swMath.d \
./User/SerialWombatPinModes/throughputConsumer.d \
./User/SerialWombatPinModes/uartHw8B.d \
./User/SerialWombatPinModes/uartSw.d \
./User/SerialWombatPinModes/ultrasonicDistance.d \
./User/SerialWombatPinModes/watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
User/SerialWombatPinModes/%.o: ../User/SerialWombatPinModes/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DSW8B -I"../Debug" -I"../../../SerialWombatCommon" -I"F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_App\Core" -I"F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_App\User" -I"F:\keep\github\broadwellconsultinginc\SerialWombat\SerialWombat8B\SerialWombat8B_App\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

