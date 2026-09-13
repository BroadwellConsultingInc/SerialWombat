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
SOURCEFILES_QUOTED_IF_SPACED=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/memory/flash.s pic24fj256ga702/mcc_generated_files/i2c2Controller.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c timingResource.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c ../../SerialWombatPinModes/swMath.c ../../SerialWombatPinModes/ir_rx.c ../../SerialWombatPinModes/queue.c ../../SerialWombatPinModes/blink.c ../../SerialWombatPinModes/ir_tx.c ../../SerialWombatPinModes/SPI.c ../../SerialWombatPinModes/charlieplex.c ../../SerialWombatPinModes/randomBlink.c main.c protocol.c asciiConversion.c pinRegisters.c ../../SerialWombatPinModes/protocolCommon.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/timingResource.o ${OBJECTDIR}/_ext/1921908958/touch.o ${OBJECTDIR}/_ext/1921908958/uartHw.o ${OBJECTDIR}/_ext/1921908958/vga.o ${OBJECTDIR}/_ext/1921908958/ws2812.o ${OBJECTDIR}/_ext/1138356336/HSClock.o ${OBJECTDIR}/_ext/1138356336/HSCounter.o ${OBJECTDIR}/_ext/1138356336/hfServo.o ${OBJECTDIR}/_ext/1138356336/resistanceInput.o ${OBJECTDIR}/_ext/1138356336/uartSw.o ${OBJECTDIR}/_ext/1138356336/analogInput.o ${OBJECTDIR}/_ext/1138356336/digitalIO.o ${OBJECTDIR}/_ext/1138356336/hBridge.o ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o ${OBJECTDIR}/_ext/1138356336/inputProcess.o ${OBJECTDIR}/_ext/1138356336/outputScale.o ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o ${OBJECTDIR}/_ext/1138356336/protectedOutput.o ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o ${OBJECTDIR}/_ext/1138356336/pulseTimer.o ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o ${OBJECTDIR}/_ext/1138356336/watchdog.o ${OBJECTDIR}/_ext/1138356336/Font5x7.o ${OBJECTDIR}/_ext/1138356336/TM1637.o ${OBJECTDIR}/_ext/1138356336/debounce.o ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o ${OBJECTDIR}/_ext/1138356336/quadEnc.o ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o ${OBJECTDIR}/_ext/1138356336/servo.o ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o ${OBJECTDIR}/_ext/1138356336/pwm.o ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o ${OBJECTDIR}/_ext/1138356336/i2cController.o ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o ${OBJECTDIR}/_ext/2091145489/swMath.o ${OBJECTDIR}/_ext/2091145489/ir_rx.o ${OBJECTDIR}/_ext/2091145489/queue.o ${OBJECTDIR}/_ext/2091145489/blink.o ${OBJECTDIR}/_ext/2091145489/ir_tx.o ${OBJECTDIR}/_ext/2091145489/SPI.o ${OBJECTDIR}/_ext/2091145489/charlieplex.o ${OBJECTDIR}/_ext/2091145489/randomBlink.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/_ext/2091145489/protocolCommon.o
POSSIBLE_DEPFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d ${OBJECTDIR}/timingResource.o.d ${OBJECTDIR}/_ext/1921908958/touch.o.d ${OBJECTDIR}/_ext/1921908958/uartHw.o.d ${OBJECTDIR}/_ext/1921908958/vga.o.d ${OBJECTDIR}/_ext/1921908958/ws2812.o.d ${OBJECTDIR}/_ext/1138356336/HSClock.o.d ${OBJECTDIR}/_ext/1138356336/HSCounter.o.d ${OBJECTDIR}/_ext/1138356336/hfServo.o.d ${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d ${OBJECTDIR}/_ext/1138356336/uartSw.o.d ${OBJECTDIR}/_ext/1138356336/analogInput.o.d ${OBJECTDIR}/_ext/1138356336/digitalIO.o.d ${OBJECTDIR}/_ext/1138356336/hBridge.o.d ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d ${OBJECTDIR}/_ext/1138356336/inputProcess.o.d ${OBJECTDIR}/_ext/1138356336/outputScale.o.d ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d ${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d ${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d ${OBJECTDIR}/_ext/1138356336/watchdog.o.d ${OBJECTDIR}/_ext/1138356336/Font5x7.o.d ${OBJECTDIR}/_ext/1138356336/TM1637.o.d ${OBJECTDIR}/_ext/1138356336/debounce.o.d ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d ${OBJECTDIR}/_ext/1138356336/quadEnc.o.d ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d ${OBJECTDIR}/_ext/1138356336/servo.o.d ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d ${OBJECTDIR}/_ext/1138356336/pwm.o.d ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d ${OBJECTDIR}/_ext/1138356336/i2cController.o.d ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d ${OBJECTDIR}/_ext/2091145489/swMath.o.d ${OBJECTDIR}/_ext/2091145489/ir_rx.o.d ${OBJECTDIR}/_ext/2091145489/queue.o.d ${OBJECTDIR}/_ext/2091145489/blink.o.d ${OBJECTDIR}/_ext/2091145489/ir_tx.o.d ${OBJECTDIR}/_ext/2091145489/SPI.o.d ${OBJECTDIR}/_ext/2091145489/charlieplex.o.d ${OBJECTDIR}/_ext/2091145489/randomBlink.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/protocol.o.d ${OBJECTDIR}/asciiConversion.o.d ${OBJECTDIR}/pinRegisters.o.d ${OBJECTDIR}/_ext/2091145489/protocolCommon.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/timingResource.o ${OBJECTDIR}/_ext/1921908958/touch.o ${OBJECTDIR}/_ext/1921908958/uartHw.o ${OBJECTDIR}/_ext/1921908958/vga.o ${OBJECTDIR}/_ext/1921908958/ws2812.o ${OBJECTDIR}/_ext/1138356336/HSClock.o ${OBJECTDIR}/_ext/1138356336/HSCounter.o ${OBJECTDIR}/_ext/1138356336/hfServo.o ${OBJECTDIR}/_ext/1138356336/resistanceInput.o ${OBJECTDIR}/_ext/1138356336/uartSw.o ${OBJECTDIR}/_ext/1138356336/analogInput.o ${OBJECTDIR}/_ext/1138356336/digitalIO.o ${OBJECTDIR}/_ext/1138356336/hBridge.o ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o ${OBJECTDIR}/_ext/1138356336/inputProcess.o ${OBJECTDIR}/_ext/1138356336/outputScale.o ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o ${OBJECTDIR}/_ext/1138356336/protectedOutput.o ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o ${OBJECTDIR}/_ext/1138356336/pulseTimer.o ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o ${OBJECTDIR}/_ext/1138356336/watchdog.o ${OBJECTDIR}/_ext/1138356336/Font5x7.o ${OBJECTDIR}/_ext/1138356336/TM1637.o ${OBJECTDIR}/_ext/1138356336/debounce.o ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o ${OBJECTDIR}/_ext/1138356336/quadEnc.o ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o ${OBJECTDIR}/_ext/1138356336/servo.o ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o ${OBJECTDIR}/_ext/1138356336/pwm.o ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o ${OBJECTDIR}/_ext/1138356336/i2cController.o ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o ${OBJECTDIR}/_ext/2091145489/swMath.o ${OBJECTDIR}/_ext/2091145489/ir_rx.o ${OBJECTDIR}/_ext/2091145489/queue.o ${OBJECTDIR}/_ext/2091145489/blink.o ${OBJECTDIR}/_ext/2091145489/ir_tx.o ${OBJECTDIR}/_ext/2091145489/SPI.o ${OBJECTDIR}/_ext/2091145489/charlieplex.o ${OBJECTDIR}/_ext/2091145489/randomBlink.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/_ext/2091145489/protocolCommon.o

# Source Files
SOURCEFILES=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/memory/flash.s pic24fj256ga702/mcc_generated_files/i2c2Controller.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c timingResource.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c ../../SerialWombatPinModes/swMath.c ../../SerialWombatPinModes/ir_rx.c ../../SerialWombatPinModes/queue.c ../../SerialWombatPinModes/blink.c ../../SerialWombatPinModes/ir_tx.c ../../SerialWombatPinModes/SPI.c ../../SerialWombatPinModes/charlieplex.c ../../SerialWombatPinModes/randomBlink.c main.c protocol.c asciiConversion.c pinRegisters.c ../../SerialWombatPinModes/protocolCommon.c



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
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/flags/default/e1c6d748d7b28d1f52afa5f3427dce39113f814 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/flags/default/507000719a7315ac5e1916723ca324c828e3b711 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/flags/default/e25311d1fe3700deffa51eed4831dcbd3209be87 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/flags/default/ccff9a71f27f3dd0fc16fdb7c7ed92c29de6dbf8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/flags/default/6f6dc32bcc7d7d5547feae84f40e50b016d5b34c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/flags/default/f2b100fa6b4199377f2cbaa7531e5987926b1aa7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/5a9482ef59a2c87c80f4aa840131a0315f709e27 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/flags/default/556399de62ca11f5b6354b2e639dd95c0739f58a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/flags/default/52d90255ecd6afa31717c77134fd1fda956a73e1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/flags/default/f7618871616da06292ee8db1d0b2ba53e6c2b125 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/flags/default/3caaed47bf5ac154c30efc78cc8fc04ff1aa4efa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/flags/default/5b7209b632546e97cf822bd263c50c23b78fda76 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/flags/default/90907e230fa44553959e03389a3d98001e23b9a3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/flags/default/36765f0c3cd0fd89027b22d57430fe5133f05ef0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/flags/default/795522c17ee0f08c5c632b1a93bb16376bb04839 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/flags/default/dc8d7b10ec145c8e228124bd25cc79ed9cd4bb80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/flags/default/859ac4f63ceb9224b35b07d48171934524886468 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o: pic24fj256ga702/mcc_generated_files/i2c2Controller.c  .generated_files/flags/default/ffc06925fed11324bda031b5f096b539a542e4b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2Controller.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/flags/default/72930ef914b30f6a32a5681a0c053200d424a52b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/flags/default/1d8727a3a7bf503a892cbdc6d34138c148a91f62 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timingResource.o: timingResource.c  .generated_files/flags/default/8e4af2974de0624fb93057e8b70dfe6e99aaef92 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timingResource.o.d 
	@${RM} ${OBJECTDIR}/timingResource.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timingResource.c  -o ${OBJECTDIR}/timingResource.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timingResource.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/touch.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c  .generated_files/flags/default/12689bfe91bced465640705e78be216d489b0c7f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c  -o ${OBJECTDIR}/_ext/1921908958/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/touch.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/uartHw.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c  .generated_files/flags/default/823a0aeaf5332dc2a1494ab9ad8851db446f19db .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/uartHw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/uartHw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c  -o ${OBJECTDIR}/_ext/1921908958/uartHw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/uartHw.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/vga.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c  .generated_files/flags/default/7196fe688a082f13d6a20074d872670775f9b558 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/vga.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/vga.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c  -o ${OBJECTDIR}/_ext/1921908958/vga.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/vga.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/ws2812.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c  .generated_files/flags/default/acd34db313852bdd129cdaf86e93120fc2d47e68 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/ws2812.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/ws2812.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c  -o ${OBJECTDIR}/_ext/1921908958/ws2812.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/ws2812.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/HSClock.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c  .generated_files/flags/default/ae0b82ac8cd2c4b7d0149bf3256f6ca793e72550 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSClock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSClock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c  -o ${OBJECTDIR}/_ext/1138356336/HSClock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/HSClock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/HSCounter.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c  .generated_files/flags/default/f85ae5473919fb9916862b14941ac81bb55eebfd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSCounter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSCounter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c  -o ${OBJECTDIR}/_ext/1138356336/HSCounter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/HSCounter.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/hfServo.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c  .generated_files/flags/default/11d9dfefc3a5e90c3817e843e22028987b08fe3e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hfServo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hfServo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c  -o ${OBJECTDIR}/_ext/1138356336/hfServo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/hfServo.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/resistanceInput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c  .generated_files/flags/default/2b369272bf7c6f74d9b1e4b3e1b9e7d292458244 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/resistanceInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c  -o ${OBJECTDIR}/_ext/1138356336/resistanceInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/uartSw.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c  .generated_files/flags/default/1ee44b35e1c1c1c76aee671e01d3b88aa8b79118 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/uartSw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/uartSw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c  -o ${OBJECTDIR}/_ext/1138356336/uartSw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/uartSw.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/analogInput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c  .generated_files/flags/default/c2bf8d7cf7aadf7803bdd81b3767def7c807c3b5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/analogInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c  -o ${OBJECTDIR}/_ext/1138356336/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/analogInput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/digitalIO.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c  .generated_files/flags/default/9ff32fbca1869ffb83768023c533c8f75667f588 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/digitalIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/digitalIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c  -o ${OBJECTDIR}/_ext/1138356336/digitalIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/digitalIO.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/hBridge.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c  .generated_files/flags/default/9c0afa3a8806b06fcc4e6311efc878368bbf4834 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hBridge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c  -o ${OBJECTDIR}/_ext/1138356336/hBridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/hBridge.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c  .generated_files/flags/default/d2445d7c1e823635e03461f0f4c5a9b1d614a02b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c  -o ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/inputProcess.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c  .generated_files/flags/default/7789e8ff03678c82722305d88f70602aad9c8fa8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/inputProcess.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/inputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c  -o ${OBJECTDIR}/_ext/1138356336/inputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/inputProcess.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/outputScale.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c  .generated_files/flags/default/ac46dbbe1400ce6ace5f697671021f15a1bef433 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/outputScale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/outputScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c  -o ${OBJECTDIR}/_ext/1138356336/outputScale.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/outputScale.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c  .generated_files/flags/default/d4c7b64ba97889373fb263aad91e7244cd92ad62 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c  -o ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/protectedOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c  .generated_files/flags/default/2404c7039e89ca07731a2a06a7d283d643785896 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c  -o ${OBJECTDIR}/_ext/1138356336/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pulseOnChange.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c  .generated_files/flags/default/5f1eef0a498848ff451d50ecb76329ac56603170 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c  -o ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pulseTimer.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c  .generated_files/flags/default/ac2908569660f9c97d4dc69ee734cb8833dc687e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c  -o ${OBJECTDIR}/_ext/1138356336/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c  .generated_files/flags/default/8a6a709c70f1f9449534baaf39ab1c00453ca4ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c  -o ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/watchdog.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c  .generated_files/flags/default/a7a0d7ee9fd5d7a22c5ed04cc11613452a0e41e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/watchdog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c  -o ${OBJECTDIR}/_ext/1138356336/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/watchdog.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/Font5x7.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c  .generated_files/flags/default/4ccace9c98b9133769c57d0ac64ae05a4718577a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/Font5x7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/Font5x7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c  -o ${OBJECTDIR}/_ext/1138356336/Font5x7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/Font5x7.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/TM1637.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c  .generated_files/flags/default/2bfe3f4608d7262f685236fd47a1bd108269dca1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/TM1637.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/TM1637.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c  -o ${OBJECTDIR}/_ext/1138356336/TM1637.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/TM1637.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/debounce.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c  .generated_files/flags/default/afd91b634d2bfe89e7b5df76cdd2f7fe7d44ecd9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/debounce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c  -o ${OBJECTDIR}/_ext/1138356336/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/debounce.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/frequencyOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c  .generated_files/flags/default/1683071ac897feb2813bd6e48788b3c0c437fdd9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c  -o ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/liquidCrystal.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c  .generated_files/flags/default/8e09d93aec1ca34ac744d64cf73157a3bb315a80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c  -o ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/matrixKeypad.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c  .generated_files/flags/default/a7a3ee94b3de90bd8b2a9b3d535ff5fe5abbd8c1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c  -o ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/quadEnc.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c  .generated_files/flags/default/381ec46314a81adfc3d62f2e4f7bf74dab83d4cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c  -o ${OBJECTDIR}/_ext/1138356336/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/quadEnc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c  .generated_files/flags/default/ffe61bec171a5d8b86781e78cceab3ad77284b4a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c  -o ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/servo.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c  .generated_files/flags/default/ac57e2721402ccecb873b36e35acfa94f1cb668c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c  -o ${OBJECTDIR}/_ext/1138356336/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/servo.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/throughputConsumer.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c  .generated_files/flags/default/6eafd8c2ee42ca3695c0e217d31184a513ff00ac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c  -o ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pwm.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c  .generated_files/flags/default/5e9e5956c123baff1ca6fe74066fc4d7a0007cf0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c  -o ${OBJECTDIR}/_ext/1138356336/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pwm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c  .generated_files/flags/default/3fcca1bb036b37efa2ee633b941effc7a5e41b18 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c  -o ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/i2cController.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c  .generated_files/flags/default/967b7ec0a4d5d4da25b8ddd95b21dcfb969ca571 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/i2cController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/i2cController.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c  -o ${OBJECTDIR}/_ext/1138356336/i2cController.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/i2cController.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c  .generated_files/flags/default/c5113be0db8a8087b49603615eea9f8c17d3a91c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c  -o ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/swMath.o: ../../SerialWombatPinModes/swMath.c  .generated_files/flags/default/61b0c50808408887870e32dc041c3c7d80b5a326 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/swMath.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/swMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/swMath.c  -o ${OBJECTDIR}/_ext/2091145489/swMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/swMath.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/ir_rx.o: ../../SerialWombatPinModes/ir_rx.c  .generated_files/flags/default/dafc3c1f78138c94b55ec651b570aad2e430ad1b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_rx.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_rx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/ir_rx.c  -o ${OBJECTDIR}/_ext/2091145489/ir_rx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/ir_rx.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/queue.o: ../../SerialWombatPinModes/queue.c  .generated_files/flags/default/9b8b5a74c6db6920592cebfb462bb3674de25aeb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/queue.c  -o ${OBJECTDIR}/_ext/2091145489/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/queue.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/blink.o: ../../SerialWombatPinModes/blink.c  .generated_files/flags/default/ec96af28ffd1998d45c5dc93d0da30809a29fe7d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/blink.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/blink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/blink.c  -o ${OBJECTDIR}/_ext/2091145489/blink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/blink.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/ir_tx.o: ../../SerialWombatPinModes/ir_tx.c  .generated_files/flags/default/74d2ad73a5490f076a8a1c3fbba12b386d7c0ef3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_tx.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_tx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/ir_tx.c  -o ${OBJECTDIR}/_ext/2091145489/ir_tx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/ir_tx.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/SPI.o: ../../SerialWombatPinModes/SPI.c  .generated_files/flags/default/6ea87e1b4ceb73f466443da4e13d8d2549e7de1a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/SPI.c  -o ${OBJECTDIR}/_ext/2091145489/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/SPI.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/charlieplex.o: ../../SerialWombatPinModes/charlieplex.c  .generated_files/flags/default/4bf33d3d8598c652641a4a790668669fa672ceb9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/charlieplex.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/charlieplex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/charlieplex.c  -o ${OBJECTDIR}/_ext/2091145489/charlieplex.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/charlieplex.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/randomBlink.o: ../../SerialWombatPinModes/randomBlink.c  .generated_files/flags/default/46cbd8f320c46ae830505a7a96830ca89f7e6f79 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/randomBlink.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/randomBlink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/randomBlink.c  -o ${OBJECTDIR}/_ext/2091145489/randomBlink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/randomBlink.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/decc7e1bb7724e3059b71c79bbc6ac5101e9b08f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/flags/default/ca301351383126a7785a8f9cc0464a76e4b8fc6e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/flags/default/676c026234f1f5ae28e36dd682d05bfbb3334a85 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/flags/default/af7f89f00b6735a6fe4b32b8d3d2f12b4cf5dfde .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/protocolCommon.o: ../../SerialWombatPinModes/protocolCommon.c  .generated_files/flags/default/e7479f07d3cc5741d69fd54e06e5a7fff602227d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/protocolCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/protocolCommon.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/protocolCommon.c  -o ${OBJECTDIR}/_ext/2091145489/protocolCommon.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/protocolCommon.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/flags/default/5ec94fa2d0da7f0063f01fac69fd1665f92d3769 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/flags/default/a7285d4685136c5f6eeb142b845f18e63f765c3f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/flags/default/967645ef1c0d042e033cfe7b14e4fb01af680c76 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/flags/default/b40911b41e3dca6e0fd045a331b8b3ebd27d636c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/flags/default/1e2c50763cf5a917a83158b1b051602a385fec59 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/flags/default/3eabd7f53a636f0c2660408a584586a4dc5b6c23 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/dcf1cd182bd7a634c0edd8e358c09c3c6eb94c19 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/flags/default/643f14b67b57f8bf6634759b13f0e2de335b03ad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/flags/default/6119e356fbbec9acddac4829f28be2e089a22dfd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/flags/default/1e5fefe413d38a3b3d4c1a4178e0ca8400c95091 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/flags/default/2017cd336452a5be0f6685f47a1c2a006a81eec9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/flags/default/59448833c55312afbdd5651d51841ef04bf39534 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/flags/default/45a760878cdd7112ecb4597ffc35ee314177c746 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/flags/default/a6ded59d1a251bbbd803d138fe257abfa600c9f9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/flags/default/86bf5b5b99bd8b44bdd5cbf2cd99c6b30ae37e5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/flags/default/b278bd5a49c2b4d37594e4a1e48a6fd993d7877b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/flags/default/783a4a08ecf38e602e3f587887e338c509bb8d18 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o: pic24fj256ga702/mcc_generated_files/i2c2Controller.c  .generated_files/flags/default/5e6f8517254f209476975bed7f37184e5bed079e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2Controller.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/flags/default/5701f5ebf04773ebfdfc0f2453fad22ceef60d69 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/flags/default/da7c4018e72495632e49db874de838992c6f9d1c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timingResource.o: timingResource.c  .generated_files/flags/default/98b1dae1b8638cb38672eb6dbcd4375fcb8f69c7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timingResource.o.d 
	@${RM} ${OBJECTDIR}/timingResource.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timingResource.c  -o ${OBJECTDIR}/timingResource.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timingResource.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/touch.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c  .generated_files/flags/default/28b2ddfb806d6c446eeeee32bcb0d21689d3d387 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/touch.c  -o ${OBJECTDIR}/_ext/1921908958/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/touch.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/uartHw.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c  .generated_files/flags/default/2e94b2db80ae85e6272851d0b796611b4d0a82ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/uartHw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/uartHw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/uartHw.c  -o ${OBJECTDIR}/_ext/1921908958/uartHw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/uartHw.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/vga.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c  .generated_files/flags/default/88c41b58bd37973ad496cf200e2598358b64643 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/vga.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/vga.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/vga.c  -o ${OBJECTDIR}/_ext/1921908958/vga.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/vga.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1921908958/ws2812.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c  .generated_files/flags/default/1669fc401a5bf4433ffb9d7ba17097fcf869eb3e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1921908958" 
	@${RM} ${OBJECTDIR}/_ext/1921908958/ws2812.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921908958/ws2812.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombat18A_18B/SerialWombat18A_18B.X/ws2812.c  -o ${OBJECTDIR}/_ext/1921908958/ws2812.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1921908958/ws2812.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/HSClock.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c  .generated_files/flags/default/d9c72df065eedc66cc7dafa8f79cc97ceccb2748 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSClock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSClock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSClock.c  -o ${OBJECTDIR}/_ext/1138356336/HSClock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/HSClock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/HSCounter.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c  .generated_files/flags/default/51548f4e4b1df778b39e319e85f080f38d7fa3ed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSCounter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/HSCounter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/HSCounter.c  -o ${OBJECTDIR}/_ext/1138356336/HSCounter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/HSCounter.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/hfServo.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c  .generated_files/flags/default/47f90276edff98615b5462687b41a5917ba44729 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hfServo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hfServo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hfServo.c  -o ${OBJECTDIR}/_ext/1138356336/hfServo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/hfServo.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/resistanceInput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c  .generated_files/flags/default/1ab10a140610ff303ce323972bcd520b2c3d4314 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/resistanceInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/resistanceInput.c  -o ${OBJECTDIR}/_ext/1138356336/resistanceInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/resistanceInput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/uartSw.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c  .generated_files/flags/default/db4a2e0b4bcc0c0e48958aa9095155e5ccb091d4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/uartSw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/uartSw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/uartSw.c  -o ${OBJECTDIR}/_ext/1138356336/uartSw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/uartSw.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/analogInput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c  .generated_files/flags/default/1ce7a66118df75e0a31f763eb862aa45542e5e2d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/analogInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/analogInput.c  -o ${OBJECTDIR}/_ext/1138356336/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/analogInput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/digitalIO.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c  .generated_files/flags/default/22e089006b7d28d283bc82aae58a7d2cf3f5fc0c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/digitalIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/digitalIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/digitalIO.c  -o ${OBJECTDIR}/_ext/1138356336/digitalIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/digitalIO.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/hBridge.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c  .generated_files/flags/default/98d93241131a4bc135892a207be5ec8abafd0b54 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hBridge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/hBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/hBridge.c  -o ${OBJECTDIR}/_ext/1138356336/hBridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/hBridge.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c  .generated_files/flags/default/952d5f59dfdbbaa5e4acf0e2b6a195fdd4c1aa53 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/PS2Keyboard.c  -o ${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/PS2Keyboard.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/inputProcess.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c  .generated_files/flags/default/ebdb762a29131e09df5d7ded48dede9afb590b6a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/inputProcess.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/inputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/inputProcess.c  -o ${OBJECTDIR}/_ext/1138356336/inputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/inputProcess.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/outputScale.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c  .generated_files/flags/default/819a5672a54f9b62c5095da8c3464c693ba6828b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/outputScale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/outputScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/outputScale.c  -o ${OBJECTDIR}/_ext/1138356336/outputScale.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/outputScale.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c  .generated_files/flags/default/73916ae5d2bcdf0734f6254407195dfeb279b4aa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pinInputProcessor.c  -o ${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pinInputProcessor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/protectedOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c  .generated_files/flags/default/9d0ae5f9f22b6c558b74d3a39befdc3800af34cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/protectedOutput.c  -o ${OBJECTDIR}/_ext/1138356336/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/protectedOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pulseOnChange.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c  .generated_files/flags/default/7b6079da845d4da578f538bc43c15b4e352d6d6c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseOnChange.c  -o ${OBJECTDIR}/_ext/1138356336/pulseOnChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pulseOnChange.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pulseTimer.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c  .generated_files/flags/default/b5a5b7bd4195dcf000407859271959eed86e22ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pulseTimer.c  -o ${OBJECTDIR}/_ext/1138356336/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pulseTimer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c  .generated_files/flags/default/b28eb22c5fe23a2bbc0582e4d744beb75af62d80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/ultrasonicDistance.c  -o ${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/ultrasonicDistance.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/watchdog.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c  .generated_files/flags/default/94c2dad7ed31df9149d69d3deb8b967746cb39e0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/watchdog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/watchdog.c  -o ${OBJECTDIR}/_ext/1138356336/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/watchdog.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/Font5x7.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c  .generated_files/flags/default/b71a9edded5a1ad25d0a3cc0d486b809c77e7a8c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/Font5x7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/Font5x7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/Font5x7.c  -o ${OBJECTDIR}/_ext/1138356336/Font5x7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/Font5x7.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/TM1637.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c  .generated_files/flags/default/ce125c1b8b2f0f17e08b3a0abb9e50dde47ffdbe .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/TM1637.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/TM1637.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/TM1637.c  -o ${OBJECTDIR}/_ext/1138356336/TM1637.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/TM1637.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/debounce.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c  .generated_files/flags/default/c84f175e233056b672eb07396da432b630cf8403 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/debounce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/debounce.c  -o ${OBJECTDIR}/_ext/1138356336/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/debounce.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/frequencyOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c  .generated_files/flags/default/5ef4ccf2032a3d0b8f78c35a94180e69797e8a8f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/frequencyOutput.c  -o ${OBJECTDIR}/_ext/1138356336/frequencyOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/frequencyOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/liquidCrystal.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c  .generated_files/flags/default/ba0a887dcd2d4c1e10aa165300d3e7c2fd94083c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/liquidCrystal.c  -o ${OBJECTDIR}/_ext/1138356336/liquidCrystal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/liquidCrystal.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/matrixKeypad.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c  .generated_files/flags/default/bfb510238825b5402abddfc45a1ee70ea1ccb0d1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/matrixKeypad.c  -o ${OBJECTDIR}/_ext/1138356336/matrixKeypad.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/matrixKeypad.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/quadEnc.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c  .generated_files/flags/default/48a3520910205b51a1b051ac156525af1322901c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/quadEnc.c  -o ${OBJECTDIR}/_ext/1138356336/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/quadEnc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c  .generated_files/flags/default/4880c346b27d810c2133dd5777659c51a39cff36 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/queuedPulseOutput.c  -o ${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/queuedPulseOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/servo.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c  .generated_files/flags/default/80bb69c9823408ce3ef02a87e21a22be76cb7a15 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/servo.c  -o ${OBJECTDIR}/_ext/1138356336/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/servo.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/throughputConsumer.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c  .generated_files/flags/default/38f6d4ecd9bdcb8e0af2ca5b1d2d00dfa51563f1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/throughputConsumer.c  -o ${OBJECTDIR}/_ext/1138356336/throughputConsumer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/throughputConsumer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/pwm.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c  .generated_files/flags/default/a3f1d203fb61994c19cfbea74a994f933a4670a7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/pwm.c  -o ${OBJECTDIR}/_ext/1138356336/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/pwm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c  .generated_files/flags/default/6e305de4b81b380344788e453cc04ea4a350e371 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/MAX7219Matrix.c  -o ${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/MAX7219Matrix.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/i2cController.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c  .generated_files/flags/default/3dbd674707702b19ccd88b34463209a239579b2f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/i2cController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/i2cController.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/i2cController.c  -o ${OBJECTDIR}/_ext/1138356336/i2cController.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/i2cController.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o: ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c  .generated_files/flags/default/1059e19ef58067a4ad37ac1522aaf8cdc5255a47 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1138356336" 
	@${RM} ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d 
	@${RM} ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../../Github/broadwellconsultinginc/SerialWombat/SerialWombatPinModes/swI2cRoutines.c  -o ${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1138356336/swI2cRoutines.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/swMath.o: ../../SerialWombatPinModes/swMath.c  .generated_files/flags/default/be3a5b5d4c70241977423510043eb0c8b8598185 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/swMath.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/swMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/swMath.c  -o ${OBJECTDIR}/_ext/2091145489/swMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/swMath.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/ir_rx.o: ../../SerialWombatPinModes/ir_rx.c  .generated_files/flags/default/8201151e43342883720c1d5e27e3ebc3cb00aa57 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_rx.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_rx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/ir_rx.c  -o ${OBJECTDIR}/_ext/2091145489/ir_rx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/ir_rx.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/queue.o: ../../SerialWombatPinModes/queue.c  .generated_files/flags/default/6560ef72889cd821680af32a9f643dff7c238f5f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/queue.c  -o ${OBJECTDIR}/_ext/2091145489/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/queue.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/blink.o: ../../SerialWombatPinModes/blink.c  .generated_files/flags/default/83508bcd5d62b9cf3cae527d4f4bd468d252ea4b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/blink.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/blink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/blink.c  -o ${OBJECTDIR}/_ext/2091145489/blink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/blink.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/ir_tx.o: ../../SerialWombatPinModes/ir_tx.c  .generated_files/flags/default/9a75953d1f56e6674965924a068a4d5a38282e38 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_tx.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/ir_tx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/ir_tx.c  -o ${OBJECTDIR}/_ext/2091145489/ir_tx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/ir_tx.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/SPI.o: ../../SerialWombatPinModes/SPI.c  .generated_files/flags/default/a7dba0751c8cc6ab7f1ca2579c75ed07ae267ebb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/SPI.c  -o ${OBJECTDIR}/_ext/2091145489/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/SPI.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/charlieplex.o: ../../SerialWombatPinModes/charlieplex.c  .generated_files/flags/default/199a28636f55b629f66a4adb3ae1d9b38c11f0e5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/charlieplex.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/charlieplex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/charlieplex.c  -o ${OBJECTDIR}/_ext/2091145489/charlieplex.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/charlieplex.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/randomBlink.o: ../../SerialWombatPinModes/randomBlink.c  .generated_files/flags/default/81b2d5ca390882c32c070f45b9fa1842c6d8e5cd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/randomBlink.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/randomBlink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/randomBlink.c  -o ${OBJECTDIR}/_ext/2091145489/randomBlink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/randomBlink.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/29c590c8e4b00e31df4a5a8df7a58a2bd3d2bea0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/flags/default/7bdd865c6427513fc9ac619b89307f1952fe015f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/flags/default/842bd4ab6c6135b0db12934f49fcbc9c56714437 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/flags/default/313136471f0986b3df2abebb2979d61020e87065 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/2091145489/protocolCommon.o: ../../SerialWombatPinModes/protocolCommon.c  .generated_files/flags/default/7a2eb17bdcef61024802fab937fe2cad3dfcb2ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2091145489" 
	@${RM} ${OBJECTDIR}/_ext/2091145489/protocolCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/2091145489/protocolCommon.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatPinModes/protocolCommon.c  -o ${OBJECTDIR}/_ext/2091145489/protocolCommon.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/2091145489/protocolCommon.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -DSW18AB -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" --fill=0x555555@0x27000:0x27800     -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-ivt,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
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
