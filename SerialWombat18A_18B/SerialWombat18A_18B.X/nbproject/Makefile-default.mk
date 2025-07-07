#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/memory/flash.s pic24fj256ga702/mcc_generated_files/i2c2Controller.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c timingResource.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c ../../SerialWombatPinModes/swMath.c ../../SerialWombatPinModes/ir_rx.c main.c protocol.c asciiConversion.c pinRegisters.c queue.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/timingResource.o ${OBJECTDIR}/_ext/1921908958/touch.o ${OBJECTDIR}/_ext/1921908958/uartHw.o ${OBJECTDIR}/_ext/1921908958/vga.o ${OBJECTDIR}/_ext/1921908958/ws2812.o ${OBJECTDIR}/_ext/1138356336/HSClock.o ${OBJECTDIR}/_ext/1138356336/HSCounter.o ${OBJECTDIR}/_ext/1138356336/hfServo.o ${OBJECTDIR}/_ext/1138356336/resistanceInput.o ${OBJECTDIR}/_ext/1138356336/uartSw.o ${OBJECTDIR}/_ext/1138356336/analogInput.o ${OBJECTDIR}/_ext/1138356336/digitalIO.o ${OBJECTDIR}/_ext/1138356336/hBridge.o ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o ${OBJECTDIR}/_ext/1138356336/inputProcess.o ${OBJECTDIR}/_ext/1138356336/outputScale.o ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o ${OBJECTDIR}/_ext/1138356336/protectedOutput.o ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o ${OBJECTDIR}/_ext/1138356336/pulseTimer.o ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o ${OBJECTDIR}/_ext/1138356336/watchdog.o ${OBJECTDIR}/_ext/1138356336/Font5x7.o ${OBJECTDIR}/_ext/1138356336/TM1637.o ${OBJECTDIR}/_ext/1138356336/debounce.o ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o ${OBJECTDIR}/_ext/1138356336/quadEnc.o ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o ${OBJECTDIR}/_ext/1138356336/servo.o ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o ${OBJECTDIR}/_ext/1138356336/pwm.o ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o ${OBJECTDIR}/_ext/1138356336/i2cController.o ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o ${OBJECTDIR}/_ext/2091145489/swMath.o ${OBJECTDIR}/_ext/2091145489/ir_rx.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/queue.o
POSSIBLE_DEPFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d ${OBJECTDIR}/timingResource.o.d ${OBJECTDIR}/_ext/1921908958/touch.o.d ${OBJECTDIR}/_ext/1921908958/uartHw.o.d ${OBJECTDIR}/_ext/1921908958/vga.o.d ${OBJECTDIR}/_ext/1921908958/ws2812.o.d ${OBJECTDIR}/_ext/1138356336/HSClock.o.d ${OBJECTDIR}/_ext/1138356336/HSCounter.o.d ${OBJECTDIR}/_ext/1138356336/hfServo.o.d ${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d ${OBJECTDIR}/_ext/1138356336/uartSw.o.d ${OBJECTDIR}/_ext/1138356336/analogInput.o.d ${OBJECTDIR}/_ext/1138356336/digitalIO.o.d ${OBJECTDIR}/_ext/1138356336/hBridge.o.d ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d ${OBJECTDIR}/_ext/1138356336/inputProcess.o.d ${OBJECTDIR}/_ext/1138356336/outputScale.o.d ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d ${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d ${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d ${OBJECTDIR}/_ext/1138356336/watchdog.o.d ${OBJECTDIR}/_ext/1138356336/Font5x7.o.d ${OBJECTDIR}/_ext/1138356336/TM1637.o.d ${OBJECTDIR}/_ext/1138356336/debounce.o.d ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d ${OBJECTDIR}/_ext/1138356336/quadEnc.o.d ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d ${OBJECTDIR}/_ext/1138356336/servo.o.d ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d ${OBJECTDIR}/_ext/1138356336/pwm.o.d ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d ${OBJECTDIR}/_ext/1138356336/i2cController.o.d ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d ${OBJECTDIR}/_ext/2091145489/swMath.o.d ${OBJECTDIR}/_ext/2091145489/ir_rx.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/protocol.o.d ${OBJECTDIR}/asciiConversion.o.d ${OBJECTDIR}/pinRegisters.o.d ${OBJECTDIR}/queue.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/timingResource.o ${OBJECTDIR}/_ext/1921908958/touch.o ${OBJECTDIR}/_ext/1921908958/uartHw.o ${OBJECTDIR}/_ext/1921908958/vga.o ${OBJECTDIR}/_ext/1921908958/ws2812.o ${OBJECTDIR}/_ext/1138356336/HSClock.o ${OBJECTDIR}/_ext/1138356336/HSCounter.o ${OBJECTDIR}/_ext/1138356336/hfServo.o ${OBJECTDIR}/_ext/1138356336/resistanceInput.o ${OBJECTDIR}/_ext/1138356336/uartSw.o ${OBJECTDIR}/_ext/1138356336/analogInput.o ${OBJECTDIR}/_ext/1138356336/digitalIO.o ${OBJECTDIR}/_ext/1138356336/hBridge.o ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o ${OBJECTDIR}/_ext/1138356336/inputProcess.o ${OBJECTDIR}/_ext/1138356336/outputScale.o ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o ${OBJECTDIR}/_ext/1138356336/protectedOutput.o ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o ${OBJECTDIR}/_ext/1138356336/pulseTimer.o ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o ${OBJECTDIR}/_ext/1138356336/watchdog.o ${OBJECTDIR}/_ext/1138356336/Font5x7.o ${OBJECTDIR}/_ext/1138356336/TM1637.o ${OBJECTDIR}/_ext/1138356336/debounce.o ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o ${OBJECTDIR}/_ext/1138356336/quadEnc.o ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o ${OBJECTDIR}/_ext/1138356336/servo.o ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o ${OBJECTDIR}/_ext/1138356336/pwm.o ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o ${OBJECTDIR}/_ext/1138356336/i2cController.o ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o ${OBJECTDIR}/_ext/2091145489/swMath.o ${OBJECTDIR}/_ext/2091145489/ir_rx.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/queue.o

# Source Files
SOURCEFILES=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/memory/flash.s pic24fj256ga702/mcc_generated_files/i2c2Controller.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c timingResource.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c ../../SerialWombatPinModes/swMath.c ../../SerialWombatPinModes/ir_rx.c main.c protocol.c asciiConversion.c pinRegisters.c queue.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GA702
MP_LINKER_FILE_OPTION=,--script="p24FJ256GA702_app.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/flags/default/8008fbbced1b502f6741f565045468f25734707 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/flags/default/9d8b1e8b950e9adb2f9b5b267a30117e90304906 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/flags/default/c18421560ea4391f4ff735e45577b6dd19c68073 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/flags/default/ee66afc1d4b8a37f16b730bce7798ed27d586c39 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/flags/default/c5f73d57a2285075e3bed6737ed5ff49d417f88 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/flags/default/eaceb5ba108644677d2a34e73075b3f47f0fc1e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/38edfebbb7f2cc8a9bafa72a6b3ff735fb37db1a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/flags/default/f8d9166a9d6c76e34a07a974775eb1c76383c066 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/flags/default/6e51be9dba0a31f3b01aa4cb5850eede272a24a1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/flags/default/ca951aedc7bcb8fd9c37e60f47e2f3ad6967391b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/flags/default/c0d6b194f7aa0737995f791ad45097c6eb630c89 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/flags/default/e3a9b8dd5972a03f081b0603d3b83932a46f6c91 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/flags/default/3f59d987e33cadcce8e07807d2164b7db8521139 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/flags/default/ddceb306213e4885a91627ea6edfada8fbced0a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/flags/default/baf7ef80eac53ef7fc947cc15d5731bbaface8f6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/flags/default/599350c448fd9a0a209dcb823765dc7513e338cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/flags/default/469622ea110b33981f78d9955246ed95750ad51f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o: pic24fj256ga702/mcc_generated_files/i2c2Controller.c  .generated_files/flags/default/4880fee674eb27c608cdc5e01fd027016acff7f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2Controller.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/flags/default/9685b5f6dd91c5f6a1e115ab6103188ffc9236ab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/flags/default/242590ff702e53a889834833faf0cecc952a49bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timingResource.o: timingResource.c  .generated_files/flags/default/6e0fbcb294d24a5f3867632efcf6bfd8bdef5cd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timingResource.o.d 
	@${RM} ${OBJECTDIR}/timingResource.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timingResource.c  -o ${OBJECTDIR}/timingResource.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timingResource.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/touch.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c  .generated_files/flags/default/37be34e5b9853ae9581909072196d01564ff4523 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c  -o ${OBJECTDIR}/_ext/1921908958/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/touch.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/uartHw.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c  .generated_files/flags/default/510fa2d6294b837d1c15a4296f0495bf166fb5d8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/uartHw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/uartHw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c  -o ${OBJECTDIR}/_ext/1921908958/uartHw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/uartHw.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/vga.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c  .generated_files/flags/default/cf421a5205cd8e42619d8e41beb0c3fdf04a3649 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/vga.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/vga.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c  -o ${OBJECTDIR}/_ext/1921908958/vga.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/vga.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/ws2812.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c  .generated_files/flags/default/fbaa64f8bb8cea0b318e6d1ba28f065278679ef5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/ws2812.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/ws2812.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c  -o ${OBJECTDIR}/_ext/1921908958/ws2812.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/ws2812.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/HSClock.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c  .generated_files/flags/default/97084a696ee7311fec86d4e3e7531535265399da .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSClock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSClock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c  -o ${OBJECTDIR}/_ext/1138356336/HSClock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/HSClock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/HSCounter.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c  .generated_files/flags/default/5fce1f709e9adb8e5de39516a4ea42556d925216 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSCounter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSCounter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c  -o ${OBJECTDIR}/_ext/1138356336/HSCounter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/HSCounter.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/hfServo.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c  .generated_files/flags/default/f09d604102d9188db5da6ecf67dfb00f25b836bd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hfServo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hfServo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c  -o ${OBJECTDIR}/_ext/1138356336/hfServo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/hfServo.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/resistanceInput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c  .generated_files/flags/default/6df355126663a48e9feb72238bd66086357cd743 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/resistanceInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c  -o ${OBJECTDIR}/_ext/1138356336/resistanceInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/uartSw.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c  .generated_files/flags/default/1233f7ac322098b916808c6cdc5b236109d7b35e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/uartSw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/uartSw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c  -o ${OBJECTDIR}/_ext/1138356336/uartSw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/uartSw.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/analogInput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c  .generated_files/flags/default/3a0dcc3d5ec0667eaea8ac83461d0ceefa00c12e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/analogInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c  -o ${OBJECTDIR}/_ext/1138356336/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/analogInput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/digitalIO.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c  .generated_files/flags/default/58c238d316b5db992cfac21a335b9d0511dc6186 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/digitalIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/digitalIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c  -o ${OBJECTDIR}/_ext/1138356336/digitalIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/digitalIO.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/hBridge.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c  .generated_files/flags/default/cf37bd3559294b1e9745e39ad1c02a3ff62b3f13 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hBridge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c  -o ${OBJECTDIR}/_ext/1138356336/hBridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/hBridge.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c  .generated_files/flags/default/4e178aa0ffeb38ca3c5b0fada7c439c96cb295ad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c  -o ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/inputProcess.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c  .generated_files/flags/default/d0ba5bee4f7f6f8f132120c9b831cb7b14853ea5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/inputProcess.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/inputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c  -o ${OBJECTDIR}/_ext/1138356336/inputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/inputProcess.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/outputScale.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c  .generated_files/flags/default/43261e3b57b82c5d82eeaf7d1656a6e7a2756bd5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/outputScale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/outputScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c  -o ${OBJECTDIR}/_ext/1138356336/outputScale.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/outputScale.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c  .generated_files/flags/default/e39b06f1dfe69eb93c618246ef018e87bbf98fda .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c  -o ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/protectedOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c  .generated_files/flags/default/94b1e877a6bb79ad865369ca822d491de431ae1e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c  -o ${OBJECTDIR}/_ext/1138356336/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pulseOnChange.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c  .generated_files/flags/default/4aefa86b905035fb69b1d408b7362aa94c478f4d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c  -o ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pulseTimer.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c  .generated_files/flags/default/65402884ba427c37125ef7e6579fbbe3bde5ec3b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c  -o ${OBJECTDIR}/_ext/1138356336/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c  .generated_files/flags/default/3c5a69957035ede3ef4eb98fa312775ece58bae9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c  -o ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/watchdog.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c  .generated_files/flags/default/4a6e7ac629461a456e2ebbb1727e3ce33725ecf1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/watchdog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c  -o ${OBJECTDIR}/_ext/1138356336/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/watchdog.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/Font5x7.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c  .generated_files/flags/default/715e687e6aa53aeeae247b1db88dad6f6263cff9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/Font5x7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/Font5x7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c  -o ${OBJECTDIR}/_ext/1138356336/Font5x7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/Font5x7.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/TM1637.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c  .generated_files/flags/default/b5c99bc730dd3dc8d111bd4d9268ea567c9be31a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/TM1637.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/TM1637.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c  -o ${OBJECTDIR}/_ext/1138356336/TM1637.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/TM1637.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/debounce.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c  .generated_files/flags/default/3f304f6ed1f7b58f10c66e73c9a2569ed0d145a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/debounce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c  -o ${OBJECTDIR}/_ext/1138356336/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/debounce.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/frequencyOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c  .generated_files/flags/default/116a50141f1ae5035acb9ba0e266acfd4028cba7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c  -o ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/liquidCrystal.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c  .generated_files/flags/default/4ff6e28c949983c639ac35b1c94e18e28e1ee398 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c  -o ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/matrixKeypad.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c  .generated_files/flags/default/9267d71abd2bac5d19d732fdf9125eed58565e9b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c  -o ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/quadEnc.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c  .generated_files/flags/default/b0697fb2a4c93472640e3b231cb74d59b199bb13 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c  -o ${OBJECTDIR}/_ext/1138356336/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/quadEnc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c  .generated_files/flags/default/27df3cd1be84ee72980eb169a39d5f3facc06ff8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c  -o ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/servo.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c  .generated_files/flags/default/a3f72657bab38d4b0814b6d5261786e56be0359b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c  -o ${OBJECTDIR}/_ext/1138356336/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/servo.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/throughputConsumer.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c  .generated_files/flags/default/926145ed148271985f72365b84b66f5db31b4900 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c  -o ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pwm.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c  .generated_files/flags/default/83d86a5f6b99f274aaa14fe2a6c2bf875a106751 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c  -o ${OBJECTDIR}/_ext/1138356336/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pwm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c  .generated_files/flags/default/f8e5e48f1081da3c37939e81dfe5e7da1661c65b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c  -o ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/i2cController.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c  .generated_files/flags/default/39674ac92f734d5f4f81e4b196dfc9d7d8cc07d4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/i2cController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/i2cController.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c  -o ${OBJECTDIR}/_ext/1138356336/i2cController.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/i2cController.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c  .generated_files/flags/default/559947c5d073bc8e98c604624133a3f5fea63dc9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c  -o ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/swMath.o: ../../SerialWombatPinModes/swMath.c  .generated_files/flags/default/9838552309e4344dca63549333c2ad0c3b6d91f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/swMath.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/swMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/swMath.c  -o ${OBJECTDIR}/_ext/2091145489/swMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/swMath.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/ir_rx.o: ../../SerialWombatPinModes/ir_rx.c  .generated_files/flags/default/5503e567566bc283b6a08e4f01ae60dc1cd68f3b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_rx.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_rx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/ir_rx.c  -o ${OBJECTDIR}/_ext/2091145489/ir_rx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/ir_rx.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/eef227742ff2c2ea8f8f63e83894e6d9363dc2d2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/flags/default/d28f37d0af82a0823aa0302a111c067952b57ee6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/flags/default/4f0da22c17fb39e5b7686aa5af693a4c29287a96 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/flags/default/cd494e453f9498f7e8d181a899aa04a1170557c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queue.o: queue.c  .generated_files/flags/default/df864b2d61cf2ee678652ec756a493f054630d3d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queue.c  -o ${OBJECTDIR}/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queue.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/flags/default/fb73d58d9c5be2b248efc3feef20c97e81c745a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/flags/default/efcbad39d1685f6453370934e8a2ef871b09850b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/flags/default/b3869a67d0c01a355019e4cd26cd75ab412d7cc4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/flags/default/78611c86382ea87f5b5340d2c37637762aacfb48 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/flags/default/ddb51ed488c029907e455a56fb0bc392e1847e34 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/flags/default/d34e92accc67edf28940906d8f8beac698ba1d9a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/e5d740f7cbc37c1d191a470e10884d231d66918b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/flags/default/968e4066deb373df024c8923a10c30191dacfdb8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/flags/default/80a6758f04746c493d9b7c6730bc2039ef4f1d62 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/flags/default/1497e102d7e5a14a474630ded7553b989a40e75 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/flags/default/9840df6cf861728d98b95de3ef132e0e84003593 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/flags/default/11e6c5571d47e7135363cb500b9f5787af684c3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/flags/default/52e03fd501fbc2c4535e46f4aab7198d6635c029 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/flags/default/ae7731e216e565832dc7af4b32a77d775967e033 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/flags/default/94a0ede6a3654a3af736c9697cd3a084326d93f5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/flags/default/5ffe40802b78ccfed1f071e8196f01aeebdf9a42 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/flags/default/5b621b795a3dff80ee85b2a9e4e8f75cd0a2480f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o: pic24fj256ga702/mcc_generated_files/i2c2Controller.c  .generated_files/flags/default/6ac33e2c7906cfd590d0dbb70bd5c298bcf728ac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2Controller.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/flags/default/59c9824e661262523d301b7aafe684caf272039f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/flags/default/98a125cd23adb575bd070fa787ecc49ff2dfdfaa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timingResource.o: timingResource.c  .generated_files/flags/default/b93eded422542b648ad796a86f58fdea2626f92e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timingResource.o.d 
	@${RM} ${OBJECTDIR}/timingResource.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timingResource.c  -o ${OBJECTDIR}/timingResource.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timingResource.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/touch.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c  .generated_files/flags/default/40dcc5ec120d64ba1bd6cd8bffeda71af2ce4869 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c  -o ${OBJECTDIR}/_ext/1921908958/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/touch.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/uartHw.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c  .generated_files/flags/default/f1699a1aa2d5c304daa872eaee61bc0729620f56 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/uartHw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/uartHw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c  -o ${OBJECTDIR}/_ext/1921908958/uartHw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/uartHw.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/vga.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c  .generated_files/flags/default/c2fd92da9365597f37f499a5c2662057b8dc0eae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/vga.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/vga.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c  -o ${OBJECTDIR}/_ext/1921908958/vga.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/vga.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/ws2812.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c  .generated_files/flags/default/a20b09e45ee4b2ac27bbdede60afeaf5afbd1e6f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/ws2812.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/ws2812.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c  -o ${OBJECTDIR}/_ext/1921908958/ws2812.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/ws2812.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/HSClock.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c  .generated_files/flags/default/1034194bb7ba81d59dc0c367c232c0d02e1f3ce4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSClock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSClock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c  -o ${OBJECTDIR}/_ext/1138356336/HSClock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/HSClock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/HSCounter.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c  .generated_files/flags/default/97af23f7c503e605cb14e93aba45262f54ef8607 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSCounter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSCounter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c  -o ${OBJECTDIR}/_ext/1138356336/HSCounter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/HSCounter.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/hfServo.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c  .generated_files/flags/default/8492760a1bd3ab01cc7cd7cbbe8fb657840b4a2c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hfServo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hfServo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c  -o ${OBJECTDIR}/_ext/1138356336/hfServo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/hfServo.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/resistanceInput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c  .generated_files/flags/default/9a01ea258570c81ab4c8f9081006140e4a882bcf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/resistanceInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c  -o ${OBJECTDIR}/_ext/1138356336/resistanceInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/uartSw.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c  .generated_files/flags/default/a08b7ffbfe15763a52ff423ac3467d3687d20e46 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/uartSw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/uartSw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c  -o ${OBJECTDIR}/_ext/1138356336/uartSw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/uartSw.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/analogInput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c  .generated_files/flags/default/d58ce5fbd5cd440e6faa9c18920cea575efd1e71 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/analogInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c  -o ${OBJECTDIR}/_ext/1138356336/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/analogInput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/digitalIO.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c  .generated_files/flags/default/40eae8c3f90983a2fc0182b7c9d5a4f4275b4ff3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/digitalIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/digitalIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c  -o ${OBJECTDIR}/_ext/1138356336/digitalIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/digitalIO.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/hBridge.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c  .generated_files/flags/default/a7b62dec298160d4aa00dda046b2866e2685c8e3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hBridge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c  -o ${OBJECTDIR}/_ext/1138356336/hBridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/hBridge.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c  .generated_files/flags/default/a2cc7225e52eb7658a2765ad6b6603b2d825e0ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c  -o ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/inputProcess.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c  .generated_files/flags/default/7e6d4c3dcc4692398f99dd785a096f34baa8e495 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/inputProcess.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/inputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c  -o ${OBJECTDIR}/_ext/1138356336/inputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/inputProcess.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/outputScale.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c  .generated_files/flags/default/14c6fa5f69077e566baf5a655f2fdc5a4b3dae7d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/outputScale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/outputScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c  -o ${OBJECTDIR}/_ext/1138356336/outputScale.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/outputScale.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c  .generated_files/flags/default/4e05c7fcfa5f8b50a288bbe91ccd3a91ec844014 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c  -o ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/protectedOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c  .generated_files/flags/default/281bf98f130fbb41dc0d88e761dabd423fc3ab5c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c  -o ${OBJECTDIR}/_ext/1138356336/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pulseOnChange.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c  .generated_files/flags/default/155753941124bcb72531cb8458bef835fcfb2fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c  -o ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pulseTimer.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c  .generated_files/flags/default/c3a66f37cbb0969eb20d19a47564180de6d66f93 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c  -o ${OBJECTDIR}/_ext/1138356336/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c  .generated_files/flags/default/c06928b5df0e13536505bcf21c81b9e53ede4b73 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c  -o ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/watchdog.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c  .generated_files/flags/default/75986edf8b838488c426b6adf86c972e09354f9d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/watchdog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c  -o ${OBJECTDIR}/_ext/1138356336/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/watchdog.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/Font5x7.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c  .generated_files/flags/default/9f051f34ddd39e77bf5d61207cb0dfc87c2bd655 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/Font5x7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/Font5x7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c  -o ${OBJECTDIR}/_ext/1138356336/Font5x7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/Font5x7.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/TM1637.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c  .generated_files/flags/default/794e1dd5bc35379c3f1905d49a47c72b8690d87d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/TM1637.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/TM1637.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c  -o ${OBJECTDIR}/_ext/1138356336/TM1637.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/TM1637.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/debounce.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c  .generated_files/flags/default/854112c8054f7786f51422c5652ec7fffa11c31a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/debounce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c  -o ${OBJECTDIR}/_ext/1138356336/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/debounce.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/frequencyOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c  .generated_files/flags/default/624bc20049e355c1bb013cdfb663f5073de315f4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c  -o ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/liquidCrystal.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c  .generated_files/flags/default/f51a3d4bc762ac1a7232da21d6fb9a2bc438b8b0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c  -o ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/matrixKeypad.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c  .generated_files/flags/default/900e165402c7a478afaae442b71a486da6522628 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c  -o ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/quadEnc.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c  .generated_files/flags/default/267de2afa74d9c0925e6420d24f4e18abaf3276c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c  -o ${OBJECTDIR}/_ext/1138356336/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/quadEnc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c  .generated_files/flags/default/55846177c3377bc6ea007f7399c8ee469d2e5551 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c  -o ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/servo.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c  .generated_files/flags/default/8a7d97d4cdcdf37d6726de21d2bc51f8ba069743 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c  -o ${OBJECTDIR}/_ext/1138356336/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/servo.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/throughputConsumer.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c  .generated_files/flags/default/99e04906960741ba52a5383f2228f634540d2bf1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c  -o ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pwm.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c  .generated_files/flags/default/e6aa13b9f98173a94b34fb7d5915c8908817ff72 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c  -o ${OBJECTDIR}/_ext/1138356336/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pwm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c  .generated_files/flags/default/d0921e5a6c4c3463ed0e7e7f22601380d89a5add .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c  -o ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/i2cController.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c  .generated_files/flags/default/97d51b49b74494de0da42b7e4f1d59c367ed5527 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/i2cController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/i2cController.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c  -o ${OBJECTDIR}/_ext/1138356336/i2cController.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/i2cController.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c  .generated_files/flags/default/2e203d9ff8ec5eee9d905b3d63fe1bef976a3f88 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c  -o ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/swMath.o: ../../SerialWombatPinModes/swMath.c  .generated_files/flags/default/b3f603fa0849e94e32572907704461a43d36e64a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/swMath.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/swMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/swMath.c  -o ${OBJECTDIR}/_ext/2091145489/swMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/swMath.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/ir_rx.o: ../../SerialWombatPinModes/ir_rx.c  .generated_files/flags/default/49b488ccd53c0793f7be9bc3d8514227a956b888 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_rx.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_rx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/ir_rx.c  -o ${OBJECTDIR}/_ext/2091145489/ir_rx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/ir_rx.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/2e10748d4f387149f0a3be18a512585e296a9a34 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/flags/default/4bd24d78541760bde21312bdbb312904486f8677 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/flags/default/9df0e701d6f74ee4409c5ab20685d974308cb29a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/flags/default/2458c12ee315a520d404ee497dbfc660efbc24a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queue.o: queue.c  .generated_files/flags/default/60ba083be1d67360093112347827ba828673ec7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queue.c  -o ${OBJECTDIR}/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queue.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o: pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/flags/default/f90031b21983705507845f769112b07f0e8e6c04 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/wombatasm.o: pic24fj256ga702/wombatasm.s  .generated_files/flags/default/fb92a6088ef23a6b14cc501df08408f48513d310 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o: pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/flags/default/b36d8758c24b815cd6a19088689d7a0f7efdd7f9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/wombatasm.o: pic24fj256ga702/wombatasm.s  .generated_files/flags/default/de073f92bfe79b8f43c48231232e760ea23ab857 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    p24FJ256GA702_app.gld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" --fill=0x555555@0x27000:0x27800  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-ivt,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p24FJ256GA702_app.gld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" --fill=0x555555@0x27000:0x27800 -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-ivt,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
